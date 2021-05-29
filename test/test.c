#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main()
{

	int fd;

	fd = open("a", O_WRONLY|O_CREAT, 0777);
	if (fd == -1)
	{
		printf("bad -1\n");
		return (0);
	}
	// fd = open("a", O_RDONLY);
	// if (fd == -1)
	// {
	// 	printf("bad -1\n");
	// 	return (0);
	// }

	// 	fd = open(lisa->tokens[i], 0777);
	close(fd);
	return (0);
}
