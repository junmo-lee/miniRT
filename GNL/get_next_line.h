/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choolee <choolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:28:47 by choolee           #+#    #+#             */
/*   Updated: 2024/03/11 11:05:14 by choolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
void	read_until_nl(int fd, char **temp_buf, int *error_flag);
void	gnl_strjoin(char **s1, char const *s2, int *error_flag);
char	*substr_until_nl(char *temp_buf, char **save, int *error_flag);
void	free_based_on_error(int error_flag, char **save, char **result);
char	*gnl_strdup(const char *s1, int *error_flag);
int		find_nl_position(char *buf);
void	safe_free(char **str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
#endif