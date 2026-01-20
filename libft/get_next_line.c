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

char	*read_until_line(int fd, char *buffer, char *temp)
{
	int		bytes;
	char	*new_temp;

	while (!ft_strchr(temp, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (bytes == 0)
				return (temp);
			return (NULL);
		}
		buffer[bytes] = '\0';
		new_temp = ft_strjoin(temp, buffer);
		free(temp);
		temp = new_temp;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buffer;
	char		*line;
	int			start_next;

	if (fd < 0)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!temp)
		temp = ft_strdup("");
	temp = read_until_line(fd, buffer, temp);
	free(buffer);
	if (!temp || temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	line = extract_line(temp, &start_next);
	temp = keep_rest(temp, start_next);
	return (line);
}

void	get_next_line_cleanup(void)
{
	char	*dummy;

	dummy = get_next_line(-1);
	(void)dummy;
}
