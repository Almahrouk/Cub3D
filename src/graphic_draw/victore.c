/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   victore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-joul <aal-joul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 10:46:42 by aal-joul          #+#    #+#             */
/*   Updated: 2026-01-18 10:46:42 by aal-joul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vector	create_vector(double x, double y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vector	add_vector(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return (v);
}

t_vector	rotate_vector(t_vector v, float angle)
{
	t_vector	vector;
	float		radians;

	radians = angle * PI / 180.0;
	vector.x = v.x * cos(radians) - v.y * sin(radians);
	vector.y = v.x * sin(radians) + v.y * cos(radians);
	return (vector);
}

t_vector	mult_vector(t_vector vector, double s)
{
	t_vector	v;

	v.x = vector.x * s;
	v.y = vector.y * s;
	return (v);
}
