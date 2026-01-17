/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:33:49 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/16 23:33:49 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_map_height(t_data *data, int start_index)
{
	int	i;
	int	j;
	int	map_height;

	i = start_index;
	j = start_index;
	map_height = 0;
	while (data->filt_edata[i])
		i++;
	map_height = i - j;
	data->map_height = map_height;
}

void	get_map_width(t_data *data, int start_index)
{
	int	i;
	int	j;
	int	max_width;
	int	cur_width;
	int	mwi;

	i = start_index;
	j = start_index;
	max_width = 0;
	cur_width = 0;
	mwi = 0;
	while (data->filt_edata[i])
	{
		cur_width = ft_strlen(data->filt_edata[i]);
		if (cur_width > max_width)
		{
			max_width = cur_width;
			mwi = i;
		}
		i++;
	}
	mwi -= j;
	data->map_width = max_width;
}
