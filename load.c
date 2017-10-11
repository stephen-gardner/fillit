/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:13:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/10 22:02:25 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		ff(unsigned int *shape, unsigned int pos)
{
//printf("shape: %u pos: %u\n", shape, pos);
	if (pos == 0 || !(*shape & pos))
		return (0);
	*shape ^= pos;
	return (1
			+ ff(shape, (pos >> 1))
			+ ff(shape, (pos << 1))
			+ ff(shape, (pos >> 4)));
}

static t_bool	touching(t_shape *shape)
{
	unsigned int	data;
	unsigned int	pos;
	int				result;

	shape->data <<= 16;
	data = shape->data;
	pos = HIGH_BIT;
	while (!(shape->data & pos))
		pos >>= 1;
	result = ff(&data, pos);
printf("Result: %d\n", result);
	return (result == 4);
}

t_bool			load_file(t_shape **head, int fd)
{
	char	buf[21];
	int		bytes;
	t_bool	more;

	while ((bytes = read(fd, buf, 21)) == 20 || bytes == 21)
	{
		more = (bytes > 20) ? TRUE : FALSE;
		if ((more && buf[20] != '\n')
			|| !(*head = load_shape(buf))
			|| !touching(*head))
			return (FALSE);
		head = &(*head)->next;
	}
	if (bytes != 0 || more)
		return (FALSE);
	return (TRUE);
}

t_shape			*load_shape(char *buffer)
{
	t_shape	*shape;
	int		i;
	int		blocks;

	if (!(shape = (t_shape *)ft_memalloc(sizeof(t_shape))))
			return (NULL);
	blocks = 0;
	i = 0;
	while (buffer[i] && i < 20)
	{
		if (!((i + 1) % 5))
		{
			if (buffer[i] != '\n')
				return (NULL);
			i++;
		}
		else
		{
			if (buffer[i] != '.' && buffer[i] != '#')
				return (NULL);
			shape->data <<= 1;
			if (buffer[i++] == '#')
			{
				shape->data += 1;
				blocks++;
			}
		}
	}
	return ((blocks == 4) ? shape : NULL);
}

void			unload_shapes(t_shape *head)
{
	t_shape *next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}
