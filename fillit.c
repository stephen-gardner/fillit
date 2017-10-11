/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:08:35 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/10 21:51:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	int fd;
	t_shape *shapes;

	if (argc != 2)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" target_file\n");
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (1);
	shapes = NULL;
	if (!(load_file(&shapes, fd))
		|| close(fd) == -1)
	{
		ft_putstr("error\n");
		unload_shapes(shapes);
		return (1);
	}
	print_shapes(shapes);
}

void	print_shapes(t_shape *shapes)
{
	int		data;
	int		i;

	while (shapes)
	{
		data = shapes->data;
		i = 0;
		while (i < 16)
		{
			ft_putchar((data & HIGH_BIT) ? '#' : '.');
			if (!((i + 1) % 4))
				ft_putchar('\n');
			data <<= 1;
			i++;
		}
		ft_putchar('\n');
		shapes = shapes->next;
	}
}
