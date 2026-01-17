/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_algo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <yofouzi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 23:07:19 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/15 23:19:44 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_wall(t_ray *r)
{
	if (r->side == 0)
		r->perpwalldist = r->sidedistx - r->deltadistx;
	else
		r->perpwalldist = r->sidedisty - r->deltadisty;
	if (r->perpwalldist < 1e-6)
		r->perpwalldist = 1e-6;
	r->lineheight = (int)(HEIGHT / r->perpwalldist);
	r->drawstart = -r->lineheight / 2 + HEIGHT / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + HEIGHT / 2;
	if (r->drawend >= HEIGHT)
		r->drawend = HEIGHT - 1;
}

int	get_texture_index(t_ray *r)
{
	if (r->side == 0)
	{
		if (r->stepx > 0)
			return (WEST);
		return (EAST);
	}
	else
	{
		if (r->stepy > 0)
			return (NORTH);
		return (SOUTH);
	}
}

void	calc_texture(t_ray *r, t_edata *d)
{
	if (r->side == 0)
		r->wallx = d->posy + r->perpwalldist * r->raydiry;
	else
		r->wallx = d->posx + r->perpwalldist * r->raydirx;
	r->wallx -= floor(r->wallx);
	r->tex_x = (int)(r->wallx * d->tex_width[r->tex]);
	if ((r->side == 0 && r->stepx < 0) || (r->side == 1 && r->stepy > 0))
		r->tex_x = d->tex_width[r->tex] - r->tex_x - 1;
}

void	draw_column(t_edata *d, t_ray *r, int x)
{
	int	y;

	r->step = 1.0 * d->tex_height[r->tex] / r->lineheight;
	r->texpos = (r->drawstart - HEIGHT / 2 + r->lineheight / 2) * r->step;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < r->drawstart)
			my_pixel_put(d, x, y, d->c);
		else if (y > r->drawend)
			my_pixel_put(d, x, y, d->f);
		else
		{
			r->tex_y = (int)r->texpos & (d->tex_height[r->tex] - 1);
			r->texpos += r->step;
			my_pixel_put(d, x, y, d->tex_data[r->tex][r->tex_y
				* d->tex_width[r->tex] + r->tex_x]);
		}
		y++;
	}
}

void	draw_scene_3d(t_edata *d, t_data *p)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ft_bzero(&r, sizeof(t_ray));
		init_ray(&r, d, x);
		init_step(&r, d);
		perform_dda(&r, p);
		if (r.hit)
		{
			calc_wall(&r);
			r.tex = get_texture_index(&r);
			calc_texture(&r, d);
			draw_column(d, &r, x);
		}
		x++;
	}
}
