# include "so_long.h"

static void	check_dim(char *map, int fd, t_map *so_long);
static void	check_char(char* map, int fd, t_map *so_long);
static void	check_doublon(char *map, int fd);
static void	check_walls(t_map *so_long, int fd);

void	check_map(char *map, int fd, t_map *so_long)
{
    check_dim(map, fd, so_long);// ve dim rectangulaire
	check_char(map, fd, so_long);//ve 01CEP
	check_doublon(map, fd);//ve P = 1; E = 1; C >= 1
	so_long->area = ft_split(map, '\n');
	so_long->map = ft_split(map, '\n');
	check_walls(so_long, fd);//ve si 1 autour
}

static void	check_dim(char *map, int fd, t_map *so_long)
{
	ssize_t	i;
	ssize_t x;
	ssize_t	n;
	int		check_first;

	x = 0;
	i = 0;
	n = 0;
	check_first = 0;
	while (map[i])
	{
		if (map[i] == '\n' && check_first == 0)
		{
			x = 1;
			so_long->x = i;
			n++;
			check_first = 1;
			i++;
		}
		if (map[i] == '\n' && check_first == 1)
		{
			if (x != so_long->x + 1)
				exit_error(fd, "Wrong map size");
			n++;
			x = 0;
		}
		x++;
		i++;
	}
	printf("map[i - 1] = %c i = %d\n",map[i - 1], i);
	if (map[i - 1] == '\n')
		so_long->y = n;
	else
		so_long->y = n + 1;
	printf("bravo\n");
	printf("slx = %zu sly = %zu\n",so_long->x, so_long->y);
}

static void	check_char(char* map, int fd, t_map *so_long)
{
	size_t	i;

	so_long->nb_col = 0;
	i = 0;
	while(map[i])
	{
		if (map[i] != '0' && map[i] != '1' && map[i] != 'C'
				&& map[i] != 'E' && map[i] != 'P' && map[i] != '\n')
			exit_error(fd, "Bad characters");
		if (map[i] == 'C')
			so_long->nb_col++;
		i++;
	}
	printf("col = %zu\n", so_long->nb_col);
}

static void	check_doublon(char *map, int fd)
{
	size_t	i;
	size_t	C;
	size_t	E;
	size_t	P;

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

static void		check_walls(t_map *so_long, int fd)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (so_long->area[y])
	{
		x = 0;
		while (so_long->area[y][x])
		{
			if ((y == 0 && so_long->area[y][x] != '1')
				|| (y == so_long->y - 1 && so_long->area[y][x] != '1')
				|| (x == 0 && so_long->area[y][x] != '1')
				|| (x == so_long->x - 1 && so_long->area[y][x] != '1'))
				exit_error(fd, "No closed by walls");
			x++;
		}
		y++;
	}
}

/*          -------modifier------
void    flood_file(char **area, ssize_t x, ssize_t y, t_map *so_long)
{
    if (x > so_long->x || x < 0 || y > so_long->y || y < 0 || (area[y][x] != 'C' && area[y][x] != '0' && area[y][x] != 'E' && area[y][x] != 'P'))
        return ;
	if (area[y][x] == 'E')
		area[y][x] = '1';
	else
    	area[y][x] = 'F';
    flood_file(area, x + 1, y, so_long);
    flood_file(area, x - 1, y, so_long);
    flood_file(area, x, y + 1, so_long);
    flood_file(area, x, y - 1, so_long);
}*/
