/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:22:30 by msodor            #+#    #+#             */
/*   Updated: 2023/08/29 18:25:59 by msodor           ###   ########.fr       */
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

    i = 0;
    g_elems.txtr[idx].texture = malloc(sizeof(uint32_t) * (g_elems.txtr[idx].width * g_elems.txtr[idx].height) / 4);
    while (i < g_elems.txtr[idx].width * g_elems.txtr[idx].height)
    {
        g_elems.txtr[idx].texture[i] = ft_pixel(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
        i += 4;
    }
}
void get_texture()
{
    int i;
    mlx_image_t *texture[4];

    texture[0] = mlx_load_png(g_elems.no);
    texture[1] = mlx_load_png(g_elems.so);
    texture[2] = mlx_load_png(g_elems.we);
    texture[3] = mlx_load_png(g_elems.ea);

    i = 0;    
    while (i < 4)
    {
        g_elems.txtr[i].width = texture[i]->width;
        g_elems.txtr[i].height = texture[i]->height;
        get_txtr_pixels(texture[i]->pixels, i);
        i++;  
    }
}