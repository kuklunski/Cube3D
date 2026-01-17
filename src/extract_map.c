/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:36:35 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/16 23:36:35 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_config_line(char *line)
{
	if (ft_strnstr(line, "NO ", ft_strlen(line)) || ft_strnstr(line, "EA ",
			ft_strlen(line)) || ft_strnstr(line, "SO ", ft_strlen(line))
		|| ft_strnstr(line, "WE ", ft_strlen(line)))
	{
		return (1);
	}
	if (ft_strnstr(line, "F ", ft_strlen(line)) || ft_strnstr(line, "C ",
			ft_strlen(line)))
	{
		return (1);
	}
	return (0);
}

int	not_map_line(char *line)
{
	if (is_config_line(line) || ft_strlen(line) < 3 || line[0] == '\n')
		return (1);
	return (0);
}

int	return_map_index(t_data *data)
{
	int	i;

	i = 0;
	while (data->filt_edata[i] && not_map_line(data->filt_edata[i]))
		i++;
	return (i);
}

void	rm_newline_from_map_lines(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map && data->map[i])
	{
		j = 0;
		while (data->map[i][j] && data->map[i][j] != '\0')
		{
			if (data->map[i][j] == '\n')
				data->map[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	extract_map(t_data *data)
{
	int	start_index;
	int	i;
	int	j;

	start_index = return_map_index(data);
	i = start_index;
	get_map_width(data, start_index);
	get_map_height(data, start_index);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		ft_exit_failure(data, "map allocation failed!");
	data->map[data->map_height] = NULL;
	j = 0;
	while (data->filt_edata[i])
	{
		data->map[j] = ft_strdup(data->filt_edata[i]);
		if (!data->map[j])
			ft_exit_failure(data, "map allocation failed!");
		i++;
		j++;
	}
	rm_newline_from_map_lines(data);
}
