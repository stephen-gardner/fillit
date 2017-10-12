/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:55:06 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/11 20:25:04 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_map	*gen_map(char size)
{
	t_map	*map;
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if (!(map->data = (unsigned int *)ft_memalloc(sizeof(int) * size)))
	{
		free(map);
		return (NULL);
	}
	map->size = size;
	return (map);
}

void	destroy_map(t_map *map)
{
	free(map->data);
	free(map);
}
