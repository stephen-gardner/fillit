/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:14:40 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/11 20:54:06 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define HIGH_BIT 1 << 31
# define MAP_POS (long)1 << 63
# define FULL_BIT 0xF0000000
# define STAGGERED_BIT 0x88880000

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <stdio.h>

typedef	struct	s_shape
{
	unsigned int	data;
	unsigned int	place[4];
	char			length;
	char 			width;
	char			solved[2];
	struct s_shape	*next;
}				t_shape;

typedef struct	s_map
{
	unsigned int	*data;
	char			size;
}				t_map;

/*
 ** map.c
 */

t_map	*gen_map(char size);
void	destroy_map(t_map *map);

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
** solve.c
*/

t_map	*solve(t_shape *shapes);

/*
** verify.c
*/

int		block_count(unsigned int shape);
t_bool	touching(t_shape *shape);

#endif
