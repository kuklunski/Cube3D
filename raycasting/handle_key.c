/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <yofouzi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 06:14:53 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/15 23:15:22 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_fb(int key, t_edata *d)
{
	double	s;
	double	radius;
	char	**map;

	s = 0.5;
	radius = 0.3;
	map = d->pdata->map;
	if (key == 'w')
	{
		if (map[(int)d->posy][(int)(d->posx + d->dirx
			* (s + radius))] != '1')
			d->posx += d->dirx * s;
		if (map[(int)(d->posy + d->diry * s + d->diry * radius)]
			[(int)d->posx] != '1')
			d->posy += d->diry * s;
	}
	if (key == 's')
	{
		if (map[(int)d->posy][(int)(d->posx - d->dirx
			* (s + radius))] != '1')
			d->posx -= d->dirx * s;
		if (map[(int)(d->posy - d->diry * s - d->diry * radius)]
			[(int)d->posx] != '1')
			d->posy -= d->diry * s;
	}
}

// new_position = position + direction * distance
static void	move_strafe(int key, t_edata *d)
{
	double	s;
	char	**map;

	s = 0.5;
	map = d->pdata->map;
	if (key == 'd')
	{
		if (map[(int)d->posy][(int)(d->posx + d->planex * s)] != '1')
			d->posx += d->planex * s;
		if (map[(int)(d->posy + d->planey * s)][(int)d->posx] != '1')
			d->posy += d->planey * s;
	}
	if (key == 'a')
	{
		if (map[(int)d->posy][(int)(d->posx - d->planex * s)] != '1')
			d->posx -= d->planex * s;
		if (map[(int)(d->posy - d->planey * s)][(int)d->posx] != '1')
			d->posy -= d->planey * s;
	}
}

// rotqtion matrix
static void	rotate(int key, t_edata *d)
{
	double	rs;
	double	old_dx;
	double	old_px;

	rs = 0.2;
	if (key == 65363)
		rs = -rs;
	else if (key != 65361)
		return ;
	old_dx = d->dirx;
	d->dirx = d->dirx * cos(rs) - d->diry * sin(rs);
	d->diry = old_dx * sin(rs) + d->diry * cos(rs);
	old_px = d->planex;
	d->planex = d->planex * cos(rs) - d->planey * sin(rs);
	d->planey = old_px * sin(rs) + d->planey * cos(rs);
}

// Keys:
// ESC        = 65307
// W          = 'w'
// A          = 'a'
// S          = 's'
// D          = 'd'
// Left Arrow = 65361
// Right Arrow= 65363
int	handle_key(int key, t_edata *d)
{
	if (key == 65307)
		cleanup_and_exit(d);
	move_fb(key, d);
	move_strafe(key, d);
	rotate(key, d);
	return (0);
}
