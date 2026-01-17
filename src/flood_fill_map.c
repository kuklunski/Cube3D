/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:31:35 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/17 21:05:30 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_map_copy(t_data *data)
{
	int	i;

	i = 0;
	data->map_copy = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map_copy)
		ft_exit_failure(data, "{-} Failed to allocate memory for map copy!");
	data->map_copy[data->map_height] = NULL;
	while (data->map && data->map[i])
	{
		data->map_copy[i] = ft_strdup(data->map[i]);
		if (!data->map[i])
			ft_exit_failure(data, "{-} Failed to allocate memory for map row");
		i++;
	}
}
// TODO: check if spaces are inside the map either newline or ' '
// this is not a problem because it's out of bonds for the
// player so we can argue that i treated it like a space
// i only treated it as invalid if it's in the bounds of the player himself
// found the fix i just need to make sure that 0 is
// not at the start of anything or at the end of anything!
// TODO:
//
// i think this is it
// at the endge of each wall, there should be no leaks
// as in no 0 at the end

int	leak_found(t_data *data, int pos_y, int pos_x)
{
	char	*line;

	line = data->map_copy[pos_y];
	if ((pos_x == ft_strlen(line) - 1) && data->map_copy[pos_y][pos_x] != '1')
	{
		ft_exit_failure(data, "{-} Error, leak found on the map's edge! 1");
		return (0);
	}
	if (pos_x == 0 && data->map_copy[pos_y][pos_x] != '1')
	{
		ft_exit_failure(data, "{-} Error, leak found on the map's edge! 2");
		return (0);
	}
	if ((pos_y == data->map_height - 1) && data->map_copy[pos_y][pos_x] != '1')
	{
		ft_exit_failure(data, "{-} Error, leak found on the map's edge! 3");
		return (0);
	}
	if (pos_y == 0 && data->map_copy[pos_y][pos_x] != '1')
	{
		ft_exit_failure(data, "{-} Error, leak found on the map's edge! 4");
		return (0);
	}
	return (0);
}

void	flood_fill(t_data *data, int pos_x, int pos_y, char player_char)
{
	if ((pos_x < 0 || pos_y < 0) || (pos_x >= data->map_width - 1)
		|| (pos_y >= data->map_height))
		return ;
	if (data->map_copy[pos_y][pos_x] == '1'
		|| data->map_copy[pos_y][pos_x] == 'X')
		return ;
	if (data->map_copy[pos_y][pos_x] == ' '
		|| data->map_copy[pos_y][pos_x] == '\0' || leak_found(data, pos_y,
			pos_x))
		ft_exit_failure(data, "{-} Error , leak found on the maps edge! 5");
	data->map_copy[pos_y][pos_x] = 'X';
	flood_fill(data, pos_x + 1, pos_y, player_char);
	flood_fill(data, pos_x - 1, pos_y, player_char);
	flood_fill(data, pos_x, pos_y - 1, player_char);
	flood_fill(data, pos_x, pos_y + 1, player_char);
}

void	invoke_flood(t_data *data)
{
	int	pos_x;
	int	pos_y;

	pos_x = data->player_position.x;
	pos_y = data->player_position.y;
	flood_fill(data, pos_x, pos_y, data->player_char);
}
