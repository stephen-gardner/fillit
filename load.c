/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:13:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/12 01:39:28 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		calc_dimen(t_shape *shape)
{
	while (shape->data & (FULL_BIT >> (shape->length * 4)))
		shape->length++;
	while (shape->data & ((STAGGERED_BIT) >> shape->width))
		shape->width++;
}

static t_bool	load_shape(t_shape **head, char *buffer)
{
	int		i;

	if (!(*head = (t_shape *)ft_memalloc(sizeof(t_shape))))
		return (FALSE);
	i = 0;
	while (buffer[i] && i < 20)
	{
		if (!((i + 1) % 5))
		{
			if (buffer[i++] != '\n')
				return (FALSE);
		}
		else
		{
			if (buffer[i] != '.' && buffer[i] != '#')
				return (FALSE);
			(*head)->data <<= 1;
			if (buffer[i++] == '#')
				(*head)->data++;
		}
	}
	(*head)->data <<= 16;
	return (TRUE);
}

static void		trim_shape(t_shape *shape)
{
	unsigned int	data;

	while (!(shape->data & FULL_BIT))
		shape->data <<= 4;
	while (!(shape->data & STAGGERED_BIT))
	{
		data = 0;
		data += ((shape->data << 1) >> 28) << 28;
		data += ((shape->data << 5) >> 28) << 24;
		data += ((shape->data << 9) >> 28) << 20;
		data += ((shape->data << 13) >> 28) << 16;
		shape->data = data;
	}
}

t_bool			load_file(t_shape **head, int fd)
{
	char	buf[21];
	int		bytes;
	int		n_shapes;
	t_bool	more;

	n_shapes = 0;
	while ((bytes = read(fd, buf, 21)) == 20 || bytes == 21)
	{
		if (++n_shapes > 26)
			break ;
		more = (bytes > 20) ? TRUE : FALSE;
		if ((more && buf[20] != '\n')
			|| !load_shape(head, buf)
			|| !is_valid((*head)->data))
			return (FALSE);
		trim_shape(*head);
		calc_dimen(*head);
		head = &(*head)->next;
	}
	if (bytes != 0 || more)
		return (FALSE);
	return (n_shapes > 0);
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
