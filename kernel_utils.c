/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kernel_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 09:54:03 by pacovali      #+#    #+#                 */
/*   Updated: 2019/11/02 09:54:03 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** functions to create, setup, execute and free kernel
*/

# include "main_header.h"

/*
** desc.	read kernel source file
** args.	char			*name			string, name of file
** args.	char			**src_kernel	pointer to string for file content
** args.	size_t			*src_size		pointer to size of content
** ret.		void
*/

void		read_kernel_src(char *name, char **src_kernel, size_t *src_size)
{
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd < 3)
		exit(!!ft_printf("Error: kernel source not found\n"));
	*src_size = (size_t)read(fd, (void*)(*src_kernel), MAX_SIZE);
	if (*src_size < 1 || *src_size > MAX_SIZE - 1)
		exit(!!ft_printf("Error: kernel source size out of bounds\n"));
	close(fd);
}

/*
** desc.	allocate memory buffers for kernel and assign them to kernel args
** args.	t_cl_kernel		*kernel			pointer to kernel struct
** args.	t_cl_context	*context		pointer to context struct
** ret.		void
*/

void		set_kernel_args(t_cl_kernel *kernel, t_cl_context *context)
{
	cl_int					ret;

	kernel->a_buf = clCreateBuffer(context->context, CL_MEM_READ_ONLY, \
			   LIST_SIZE * sizeof(int), NULL, &ret);
	kernel->b_buf = clCreateBuffer(context->context, CL_MEM_READ_ONLY, \
				LIST_SIZE * sizeof(int), NULL, &ret);
	kernel->c_buf = clCreateBuffer(context->context, CL_MEM_WRITE_ONLY, \
				LIST_SIZE * sizeof(int), NULL, &ret);
	ret = clSetKernelArg(kernel->kernel, 0, sizeof(cl_mem), \
						 (void *)&kernel->a_buf);
	ret = clSetKernelArg(kernel->kernel, 1, sizeof(cl_mem), \
						 (void *)&kernel->b_buf);
	ret = clSetKernelArg(kernel->kernel, 2, sizeof(cl_mem), \
						 (void *)&kernel->c_buf);
}

/*
** desc.		on first call:
** desc.	sets kernel
** desc.		on further calls:
** desc.	returns existing kernel
** args.	char			*src_name		name of kernel source file
** args.	t_cl_context	*context		pointer to context struct
** ret.		t_cl_kernel*					poiner to kernel struct
*/

t_cl_kernel	*get_cl_kernel(char *src_name, t_cl_context *context)
{
	static	t_cl_kernel		kernel;
	cl_int					ret;
	char					*src_kernel;
	size_t					src_size;

	if (kernel.is_set != 1)
	{
		src_kernel = (char*)ft_memalloc(sizeof(char) * MAX_SIZE);
		read_kernel_src(src_name, &src_kernel, &src_size);
		kernel.program = clCreateProgramWithSource(context->context, 1, \
			(const char **)&src_kernel, (const size_t *)&src_size, &ret);
		ret = clBuildProgram(kernel.program, 1, &(context->device_id), \
							 NULL, NULL, NULL);
		kernel.kernel = clCreateKernel(kernel.program, "vector_add", &ret);
		set_kernel_args(&kernel, context);
		kernel.is_set = 1;
	}
	return (&kernel);
}

/*
** desc.	copy data into kernel buffers and execute kernel
** args.	t_cl_kernel		*kernel			pointer to kernel struct
** args.	t_data			*data			pointer to data struct
** ret.		void
*/

void	execute_kernel(t_cl_kernel *kernel, t_data *data)
{
	t_cl_context	*context;
	cl_int			ret;
	size_t			group_size;

	context = get_cl_context();
	ret = clEnqueueWriteBuffer(context->command_queue, kernel->a_buf, CL_TRUE,
						0, LIST_SIZE * sizeof(int), data->a, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(context->command_queue, kernel->b_buf, CL_TRUE,
						0, LIST_SIZE * sizeof(int), data->b, 0, NULL, NULL);
	group_size = GROUP_SIZE;
	ret = clEnqueueNDRangeKernel(context->command_queue, kernel->kernel, 1,
		NULL, &(data->list_size), &group_size, 0, NULL, NULL);
}

/*
** desc.	free kernel memory
** args.	t_cl_kernel		*kernel			pointer to kernel struct
** ret.		void
*/

void	clean_kernel(t_cl_kernel *kernel)
{
	cl_int			ret;

	ret = clReleaseKernel(kernel->kernel);
    ret = clReleaseProgram(kernel->program);
    ret = clReleaseMemObject(kernel->a_buf);
    ret = clReleaseMemObject(kernel->b_buf);
    ret = clReleaseMemObject(kernel->c_buf);
}
