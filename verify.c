/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 22:41:47 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/12 01:50:37 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	ff(unsigned int *shape, unsigned int pos)
{
	if (!pos || pos < USED_BITS || !(*shape & pos))
		return (0);
	*shape ^= pos;
	return (1
			+ ff(shape, (pos >> 1))
			+ ff(shape, (pos << 1))
			+ ff(shape, (pos >> 4)));
}

t_bool		is_valid(unsigned int shape)
{
	unsigned int	first_block;
	int				n_blocks;
	unsigned int	pos;

	first_block = 0;
	n_blocks = 0;
	pos = HIGH_BIT;
	while (pos > UNUSED_BITS)
	{
		if (shape & pos)
		{
			if (!first_block)
				first_block = pos;
			n_blocks++;
		}
		pos >>= 1;
	}
	return (n_blocks == 4 && ff(&shape, first_block) == 4);
}
