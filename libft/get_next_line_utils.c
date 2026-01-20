/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:50:16 by dal-mahr     #+#    #+#             */
/*   Updated: 2025/01/01 13:50:24 by dal-mahr     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	get_next_line_cleanup(void)
{
	char	*dummy;

	dummy = get_next_line(-1);
	(void)dummy;
}
