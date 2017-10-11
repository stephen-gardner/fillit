/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:13:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/11 12:50:48 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
			|| !(*head = load_shape(buf))
			|| !touching(*head))
			return (FALSE);
		trim_shape(*head);
		head = &(*head)->next;
	}
	if (bytes != 0 || more)
		return (FALSE);
	return (n_shapes > 0);
}

t_shape			*load_shape(char *buffer)
{
	t_shape	*shape;
	int		i;

	if (!(shape = (t_shape *)ft_memalloc(sizeof(t_shape))))
			return (NULL);
	i = 0;
	while (buffer[i] && i < 20)
	{
		if (!((i + 1) % 5))
		{
			if (buffer[i++] != '\n')
				return (NULL);
		}
		else
		{
			if (buffer[i] != '.' && buffer[i] != '#')
				return (NULL);
			shape->data <<= 1;
			if (buffer[i++] == '#')
				shape->data += 1;
		}
	}
	return ((block_count(shape->data)) ? shape : NULL);
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
