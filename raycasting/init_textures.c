/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:10:07 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/17 21:10:07 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	load_texture(t_edata *data, int id, char *path)
{
	int	bpp;
	int	size_line;
	int	endian;

	data->textures[id] = mlx_xpm_file_to_image(data->mlx, path,
			&data->tex_width[id], &data->tex_height[id]);
	if (!data->textures[id])
	{
		ft_printf("Error: failed to load texture id %d\n", id);
		cleanup_and_exit(data);
		exit(1);
	}
	data->tex_data[id] = (int *)mlx_get_data_addr(data->textures[id], &bpp,
			&size_line, &endian);
}

void	init_textures(t_edata *data, t_data *pdata)
{
	char	*paths[4];

	paths[NORTH] = pdata->no_texture;
	paths[SOUTH] = pdata->so_texture;
	paths[EAST] = pdata->ea_texture;
	paths[WEST] = pdata->we_texture;
	load_texture(data, NORTH, paths[NORTH]);
	load_texture(data, SOUTH, paths[SOUTH]);
	load_texture(data, EAST, paths[EAST]);
	load_texture(data, WEST, paths[WEST]);
}
