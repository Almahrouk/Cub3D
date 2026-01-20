/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:15:16 by dal-mahr          #+#    #+#             */
/*   Updated: 2024/11/10 11:15:16 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*keep_rest(char *temp, int start)
{
	char	*rest;
	int		len;

	len = ft_strlen(temp) - start;
	if (len <= 0)
	{
		free(temp);
		return (NULL);
	}
	rest = ft_substr(temp, start, len);
	free(temp);
	return (rest);
}

static char	*extract_line(char *temp, int *start_next)
{
	int		i;
	char	*line;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		*start_next = i + 1;
	else
	{
		*start_next = i;
		if (i == 0)
			return (NULL);
	}
	line = ft_substr(temp, 0, *start_next);
	return (line);
}

static char	*check_tmp(char *temp)
{
	if (!temp || temp[0] == '\0')
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	t_gnl		gnl;
	static char	*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (fd < 0 && temp)
		{
			free(temp);
			temp = NULL;
		}
		return (NULL);
	}
	gnl.buffer = malloc(BUFFER_SIZE + 1);
	if (!gnl.buffer)
		return (NULL);
	if (!temp)
		temp = ft_strdup("");
	temp = read_until_line(fd, gnl.buffer, temp);
	free(gnl.buffer);
	temp = check_tmp(temp);
	if (!temp)
		return (NULL);
	gnl.line = extract_line(temp, &gnl.start_next);
	temp = keep_rest(temp, gnl.start_next);
	return (gnl.line);
}
