/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:33 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/06/21 17:35:53 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *buf, int fd, char *stash);
static char	*split_leftover(char	*line);
static char	*ft_substr(char const *s, unsigned int start, size_t len);
static char	*ft_strchr(const char *s, int c);

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*stash;

	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buf);
		stash = NULL;
		buf = NULL;
		return (NULL);
	}
	if (!buf)
		return (NULL);
	line = extract_line(buf, fd, stash);
	free (buf);
	buf = NULL;
	if (!line)
		return (NULL);
	stash = split_leftover(line);
	return (line);
}

static char	*extract_line(char *buf, int fd, char *stash)
{
	char	*temp;
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

static char	*split_leftover(char	*line)
{
	char	*stash;
	size_t		i;

	i = 0;
	while (!(line[i] == '\0' || line[i] == '\n'))
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	stash = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line [i + 1] = '\0';
	return (stash);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	output = (char *)ft_calloc(len + 1, sizeof(char));
	if (!output)
		return (NULL);
	output[len] = '\0';
	while (len--)
	{
		((char *)output)[len] = ((char *)s)[start + len];
	}
	return (output);
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