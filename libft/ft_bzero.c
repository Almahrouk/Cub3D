/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dal-mahr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:29:05 by dal-mahr          #+#    #+#             */
/*   Updated: 2024/09/03 18:31:28 by dal-mahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//size_t is unsigned integer & Platform-Dependent Size
//used in memoy allocation function

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*int	main(void)
{
	int		v[20];

	for (int i = 0; i < 20; ++i)
		v[i] = 42;

	for (int i = 0; i < 20; ++i)
		printf("%d\n", v[i]);
	puts("");

	ft_bzero(v, 80);
	
	for (int i = 0; i < 20; ++i)
		printf("%d\n", v[i]);
}*/
