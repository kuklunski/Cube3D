/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:09:15 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/16 22:09:15 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: think about when to exit and when to return -1
// when an error that demands closing the program is met
// just exit, but make sure to have that inside a function that makes
// sure everything that needs to be freed is freed.

// void	debug_printf(t_data *d)
// {
// 	printf("file_str: %s\n", d->file_str ? "true" : "false");
// 	printf("filt_edata: %s\n", d->filt_edata ? "true" : "false");
// 	printf("NO: %s\n", d->no_texture);
// 	printf("SO: %s\n", d->so_texture);
// 	printf("WE: %s\n", d->we_texture);
// 	printf("EA: %s\n", d->ea_texture);
// 	printf("F: %d %d %d\n", d->floor[0], d->floor[1], d->floor[2]);
// 	printf("C: %d %d %d\n", d->ceiling[0], d->ceiling[1], d->ceiling[2]);
// }

// void	print_map(char **map, int height)
// {
// 	int		x;
// 	char	c;

// 	for (int y = 0; y < height; y++)
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			c = map[y][x];
// 			if (c == ' ')
// 				putchar('s');
// 			else
// 				putchar(c);
// 			x++;
// 		}
// 		putchar('\n');
// 	}
// }

//void	parsing(char *file_str, t_data *data)
// {
// 	init_reset_data(data);
// 	data->file_str = file_str;
// 	check_file_validity(data, file_str);
// 	get_number_of_lines(file_str, data);
// 	get_filt_edata(data);
// 	extract_textures(data);
//   validate_textures(data);
// 	extract_floor_and_ceiling(data);
// 	check_ranges(data);
// 	do_premap_elements_exist(data);
//   printf("--------------- pre map stop sign --------------------\n");
// 	extract_map(data);
//   print_map(data->map, data->map_height);
//   map_validation(data);
//   printf("{+} stop sign\n");
//   printf("--------------- we got here sign --------------------\n");
// 	create_map_copy(data);
// 	invoke_flood(data);
// 	printf("map height : %d, map width : %d\n", data->map_height,
// 		data->map_width);
// 	printf("x : %d, y : %d\n", data->player_position.x,
// 		data->player_position.y);
// 	print_map(data->map_copy, data->map_height);
//   //debug_printf(data);
// 	// fret_edata(data);
// }

void	parsing(char *file_str, t_data *data)
{
	init_reset_data(data);
	data->file_str = file_str;
	check_file_validity(data, file_str);
	get_number_of_lines(file_str, data);
	get_filt_edata(data);
	extract_textures(data);
	validate_textures(data);
	extract_floor_and_ceiling(data);
	check_ranges(data);
	do_premap_elements_exist(data);
	extract_map(data);
	map_validation(data);
	create_map_copy(data);
	invoke_flood(data);
}

int	render(t_edata *data)
{
	ft_memset(data->addr, 0, HEIGHT * data->line_length);
	draw_scene_3d(data, data->pdata);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

// 

// pdata for parsing data
// edata for execution data
int	main(int argc, char **argv)
{
	char	*file_str;
	t_data	pdata;
	t_edata	edata;

	if (argc != 2)
	{
		printf("{-} Wrong Number of Args!\n");
		exit(1);
	}
	file_str = argv[1];
	parsing(file_str, &pdata);
	ft_printf("{+} parsing status: SUCCESS...\n");
	init_data(&edata, &pdata);
	init_textures(&edata, &pdata);
	mlx_loop_hook(edata.mlx, render, &edata);
	mlx_key_hook(edata.win, handle_key, &edata);
	mlx_hook(edata.win, 17, 0, handle_close, &edata);
	mlx_loop(edata.mlx);
	return (0);
}
