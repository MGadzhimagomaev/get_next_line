#include "get_next_line.h"

int main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 1)
	{
		// No file given: read from stdin (fd = 0)
		fd = 0;
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening file");
			return (1);
		}
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	if (fd != 0)
		close(fd);

	return (0);
}
