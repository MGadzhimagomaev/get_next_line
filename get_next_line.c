/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:33 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/06/14 20:18:35 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char 		*buf;

	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if(!buf)
		return (NULL);
	if(read(fd, buf, BUFFER_SIZE) == -1)
	{
		return (NULL);
	}
	// close(fd);
	return(print_line(buf));
}

char	*print_line(char *buf)
{
	char		*line;
	static char	*leftover;
	int		i;

	i = 0;
	if (!leftover)
		leftover = buf;
	else
	{
		line = leftover;
		leftover = ft_strjoin(line, buf);
	}
	return (leftover);
}

int	main()
{
	int	fd;
	char *line;

	fd = open("test.txt", O_RDONLY);

	line = get_next_line(fd);
	printf("1st:\n%s\n\n", line);
	line = get_next_line(fd);
	printf("2nd:\n%s\n\n", line);
	line = get_next_line(fd);
	printf("3rd:\n%s\n\n", line);
	line = get_next_line(fd);
	printf("4th:\n%s\n\n", line);
	return (0);
}