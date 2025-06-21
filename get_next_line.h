/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:42 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/06/21 16:46:43 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdio.h>

// static char	*extract_line(char *buf, int fd, char *stash);
// static char	*split_leftover(char	*line);
// static char	*ft_substr(char const *s, unsigned int start, size_t len);
// static char	*ft_strchr(const char *s, int c);
char		*get_next_line(int fd);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);

#endif
