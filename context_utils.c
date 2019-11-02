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
** functions to create, setup and free context
*/

# include "main_header.h"

/*
** desc.		on first call:
** desc.	gets context - gets system info: available platform and devices,
** desc.	sets context and command queue
** desc.		on further calls:
** desc.	returns current context
** args.	void
** ret.		t_cl_context	*context	pointer to current context
*/

t_cl_context	*get_cl_context(void)
{
	static	t_cl_context	context;
	cl_int					ret;

	if (context.is_set != 1)
	{
		ret = clGetPlatformIDs(1, &(context.platform_id), \
							&(context.ret_num_platforms));
		if (ret != CL_SUCCESS)
			exit(!!(ft_printf("Error: listing platforms failed\n")));
		ret = clGetDeviceIDs(context.platform_id, CL_DEVICE_TYPE_DEFAULT, \
					1, &(context.device_id), &(context.ret_num_devices));
		if (ret != CL_SUCCESS)
			exit(!!(ft_printf("Error: listing devices failed\n")));
		context.context = clCreateContext(NULL, 1, &(context.device_id), \
										   NULL, NULL, &ret);
		context.command_queue = clCreateCommandQueue(context.context, \
										context.device_id, 0, &ret);
		context.is_set = 1;
	}
	return (&context);
}

/*
** desc.	free context memory
** args.	t_cl_context	*cl_context		pointer to context struct
** ret.		void
*/

void	clean_context(t_cl_context *cl_context)
{
	cl_int			ret;

    ret = clFlush(cl_context->command_queue);
    ret = clFinish(cl_context->command_queue);
    ret = clReleaseCommandQueue(cl_context->command_queue);
    ret = clReleaseContext(cl_context->context);
}
