/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:22:30 by msodor            #+#    #+#             */
/*   Updated: 2023/08/31 20:13:03 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void    get_txtr_pixels(uint8_t *pixels, int idx)
{
    int i;
    int j;

    i = 0;
    j = 0;
    g_inf.txtr[idx].texture = malloc(sizeof(uint32_t) * (g_inf.txtr[idx].width * g_inf.txtr[idx].height) * 4);
    while (i < g_inf.txtr[idx].width * g_inf.txtr[idx].height * 4)
    {
        g_inf.txtr[idx].texture[j] = ft_pixel(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
        i += 4;
        j++;
    }
}

void get_texture()
{
    int i;
    mlx_texture_t *texture[4];

    texture[0] = mlx_load_png(g_inf.no);
    texture[1] = mlx_load_png(g_inf.so);
    texture[2] = mlx_load_png(g_inf.we);
    texture[3] = mlx_load_png(g_inf.ea);
    
    i = 0;
    while (i < 4)
    {
        g_inf.txtr[i].width = texture[i]->width;
        g_inf.txtr[i].height = texture[i]->height;
        get_txtr_pixels(texture[i]->pixels, i);
        i++;  
    }
}
