/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:33 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/06/15 19:42:29 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buf;

	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	return (append_to_stash(buf, fd));
}

char	*append_to_stash(char *buf, int fd)
{
	static char	*stash;
	char		*temp;
	char		*leftover;
	int			bytes_read;

	bytes_read = 1;
	if (!stash)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 1)
		{
			free (buf);
			free (stash);
			return (NULL);
		}
		stash = ft_strdup(buf);
	}
	leftover = ft_strchr(stash, '\n');
	while (!(leftover) && bytes_read != 0)
	{
		temp = stash;
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if ((bytes_read == 0 && !stash) || bytes_read == -1)
		{
			free (buf);
			free (stash);
			return (NULL);
		}
		stash = ft_strjoin(temp, buf);
		// free (temp);
		leftover = ft_strchr(stash, '\n');
	}
	if (!(leftover))
	{
		temp = ft_strdup(stash);
		free (stash);
		stash = NULL;
		free (buf);
		return (temp);
	}
	temp = ft_substr(stash, 0, ft_strlen(stash) - ft_strlen(leftover) + 1);
	free (stash);
	stash = ft_strdup(leftover + 1);
	return (temp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
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

char	*ft_strchr(const char *s, int c)
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