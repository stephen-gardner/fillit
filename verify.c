/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 22:41:47 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/11 14:17:16 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	ff(unsigned int *shape, unsigned int pos)
{
	if (!pos || pos < 0x8000 || !(*shape & pos))
		return (0);
	*shape ^= pos;
	return (1
			+ ff(shape, (pos >> 1))
			+ ff(shape, (pos << 1))
			+ ff(shape, (pos >> 4)));
}

int			block_count(unsigned int shape)
{
	int blocks;

	blocks = 0;
	while (shape > 0)
	{
		if (HIGH_BIT & shape)
			blocks++;
		shape <<= 1;
	}
	return (blocks == 4);
}

t_bool		touching(t_shape *shape)
{
	unsigned int	data;
	unsigned int	pos;

	shape->data <<= 16;
	data = shape->data;
	pos = HIGH_BIT;
	while (!(shape->data & pos))
		pos >>= 1;
	return (ff(&data, pos) == 4);
}
