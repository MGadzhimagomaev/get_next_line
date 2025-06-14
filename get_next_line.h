/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgadzhim <mgadzhim@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:42 by mgadzhim          #+#    #+#             */
/*   Updated: 2025/06/14 20:14:41 by mgadzhim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

#include <fcntl.h>
// #include "include/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdio.h>

char	*print_line(char *buf);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
