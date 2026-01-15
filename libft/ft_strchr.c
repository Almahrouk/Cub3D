/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:45:12 by dal-mahr          #+#    #+#             */
/*   Updated: 2024/08/31 19:04:26 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//first occarence of the char c in the string s
//The cast (char *)s is done to match the return type of the function
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}
