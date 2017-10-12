/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:08:35 by nkouris           #+#    #+#             */
/*   Updated: 2017/10/12 13:24:19 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	int		fd;
	t_shape *shapes;
	t_map	*map;

	if (argc != 2)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" target_file\n");
		return (0);
	}
	shapes = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1
		|| !(load_file(&shapes, fd))
		|| close(fd) == -1
		|| !(map = solve(shapes))
		|| !print_map(map, shapes))
	{
		ft_putstr("error\n");
		unload_shapes(shapes);
		return (1);
	}
	unload_shapes(shapes);
	return (0);
}
