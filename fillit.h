/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:14:40 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/10 22:08:54 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define FALSE 0
# define TRUE !FALSE
# define HIGH_BIT 1 << 31

typedef int	t_bool;

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <stdio.h>
typedef	struct	s_shape
{
	unsigned int	data;
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

#endif
