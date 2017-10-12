/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:14:05 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/12 13:41:34 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char		*create_template(t_map *map)
{
	char	*out;
	int		out_len;
	int		i;

	out_len = (map->size * map->size) + map->size;
	if (!(out = (char *)malloc(out_len + 1)))
		return (NULL);
	ft_memset((void *)out, '.', out_len);
	out[out_len] = '\0';
	i = 0;
	while (i <= map->size)
	{
		out[(map->size * (i + 1)) + i] = '\n';
		i++;
	}
	return (out);
}

static t_bool	fill_template(char *out, t_map *map, t_shape *shapes)
{
	int		n_shapes;
	int		row;
	int		i;

	n_shapes = 0;
	while (shapes)
	{
		row = 0;
		while (row < 4)
		{
			i = ((shapes->loc[0] + row) * (map->size + 1));
			while (shapes->masks[row] > 0)
			{
				if (shapes->masks[row] & HIGH_BIT)
					out[i] = n_shapes + 'A';
				i++;
				shapes->masks[row] <<= 1;
			}
			row++;
		}
		n_shapes++;
		shapes = shapes->next;
	}
	return (TRUE);
}

void			destroy_map(t_map *map)
{
	free(map->data);
	free(map);
}

t_map			*gen_map(int size)
{
	t_map	*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if (!(map->data = (t_uint *)ft_memalloc(sizeof(t_uint) * size)))
	{
		free(map);
		return (NULL);
	}
	map->size = size;
	return (map);
}

t_bool			print_map(t_map *map, t_shape *shapes)
{
	char	*out;

	if (!(out = create_template(map)))
	{
		destroy_map(map);
		return (FALSE);
	}
	if (!fill_template(out, map, shapes))
	{
		free(out);
		destroy_map(map);
		return (FALSE);
	}
	ft_putstr(out);
	free(out);
	destroy_map(map);
	return (TRUE);
}
