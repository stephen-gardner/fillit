/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:13:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/10 22:50:52 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
