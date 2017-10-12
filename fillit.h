/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:14:40 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/12 02:00:55 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define HIGH_BIT 1 << 31
# define USED_BITS 1 << 16
# define UNUSED_BITS 1 << 15
# define FULL_BIT 0xF0000000
# define STAGGERED_BIT 0x88880000

#include <stdio.h>

typedef unsigned int	t_uint;

typedef	struct	s_shape
{
	unsigned int	data;
	unsigned int	masks[4];
	int				loc[2];
	int				length;
	int				width;
	struct s_shape	*next;
}				t_shape;

typedef struct	s_map
{
	unsigned int	*data;
	int				size;
}				t_map;

/*
** fillit.c
*/

void	print_map(t_map *map);
void	print_shapes(t_shape *shapes);

/*
** load.c
*/

t_bool	load_file(t_shape **head, int fd);
void	unload_shapes(t_shape *head);

/*
** map.c
*/

t_map	*gen_map(int size);
void	destroy_map(t_map *map);

/*
** solve.c
*/

t_map	*solve(t_shape *shapes);

/*
** verify.c
*/

t_bool	is_valid(unsigned int shape);
#endif
