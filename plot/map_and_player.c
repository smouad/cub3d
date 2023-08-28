/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_and_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybourais <ybourais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:06:56 by ybourais          #+#    #+#             */
/*   Updated: 2023/08/28 11:57:48 by ybourais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_square(uint32_t color, int x, int y)
{
	int size_x = x + SQUAR_SIZE - 1;
	int size_y = y + SQUAR_SIZE - 1;
	int firs_y = y;

	while (x < size_x)
	{
		y = firs_y;
		while (y < size_y)
		{
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_grid()
{
    int i = 0;
    while (i < g_elems.height * SQUAR_SIZE)
    {
        int j = 0;
        while (j < g_elems.width * SQUAR_SIZE)
        {
			mlx_put_pixel(image, j, i, BLACK);
            j++;
        }
        i++;
    }
}

void plot_sky_and_land()
{
	int i = 0;
	while (i < HEIGHT)
	{
		int j = 0;
		while (j < WIDTH)
		{
			if (i <= HEIGHT/2)
				mlx_put_pixel(image, j, i, DARK_BLUE);
			else
				mlx_put_pixel(image, j, i, DARK_GREEN);
			j++;
		}
		i++;
	}
}

void get_y_coordinate(float *y0, float *y1, float ray_distance, double ray_angle)
{
	int static b;
	float wall_height;
	
	ray_distance = ray_distance*cos(ray_angle - g_elems.player_angle);
	wall_height = SQUAR_SIZE*HEIGHT/ray_distance;

	*y0 = HEIGHT/2 - wall_height/2;
	*y1 = *y0 + wall_height;
	b++;
}

void _2_to_3d()
{
	int x = 0;
	float y0;
	float y1;
	double ray_angle;

	plot_sky_and_land();
	ray_angle = (g_elems.player_angle - 30*TO_RADIAN);
	while (x < WIDTH)
	{
		get_y_coordinate(&y0, &y1, g_elems.ray_distante[x], ray_angle);
		if(y0 > HEIGHT || y1 > HEIGHT)
		{
			y0 = 0;
			y1 = HEIGHT - 1;
		}
		DDA(x, y0, x, y1, ORANGE);
		ray_angle += (FOV_ANGLE/RAYS_NUM);
		x++;
	}
}

void draw_player(uint32_t color, float x, float y)
{
	g_elems.pos_x_p = x + g_elems.pos_x_p;
	g_elems.pos_y_p = y + g_elems.pos_y_p;
	x = g_elems.pos_x_p;
	y = g_elems.pos_y_p;

	int radius = PLAYER_SIZE / 2;
	int pixel_x = x - radius;
	cast_rays();
	draw_line(x, y);
	while (pixel_x < x + radius)
    {
		int pixel_y = y - radius;
        while (pixel_y <= y + radius)
        {
            if (pow(pixel_x - x, 2) + pow(pixel_y - y, 2) <= pow(radius, 2))
                mlx_put_pixel(image, pixel_x, pixel_y, color);
			pixel_y++;
        }
		pixel_x++;
    }
}

void DDA(int x0, int y0, int x1, int y1, uint32_t color)
{
	t_norm norm;
    norm.dx = x1 - x0;
    norm.dy = y1 - y0;
	int steps;

	if (abs(norm.dx) >= abs(norm.dy))
		steps = abs(norm.dx);
	else
		steps = abs(norm.dy);
    norm.x = x0;
    norm.y = y0;
	norm.x_step = (float)norm.dx / steps;
	norm.y_step = (float)norm.dy / steps;
	int i = 0;
	while (i <= steps)
	{
		mlx_put_pixel(image, round(norm.x), round(norm.y), color);
		norm.x = norm.x + norm.x_step;
		norm.y = norm.y + norm.y_step;
		i++;
	}
}


void init_image()
{
	// mlx = mlx_init((int)(g_elems.width*SQUAR_SIZE), (int)(g_elems.height*SQUAR_SIZE), "GAME", 0);
	// image = mlx_new_image(mlx, g_elems.width*SQUAR_SIZE, g_elems.height*SQUAR_SIZE);
	// mlx_image_to_window(mlx, image, 0, 0);

	mlx = mlx_init(WIDTH, HEIGHT, "GAME", 0);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
}

void plot_map()
{
	int i;
	
	draw_grid();
	i = 0;
	while (g_elems.map[i])
	{
		int j = 0;
		while (g_elems.map[i][j])
		{
			if(g_elems.map[i][j] == '1')
				draw_square(RED, (SQUAR_SIZE) * j, (SQUAR_SIZE) * i);
			else if (g_elems.map[i][j] != ' ')
				draw_square(GRAY, (SQUAR_SIZE) * j, (SQUAR_SIZE) * i);
			j++;
		}
		i++;
	}
}