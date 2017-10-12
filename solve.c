/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:47:03 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/11 21:19:50 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_bool			can_place(t_map *map, t_shape *shape,
		char row, char col)
{
	int i;

	i = 0;
	if (row + shape->length > map->size || col + shape->width > map->size)
		return (FALSE);
	while (i < 4)
	{
		shape->place[i] = ((shape->data << (i << 2)) >> 28) << (28 - col);
		if (shape->place[i++] & map->data[row++])
				break ;
	}
	if (i == 4)
	{
		while (i > 0)
			map->data[--row] |= shape->place[--i];
		shape->solved[0] = row;
		shape->solved[1] = col;
		return (TRUE);
	}
	return (FALSE);
}

static void				remove_shape(t_map *map, t_shape *shape)
{
	int 			i;
	unsigned int	map_row;
	char			row;
	char			col;

	row = shape->solved[0];
	col = shape->solved[1];
	i = 0;
	while (i < 4)
		map->data[row++] ^= shape->place[i++];
	shape->solved[0] = 0;
	shape->solved[1] = 0;
}

static t_map			*work_map(t_map *map, t_shape *shapes)
{
	char			row;
	char			col;

	if (!shapes)
		return (map);
	row = 0;
	while (row < map->size)
	{
		col = 0;
		while (col < map->size)
		{
			if (can_place(map, shapes, row, col))
			{
				if (work_map(map, shapes->next))
					return (map);
				remove_shape(map, shapes);
			}
			col++;
		}
		row++;
	}
	return (NULL);
}

t_map					*solve(t_shape *shapes)
{
	t_map	*map;
	t_shape	*current;
	char	min_area;
	char	size;

	current = shapes;
	min_area = 4;
	while ((current = current->next))
		min_area += 4;
	size = 2;
	while (size * size < min_area)
		size++;
	while (!work_map((map = gen_map(size++)), shapes))
		destroy_map(map);
	return (map);
}
