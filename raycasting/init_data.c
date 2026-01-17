/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 22:46:46 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/06 22:46:46 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	rgb_to_hex(int rgb[3])
{
	return (((rgb[0] & 0xFF) << 16) | ((rgb[1] & 0xFF) << 8) | (rgb[2] & 0xFF));
}

static void	null_textures(t_edata *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->textures[i] = NULL;
		data->tex_data[i] = NULL;
		data->tex_width[i] = 0;
		data->tex_height[i] = 0;
		i++;
	}
}

void	init_data(t_edata *data, t_data *pdata)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->posx = pdata->player_position.x + 0.5;
	data->posy = pdata->player_position.y + 0.5;
	init_dirplane(data, pdata);
	data->c = rgb_to_hex(pdata->ceiling);
	data->f = rgb_to_hex(pdata->floor);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	null_textures(data);
	data->pdata = pdata;
}
