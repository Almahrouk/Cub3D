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

static char *temp = NULL;

static char	*keep_rest(char *temp, int start)
{
	char	*rest;
	int		len;

	len = ft_strlen(temp) - start;
	if (len <= 0)
		return (free(temp), (NULL));
	rest = ft_substr(temp, start, len);
	return (free(temp), (rest));
}

static char	*extract_line(char *temp, int *start_next)
{
	char	*line;
	int		i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		*start_next = i + 1;
	else
	{
		*start_next = i;
		if (i == 0 && temp[i] == '\0')
			return (NULL);
	}
	line = ft_substr(temp, 0, *start_next);
	return (line);
}

static char	*new_line(int fd, char *buffer, char *temp)
{
	int		read_bytes;
	char	*new_temp;

	while (!ft_strchr(temp, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0 && temp[0] == '\0')
			return (free(temp), (NULL));
		if (read_bytes <= 0)
			return (temp);
		buffer[read_bytes] = '\0';
		new_temp = ft_strjoin(temp, buffer);
		free(temp);
		temp = new_temp;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	int			start_next;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (temp == NULL)
		temp = ft_strdup("");
	temp = new_line(fd, buffer, temp);
	free(buffer);
	if (!temp)
		return (NULL);
	line = extract_line(temp, &start_next);
	if (!line)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	temp = keep_rest(temp, start_next);
	return (line);
}

void	gnl_cleanup(void)
{
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
}
