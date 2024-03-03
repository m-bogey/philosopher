#include "so_long.h"

int	main(void)
{
	char	buf[1000];
	int		fd;
	int		size;
	t_map	so_long;

	fd = open("lvl.ber", O_RDONLY);
	if (fd == -1)
		return 1;
	size = read(fd, buf, 127);
	buf[size] = 0;
	check_map(buf, fd, &so_long);

	close(fd);
	// ouvrir une fenetre
	// insert perso avec deplacement 
	//inserer la carte et gerer collision/fin de partie/ect
}
