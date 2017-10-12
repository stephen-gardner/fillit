/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:08:35 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/12 02:06:02 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_map(t_map *map)
{
	int	row;
	int	col;

	printf("Size: %d\n", map->size);
	row = 0;
	while (row < map->size)
	{
		col = 0;
		while (col < map->size)
		{
			ft_putchar(((map->data[row] << col) & HIGH_BIT) ? '#' : '.');
			col++;
		}
		ft_putchar('\n');
		row++;
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	t_shape *shapes;

	if (argc != 2)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" target_file\n");
		return (0);
	}
	shapes = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1
		|| !(load_file(&shapes, fd))
		|| close(fd) == -1)
	{
		ft_putstr("error\n");
		unload_shapes(shapes);
		return (1);
	}
	print_shapes(shapes);
	print_map(solve(shapes));
	unload_shapes(shapes);
	return (0);
}

void	print_shapes(t_shape *shapes)
{
	int		data;
	int		i;

	while (shapes)
	{
		data = shapes->data;
		printf("Length: %d, Width: %d\n", shapes->length, shapes->width);
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
