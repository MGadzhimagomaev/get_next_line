#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	int		line_count = 0;

	fd = open("multiple_nl.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", ++line_count, line);
		free(line); // Important: must free every line
	}
	close(fd);
	return (0);
}
