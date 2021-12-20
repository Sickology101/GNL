
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>

int	get_next_line(const int fd, char **line);

int main ()
{
	int fd;
	int fd1;
	char **file;

	fd = open("42", O_RDONLY);
	if(fd == -1)
	{
		ft_putstr("open() error");
		return (1);
	}
	printf("fd = %d \n",fd);
	file = malloc(sizeof(char *) * 8096);
	while (get_next_line(fd,file) != 0)
		printf("%s\n",file[0]);
	printf("%s\n",file[0]);
	fd1 = open("43", O_RDONLY);
	if(fd == -1)
	{
		ft_putstr("open() error");
		return (1);
	}
	printf("fd = %d \n",fd1);
	file = malloc(sizeof(char *) * 8096);
	get_next_line(fd1, file);
	printf("line2 = %s\n",file[0]);
	get_next_line(fd1, file);
	printf("line2 = %s\n",file[0]);
	get_next_line(fd1, file);
	printf("line2 = %s\n",file[0]);
	get_next_line(fd1, file);
	printf("line2 = %s\n",file[0]);
	if (close(fd) == -1)
	{
		ft_putstr("close() error");
		return (1);
	}

	return (0);
}
