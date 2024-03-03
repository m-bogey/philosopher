#include "so_long.h"

void	exit_error(int fd, char *str)
{
	write(2, "Error\n", 6);
	ft_putstr_fd(2, str);
	close(fd);
	exit(EXIT_FAILURE);
}