/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:33 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/07/27 17:09:25 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_fill_stash(int fd, char **stash)
{
	char	*buf;
	char	*tmp;
	ssize_t	br;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(*stash), *stash = NULL, NULL);
	br = 1;
	while (!ft_strchr(*stash, '\n') && br > 0)
	{
		br = read(fd, buf, BUFFER_SIZE);
		if (br <= 0)
			break ;
		buf[br] = '\0';
		tmp = ft_strjoin(*stash, buf);
		free(*stash);
		*stash = tmp;
	}
	free(buf);
	if (br < 0 || !*stash)
		return (free(*stash), *stash = NULL, NULL);
	return (*stash);
}

char	*ft_get_line(const char *stash)
{
	size_t	len;
	size_t	i;
	char	*line;

	len = 0;
	i = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

void	ft_update_stash(char **stash, size_t len)
{
	char	*rest;

	if ((*stash)[len])
	{
		rest = ft_strdup(*stash + len);
		free(*stash);
		*stash = rest;
	}
	else
	{
		free(*stash);
		*stash = NULL;
	}
}

char	*ft_readline(int fd, char **stash)
{
	char	*line;

	if (!*stash || !ft_strchr(*stash, '\n'))
	{
		if (!ft_fill_stash(fd, stash))
			return (NULL);
	}
	if (!*stash || !**stash)
		return (free(*stash), *stash = NULL, NULL);
	line = ft_get_line(*stash);
	if (!line)
		return (free(*stash), *stash = NULL, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = ft_readline(fd, &stash[fd]);
	if (!line)
		return (NULL);
	len = 0;
	while (stash[fd][len] && stash[fd][len] != '\n')
		len++;
	if (stash[fd][len] == '\n')
		len++;
	ft_update_stash(&stash[fd], len);
	return (line);
}

/*
int	main(void)
{
	int		fd;
	char	*line;

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
//*/