#include "so_long.h"

void	make_area(char *buf, t_map *so_long)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	j = 0;
	so_long->area = malloc(sizeof(char *) * so_long->y + 1);
	//if (area == NULL)
	//	exit_error(fd, "Fail malloc area");
	so_long->area[so_long->y] = NULL;
	while (i < so_long->y)
	{
		k = 0;
		so_long->area[i] = malloc(sizeof (char) * so_long->x);
		while (buf[j] != '\n')
		{
			so_long->area[i][k]= buf[j];
			j++;
			k++;
		}
		so_long->area[i][k] = '\0';
		j++;
		i++;
	}
}

void	check_path() 
{

}

int main()
{
    int fd;
    int size;
    char buf[1000];
	t_map	so_long;

	so_long.x = 8;
	so_long.y = 8;
    fd = open("lvl.ber", O_RDONLY);
    size = read(fd, buf, 1020);
	make_area(buf, &so_long);
	for(int i = 0;so_long.area[i];i++)
    	printf("%s\n", so_long.area[i]);
}