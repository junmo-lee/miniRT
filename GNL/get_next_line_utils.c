/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choolee <choolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:28:33 by choolee           #+#    #+#             */
/*   Updated: 2024/09/01 16:49:32 by choolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*gnl_strdup(const char *s1, int *error_flag)
{
	char	*result;
	int		index;

	if (s1 == NULL || error_flag == NULL)
		return (NULL);
	index = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (index + 1));
	if (!result)
	{
		*error_flag = -1;
		return (NULL);
	}
	ft_strlcpy(result, s1, index + 1);
	return (result);
}

int	find_nl_position(char *buf)
{
	int	index;

	index = 0;
	if (buf == NULL)
		return (-1);
	while (buf[index] != '\0')
	{
		if (buf[index] == '\n')
		{
			index ++;
			return (index);
		}
		index ++;
	}
	return (-1);
}

void	safe_free(char **str)
{
	if (*str == NULL)
		return ;
	else
	{
		free(*str);
		*str = NULL;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	src_len;

	if (dst == NULL || src == NULL)
		return (0);
	index = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while ((src[index] != '\0') && (index < (size - 1)))
	{
		dst[index] = src[index];
		index ++;
	}
	dst[index] = '\0';
	return (src_len);
}

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	if (s == NULL)
		return (0);
	while (s[index] != '\0')
		index ++;
	return (index);
}
