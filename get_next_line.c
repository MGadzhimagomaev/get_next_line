/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:33 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/07/05 19:26:18 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_next(int fd, char *stash);
static char	*extract_leftover(char *stash);
static char	*extract_line(char *stash);
static char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	stash = read_next(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = extract_leftover(stash);
	return (line);
}

static char	*read_next(int fd, char *stash)
{
	char	*buf;
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free (buf), NULL);
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free (buf);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t		i;
	char		*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	if (!(ft_strchr(stash, '\n')))
		return (ft_strdup(stash));
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_substr(stash, 0, i + 1);
	return (line);
}

static char	*extract_leftover(char *stash)
{
	size_t		i;
	char		*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || stash[i + 1] == '\0')
		return (free(stash), NULL);
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i - 1);
	free (stash);
	if (!new_stash || new_stash[0] == '\0')
	{
		return (free (new_stash), NULL);
		// new_stash = NULL;
	}
	return (new_stash);
}

static char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
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