/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_algo2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 23:41:55 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/06 23:41:55 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_ray *r, t_edata *d, int x)
{
	r->camerax = 2 * x / (double)WIDTH - 1;
	r->raydirx = d->dirx + d->planex * r->camerax;
	r->raydiry = d->diry + d->planey * r->camerax;
	r->map_x = (int)d->posx;
	r->map_y = (int)d->posy;
	r->deltadistx = fabs(1 / r->raydirx);
	r->deltadisty = fabs(1 / r->raydiry);
}

void	init_step(t_ray *r, t_edata *d)
{
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (d->posx - r->map_x) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->map_x + 1.0 - d->posx) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (d->posy - r->map_y) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->map_y + 1.0 - d->posy) * r->deltadisty;
	}
}

void	perform_dda(t_ray *r, t_data *p)
{
	while (!r->hit)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->map_x += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->map_y += r->stepy;
			r->side = 1;
		}
		if (r->map_y < 0 || r->map_y >= p->map_height)
			return ;
		if (r->map_x < 0 || r->map_x >= (int)ft_strlen(p->map[r->map_y]))
			return ;
		if (p->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}
