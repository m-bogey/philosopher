#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
// # include <sys/mman.h>
// #include "minilibx-linux/mlx_int.h"
// #include "minilibx-linux/mlx.h"

typedef struct	s_map
{
	size_t		x;
	size_t		y;
	size_t		pos_begin_x;
	size_t		pos_begin_y;
	char		**area;
}				t_map;

void	check_map(char *map, int fd, t_map so_long);
size_t	ft_strlen_c(char* map, char c);
void	ft_putstr_fd(int fd, char *str);
void	exit_error(int fd, char *str);

#endif 