/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal_lines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:21:41 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/31 20:13:03 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_direction(int *ray_up, int *ray_right, double ray_angle)
{
	*ray_up = ray_angle >= M_PI && ray_angle < 2*M_PI;
	*ray_right = ray_angle >= (3*M_PI)/2 || ray_angle < M_PI/2;
}

void init_horizontal_coordinate(float *x, float *y, double ray_angle, int ray_up)
{
	*y = ((int)(g_inf.pos_y_p/T_SIZE))*T_SIZE;
	if(!ray_up)
		*y += T_SIZE;
	*x = g_inf.pos_x_p - ((g_inf.pos_y_p - *y)/tan(ray_angle - M_PI));
	if(ray_up)
		(*y) -= (float)1/HEIGHT;
}

void init_horizontal_steps(float *delta_x, float *delta_y, double ray_angle)
{
	*delta_x = T_SIZE/tan(ray_angle - M_PI);
	*delta_y =  T_SIZE;
}

void find_horizontal_intersection(double ray_angle, float *x, float *y)
{
	t_coordinate horizontal;

	init_direction(&horizontal.ray_up, &horizontal.ray_right, ray_angle);
	init_horizontal_coordinate(&horizontal.n_x, &horizontal.n_y, ray_angle, horizontal.ray_up);
	init_horizontal_steps(&horizontal.delta_x, &horizontal.delta_y, ray_angle);

	if((!horizontal.ray_right && horizontal.delta_x > 0) || (horizontal.ray_right && horizontal.delta_x < 0))
		horizontal.delta_x *= -1;

	if(horizontal.ray_up)
		horizontal.delta_y *= -1;

	while (horizontal.n_x >= 0 && horizontal.n_x <= g_inf.width*T_SIZE && horizontal.n_y >= 0 && horizontal.n_y <= g_inf.height*T_SIZE)
	{
		if (in_map_pixel(horizontal.n_x, horizontal.n_y))
		{
			*x = horizontal.n_x;
			*y = horizontal.n_y;
			break;
		}
		horizontal.n_x += horizontal.delta_x;
		horizontal.n_y += horizontal.delta_y;
	}
}
