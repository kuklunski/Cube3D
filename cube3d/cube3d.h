/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:01:27 by ylemkere          #+#    #+#             */
/*   Updated: 2025/11/05 20:01:27 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 700
#define MOVE_SPEED 10
#define MAP_W 24
#define MAP_H 24
#define NORTH_path "wolftex/pics/wood.xpm"
#define SOUTH_path "wolftex/pics/redbrick.xpm"
#define EAST_path "wolftex/pics/eagle.xpm"
#define WEST_path "wolftex/pics/mossy.xpm"
#define NORTH   0
#define SOUTH   1
#define EAST    2
#define WEST    3

typedef struct s_paths
{
    char    *north;
    char    *south;
    char    *east;
    char    *west;
}   t_paths;

typedef struct s_data 
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    double     posX;
    double     posY;
    int bits_per_pixel;
    int line_length;
    int endian;
    double  dirX;
    double  dirY;
    double  planeX;
    double  planeY;
    t_paths  paths;
    int c;
    int f;
    void    *textures[4];
    int     *tex_data[4];
    int     tex_width[4];
    int     tex_height[4];
}   t_data;

void    *ft_memset(void *b, int c, size_t len);

#endif