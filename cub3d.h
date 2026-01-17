/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:09:06 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/16 22:09:06 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_printf/ft_printf.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 900
# define HEIGHT 700
# define MOVE_SPEED 10
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct s_player_position
{
	int					x;
	int					y;
}						t_player_position;

typedef struct s_data
{
	char				**filt_edata;
	char				*file_str;
	int					line_count;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	int					floor[3];
	int					ceiling[3];
	char				**map;
	char				**map_copy;
	int					map_height;
	int					map_width;
	t_player_position	player_position;
	char				player_char;
}						t_data;

void					get_number_of_lines(char *path, t_data *data);
void					check_file_validity(t_data *data, char *file_str);
void					get_filt_edata(t_data *data);
void					extract_textures(t_data *data);
void					extract_floor_and_ceiling(t_data *data);
void					do_premap_elements_exist(t_data *data);
void					extract_map(t_data *data);
void					map_validation(t_data *data);
void					create_map_copy(t_data *data);
void					invoke_flood(t_data *data);
void					init_reset_data(t_data *data);
void					fret_edata(t_data *data);
void					ft_exit_failure(t_data *data, char *msg);
void					validate_textures(t_data *data);
void					check_is_directory(t_data *data, char *texture);
void					check_is_fd_valid(t_data *data, char *texture);
void					check_xpm_extention(t_data *data, char *texture);
void					check_ranges(t_data *data);
int						ends_with(char *s, char *target);
void					get_map_width(t_data *data, int start_index);
void					get_map_height(t_data *data, int start_index);
void					free_matrix(char **matrix);
int						validate_number(char *str);
void					get_ceiling_out_of_matrix(t_data *data, char **matrix);
void					check_cub_extention(t_data *data, char *texture);
void					check_xpm_extention(t_data *data, char *texture);

// execution

typedef struct s_paths
{
	char				*north;
	char				*south;
	char				*east;
	char				*west;
}						t_paths;

typedef struct s_executiondata
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	double				posx;
	double				posy;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;
	t_paths				paths;
	int					c;
	int					f;
	void				*textures[4];
	int					*tex_data[4];
	int					tex_width[4];
	int					tex_height[4];
	t_data				*pdata;
	int					**int_map;
}						t_edata;

typedef struct s_ray
{
	double				camerax;
	double				raydirx;
	double				raydiry;
	int					map_x;
	int					map_y;
	double				sidedistx;
	double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	double				perpwalldist;
	int					stepx;
	int					stepy;
	int					hit;
	int					side;
	int					lineheight;
	int					drawstart;
	int					drawend;
	int					tex;
	int					tex_x;
	int					tex_y;
	double				wallx;
	double				step;
	double				texpos;
}						t_ray;

void					*ft_memset(void *b, int c, size_t len);
int						handle_key(int key, t_edata *d);
void					cleanup_and_exit(t_edata *data);
void					print_map(char **map, int height);
void					init_data(t_edata *data, t_data *pdata);
void					draw_scene_3d(t_edata *d, t_data *p);
void					init_ray(t_ray *r, t_edata *d, int x);
void					init_step(t_ray *r, t_edata *d);
void					perform_dda(t_ray *r, t_data *p);
void					calc_wall(t_ray *r);
void					calc_texture(t_ray *r, t_edata *d);
void					draw_column(t_edata *d, t_ray *r, int x);
int						get_texture_index(t_ray *r);
void					my_pixel_put(t_edata *data, int x, int y, int color);
int						handle_close(t_edata *data);
void					cleanup_and_exit(t_edata *data);
void					my_pixel_put(t_edata *data, int x, int y, int color);
void					init_dirplane(t_edata *d, t_data *pdata);
void					is_valid_map_char(t_data *data);
int						render(t_edata *data);
void					init_textures(t_edata *data, t_data *pdata);

#endif
