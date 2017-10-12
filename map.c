/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:55:06 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/11 23:24:06 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_map	*gen_map(int size)
{
	t_map	*map;
	int		row;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if (!(map->data = (unsigned int *)malloc(sizeof(unsigned int) * size)))
	{
		free(map);
		return (NULL);
	}
	row = 0;
	while (row < size)
		map->data[row++] = 0;
	map->size = size;
	return (map);
}

void	destroy_map(t_map *map)
{
	free(map->data);
	free(map);
}
