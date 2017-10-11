/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:14:40 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/11 13:12:04 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define FALSE 0
# define TRUE !FALSE
# define HIGH_BIT 1 << 31
# define FULL_BIT 0xF0000000
# define STAGGERED_BIT 0x88880000


typedef int	t_bool;

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <stdio.h>
typedef	struct	s_shape
{
	unsigned int	data;
	unsigned int	solved;
	int				length;
	int 			width;
	struct s_shape	*next;
}				t_shape;

/*
** fillit.c
*/

void	print_shapes(t_shape *shapes);

/*
** load.c
*/

t_bool	load_file(t_shape **head, int fd);
t_shape	*load_shape(char *buffer);
void	unload_shapes(t_shape *head);

/*
** verify.c
*/

int		block_count(unsigned int shape);
t_bool	touching(t_shape *shape);
void	trim_shape(t_shape *shape);

#endif
