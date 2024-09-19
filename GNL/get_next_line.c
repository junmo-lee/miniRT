/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:28:09 by choolee           #+#    #+#             */
/*   Updated: 2024/09/19 18:33:00 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*result;
	int			error_flag;
	char		*temp_buf;

	result = NULL;
	error_flag = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (save != NULL)
		temp_buf = gnl_strdup(save, &error_flag);
	else
		temp_buf = gnl_strdup("", &error_flag);
	safe_free(&save);
	if (find_nl_position(temp_buf) == -1 && temp_buf != NULL)
		read_until_nl(fd, &temp_buf, &error_flag);
	if (error_flag != -1)
		result = substr_until_nl(temp_buf, &save, &error_flag);
	free_based_on_error(error_flag, &save, &result);
	safe_free(&temp_buf);
	return (result);
}

void	read_until_nl(int fd, char **temp_buf, int *error_flag)
{
	char	*read_buf;
	int		temp_read_size;

	if (*temp_buf == NULL || error_flag == NULL)
		return ;
	read_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buf)
	{
		*error_flag = -1;
		return ;
	}
	while (1)
	{
		temp_read_size = read(fd, read_buf, BUFFER_SIZE);
		if (temp_read_size < 1)
			break ;
		read_buf[temp_read_size] = '\0';
		gnl_strjoin(temp_buf, read_buf, error_flag);
		if (find_nl_position(*temp_buf) != -1 || *error_flag == -1)
			break ;
	}
	if (temp_read_size == -1)
		*error_flag = -1;
	safe_free(&read_buf);
}

void	gnl_strjoin(char **s1, char const *s2, int *error_flag)
{
	char		*tem_buf;
	int			index;
	const int	s1_len = ft_strlen(*s1);
	const int	s2_len = ft_strlen(s2);

	if (*s1 == NULL || s2 == NULL || error_flag == NULL)
		return ;
	index = 0;
	tem_buf = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!tem_buf)
	{
		*error_flag = -1;
		return ;
	}
	ft_strlcpy(tem_buf, *s1, s1_len + 1);
	while (index < s2_len)
	{
		tem_buf[s1_len + index] = s2[index];
		index ++;
	}
	tem_buf[s1_len + index] = '\0';
	safe_free(s1);
	*s1 = tem_buf;
}

char	*substr_until_nl(char *temp_buf, char **save, int *error_flag)
{
	char	*result;
	int		n_index;

	if (temp_buf == NULL || error_flag == NULL)
		return (NULL);
	n_index = find_nl_position(temp_buf);
	if (n_index == -1)
	{
		n_index = ft_strlen(temp_buf);
		*error_flag = 1;
	}
	result = (char *)malloc(sizeof(char) * (n_index + 1));
	if (!result)
	{
		*error_flag = -1;
		return (NULL);
	}
	ft_strlcpy(result, temp_buf, n_index + 1);
	*save = gnl_strdup(temp_buf + n_index, error_flag);
	return (result);
}

void	free_based_on_error(int error_flag, char **save, char **result)
{
	if (error_flag == -1)
	{
		safe_free(save);
		safe_free(result);
		return ;
	}
	if (*result != NULL && *result[0] == '\0')
		safe_free(result);
	if ((result != NULL && error_flag == 1))
		safe_free(save);
}
