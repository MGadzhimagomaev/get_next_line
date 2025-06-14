/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:54 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/06/14 20:16:02 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		((unsigned char *)s)[--n] = '\0';
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*output;

	if (size != 0 && nmemb != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	output = (void *)malloc(nmemb * size);
	if (!output)
		return (NULL);
	ft_bzero(output, nmemb * size);
	return (output);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (sizeof(char) * i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	dest = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	len_pre;
	size_t	len_suff;

	len_pre = ft_strlen(s1);
	len_suff = ft_strlen(s2);
	output = (char *)ft_calloc(len_pre + len_suff + 1, sizeof(char));
	if (!output)
		return (NULL);
	ft_strlcpy(output, s1, len_pre + 1);
	ft_strlcpy(output + len_pre, s2, len_suff + 1);
	return (output);
}