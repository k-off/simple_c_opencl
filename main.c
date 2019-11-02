/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pacovali <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 09:54:03 by pacovali      #+#    #+#                 */
/*   Updated: 2019/11/02 09:54:03 by pacovali      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "main_header.h"

t_data	*get_data(void)
{
	static t_data	*data = NULL;
	size_t			i;

	if (!data)
	{
		data = (t_data*)ft_memalloc(sizeof(t_data));
		if (!data)
			exit(!!ft_printf("Error: data not allocated\n"));
		data->list_size = LIST_SIZE;
		data->a = (int*)ft_memalloc(sizeof(int) * data->list_size);
		data->b = (int*)ft_memalloc(sizeof(int) * data->list_size);
		data->c = (int*)ft_memalloc(sizeof(int) * data->list_size);
		i = 0;
		while (i < data->list_size)
		{
			data->a[i] = (int)i;
			data->b[i] = (int)(data->list_size - i);
			i++;
		}
	}
	return (data);
}

void	display_result(int *res)
{
	int			i;

	i = 0;
	while (i < LIST_SIZE)
	{
		ft_printf("%d ", res[i]);
		if (i % 32 == 31)
			ft_printf("\n");
		i++;
	}
}

void	free_data_struct(t_data *data)
{
	free(data->a);
	free(data->b);
	free(data->c);
	free(data);
}

int		main(int ac, char **av)
{
	t_data			*data;
	t_cl_context	*cl_context;
	t_cl_kernel		*kernel;
	int				res[LIST_SIZE];

	if (ac < 2)
		exit(!!ft_printf("Error: kernel source name not provided\n"));
	data = get_data();
	cl_context = get_cl_context();
	kernel = get_cl_kernel(av[1], cl_context);
	for (int i = 0; i < 10; i++) {
		execute_kernel(kernel, data);
		clEnqueueReadBuffer(cl_context->command_queue, kernel->c_buf, CL_TRUE,
					0, LIST_SIZE * sizeof(int), res, 0, NULL, NULL);
		display_result(res);
		ft_printf("\n");
	}
	display_result(res);
	clean_context(cl_context);
	clean_kernel(kernel);
	free_data_struct(data);
	exit(0);
}
