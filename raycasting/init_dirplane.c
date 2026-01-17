/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dirplane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:07:36 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/16 22:07:36 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_north(t_edata *d)
{
	d->dirx = 0;
	d->diry = -1;
	d->planex = -0.66;
	d->planey = 0;
}

static void	set_south(t_edata *d)
{
	d->dirx = 0;
	d->diry = 1;
	d->planex = 0.66;
	d->planey = 0;
}

static void	set_east(t_edata *d)
{
	d->dirx = 1;
	d->diry = 0;
	d->planex = 0;
	d->planey = -0.66;
}

static void	set_west(t_edata *d)
{
	d->dirx = -1;
	d->diry = 0;
	d->planex = 0;
	d->planey = 0.66;
}

void	init_dirplane(t_edata *d, t_data *pdata)
{
	if (pdata->player_char == 'N')
		set_north(d);
	else if (pdata->player_char == 'S')
		set_south(d);
	else if (pdata->player_char == 'E')
		set_east(d);
	else if (pdata->player_char == 'W')
		set_west(d);
	else
	{
		ft_printf("Invalid player direction\n");
		cleanup_and_exit(d);
	}
}
