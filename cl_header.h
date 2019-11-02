/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cl_header.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 09:54:03 by pacovali      #+#    #+#                 */
/*   Updated: 2019/11/02 09:54:03 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CL_HEADER_H
# define __CL_HEADER_H

# include <OpenCL/cl.h>

# define LIST_SIZE	8192
# define GROUP_SIZE	256
# define MAX_SIZE	20000

typedef struct			s_data
{
	size_t				list_size;
	int					*a;
	int					*b;
	int					*c;
}						t_data;

typedef struct			s_cl_context
{
	char				is_set;
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_context			context;
	cl_command_queue	command_queue;
}						t_cl_context;

typedef struct			s_cl_kernel
{
	char				is_set;
	cl_mem				a_buf;
	cl_mem				b_buf;
	cl_mem				c_buf;
	cl_program			program;
	cl_kernel			kernel;
}						t_cl_kernel;

t_cl_context			*get_cl_context(void);
void					clean_context(t_cl_context *cl_context);
void					read_kernel_src(char *name, char **src_kernel, \
										size_t *src_size);
void					set_kernel_args(t_cl_kernel *kernel, \
										t_cl_context *context);
t_cl_kernel				*get_cl_kernel(char *src_name, t_cl_context *context);
void					execute_kernel(t_cl_kernel *kernel, t_data *data);
void					clean_kernel(t_cl_kernel *kernel);

#endif
