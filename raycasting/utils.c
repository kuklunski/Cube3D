/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mypixel_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 23:45:47 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/06 23:45:47 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_pixel_put(t_edata *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	cleanup_and_exit(t_edata *data)
{
	int	i;

	if (!data)
		exit(0);
	i = 0;
	while (i < 4)
	{
		if (data->textures[i])
			mlx_destroy_image(data->mlx, data->textures[i]);
		i++;
	}
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->pdata)
		fret_edata(data->pdata);
	exit(0);
}

int	handle_close(t_edata *data)
{
	cleanup_and_exit(data);
	return (0);
}
