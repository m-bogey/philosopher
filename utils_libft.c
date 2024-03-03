#include "so_long.h"

size_t	ft_strlen_c(char* map, char c)
{
	size_t	i;
	
	i = 0;
	while (map[i] != c)
		i++;
	return (i);
}

void	ft_putstr_fd(int fd, char *str)
{
    size_t	i;

	i = 0;
	while (str[i])
	{
		write(fd, str + i, 1);
		i++;
	}
}
