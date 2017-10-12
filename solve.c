/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:47:03 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/12 13:12:22 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_bool	place_shape(t_map *map, t_shape *shape, int row, int col)
{
	int i;

	if (row + shape->length > map->size || col + shape->width > map->size)
		return (FALSE);
	i = 0;
	while (i < 4)
	{
		shape->masks[i] = ((shape->data << (i * 4)) >> 28) << (28 - col);
		if (shape->masks[i++] & map->data[row++])
			return (FALSE);
	}
	while (i > 0)
		map->data[--row] |= shape->masks[--i];
	shape->loc[0] = row;
	shape->loc[1] = col;
	return (TRUE);
}

static void		remove_shape(t_map *map, t_shape *shape)
{
	int i;
	int	row;

	row = shape->loc[0];
	i = 0;
	while (i < 4)
		map->data[row++] ^= shape->masks[i++];
	shape->loc[0] = 0;
	shape->loc[1] = 0;
}

static t_bool	work_map(t_map *map, t_shape *shapes)
{
	int	row;
	int	col;

	if (!shapes)
		return (TRUE);
	row = 0;
	while (row < map->size)
	{
		col = 0;
		while (col < map->size)
		{
			if (place_shape(map, shapes, row, col))
			{
				if (work_map(map, shapes->next))
					return (TRUE);
				remove_shape(map, shapes);
			}
			col++;
		}
		row++;
	}
	return (FALSE);
}

t_map			*solve(t_shape *shapes)
{
	t_map	*map;
	t_shape	*current;
	int		min_area;
	int		size;
	t_bool	solved;

	current = shapes;
	min_area = 4;
	while ((current = current->next))
		min_area += 4;
	size = 2;
	while (size * size < min_area)
		size++;
	solved = FALSE;
	while (!solved)
	{
		if (!(map = gen_map(size++)))
			return (NULL);
		if (!(solved = work_map(map, shapes)))
			destroy_map(map);
	}
	return (map);
}
