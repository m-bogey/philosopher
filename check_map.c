#include "so_long.h"

static void		check_dim(char* map, int fd, t_map so_long);
static void		check_char(char* map, int fd);
static void		check_doublon(char *map, int fd);
static void		check_walls(char *map, int fd);

void	check_map(char *map, int fd, t_map so_long)
{
	check_dim(map, fd, so_long);// ve dim rectangulaire
	check_char(map, fd);//ve 01CEP
	check_doublon(map, fd);//ve P = 1; E = 1; C >= 1
	check_walls(map, fd);//ve si 1 autour
	//ve chemin valide
	
	printf("\n%s",map);
}

static void	check_dim(char* map, int fd, t_map so_long)
{
	size_t	total;
	size_t	x;
	size_t	y;
	size_t	last_line;

	total = ft_strlen_c(map, '\0') + 1;
	x = ft_strlen_c(map, '\n') + 1;
	y = total / x;
	so_long->x = x;
	so_long->y = y;
	printf("x = %zu, y = %zu",x, y);
	//verifier dimension rectangulaire
	if (total % x != 0)
		exit_error(fd, "Wrong map size");
	if (y == x - 1)
		exit_error(fd, "The map must not be square");
	y = y - 1;
	last_line = (x * y) - 1;
	while (y != 0)
	{
		if(map[last_line] != '\n')
			exit_error(fd, "Wrong map size");
		y--;
	}
}

static void	check_char(char* map, int fd)
{
	size_t	i;

	i = 0;
	while(map[i])
	{
		if (map[i] != '0' && map[i] != '1' && map[i] != 'C'
				&& map[i] != 'E' && map[i] != 'P' && map[i] != '\n')
			exit_error(fd, "Bad characters");
		i++;
	}
}

static void	check_doublon(char *map, int fd)
{
	size_t	i;
	int		C;
	int		E;
	int		P;

	i = 0;
	C = 0;
	E = 0;
	P = 0;
	while (map[i])
	{
		if (map[i] == 'C')
			C++;
		if (map[i] == 'E')
			E++;
		if (map[i] == 'P')
			P++;
		i++;
	}
	if (C == 0 || E != 1 || P != 1)
		exit_error(fd, "Duplicates characters or no collectible");
}

static void		check_walls(char *map, int fd)
{
	size_t	total;
	size_t	x;
	size_t	y;
	size_t	i;

	total = ft_strlen_c(map, '\0') + 1;
	if (total < 18)
		exit_error(fd, "The map is too small");
	x = ft_strlen_c(map, '\n') + 1;
	y = total / x;
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n' && (map[i + 1] != '1' || map[i - 1] != '1'))
			exit_error(fd, "No closed by walls");
		if (i <= x - 2 && map[i] != '1')
			exit_error(fd, "No closed by walls");
		if ((i >= x * (y - 1)) && map[i] != '1')
			exit_error(fd, "No closed by walls");
		i++;
	}
}