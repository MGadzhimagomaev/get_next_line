/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:33 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/06/29 21:04:16 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_next(char *buf, int fd, char *stash);
static char	*extract_leftover(char *stash);
static char	*extract_line(char *stash);
static char	*ft_strchr(const char *s, int c);

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stash = read_next(buf, fd, stash);
	free (buf);
	buf = NULL;
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
		return (NULL);
	stash = extract_leftover(stash);
	return (line);
}

static char	*read_next(char *buf, int fd, char *stash)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buf);
		free(temp);
		if (!stash)
			return (NULL);
		temp = NULL;
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t		i;
	char		*line;

	i = 0;
	if (!stash || *stash == '\0')
		return (NULL);
	if (!(ft_strchr(stash, '\n')))
		return (ft_strdup(stash));
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_substr(stash, 0, i + 1);
	if (line && *line == '\0')
	{
		free(line);
		line = NULL;
	}
	return (line);
}

static char	*extract_leftover(char *stash)
{
	size_t		i;
	char		*new_stash;

	i = 0;
	if (!stash || *stash == '\0')
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i - 1);
	free (stash);
	stash = NULL;
	if (new_stash && *new_stash == '\0')
	{
		free (new_stash);
		new_stash = NULL;
	}
	return (new_stash);
}

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
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