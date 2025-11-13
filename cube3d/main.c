/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:02:59 by ylemkere          #+#    #+#             */
/*   Updated: 2025/11/05 20:02:59 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  init t_paths  paths;
//  void    *textures[4];

#include "cube3d.h"

int map[MAP_W][MAP_H]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

void my_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

static void cleanup_and_exit(t_data *data)
{
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    exit(0);
}

int handle_close(t_data *data)
{
    cleanup_and_exit(data);
    return (0);
}

int handle_key(int key, t_data *d)
{
    double moveSpeed = 0.5;
    double rotSpeed = 0.2;

    if (key == 65307)
        cleanup_and_exit(d);
    // --- MOVE FORWARD ---
    if (key == 'w')
    {
        if (map[(int)(d->posY)][(int)(d->posX + d->dirX * moveSpeed)] == 0)
            d->posX += d->dirX * moveSpeed;
        if (map[(int)(d->posY + d->dirY * moveSpeed)][(int)(d->posX)] == 0)
            d->posY += d->dirY * moveSpeed;
    }
    // --- MOVE BACKWARD ---
    if (key == 's')
    {
        if (map[(int)(d->posY)][(int)(d->posX - d->dirX * moveSpeed)] == 0)
            d->posX -= d->dirX * moveSpeed;
        if (map[(int)(d->posY - d->dirY * moveSpeed)][(int)(d->posX)] == 0)
            d->posY -= d->dirY * moveSpeed;
    }
    // --- STRAFE RIGHT (D) ---
    if (key == 'd')
    {
        double strafeX = d->dirY;
        double strafeY = -d->dirX;
        if (map[(int)(d->posY)][(int)(d->posX + strafeX * moveSpeed)] == 0)
            d->posX += strafeX * moveSpeed;
        if (map[(int)(d->posY + strafeY * moveSpeed)][(int)(d->posX)] == 0)
            d->posY += strafeY * moveSpeed;
    }
    // --- STRAFE LEFT (A) ---
    if (key == 'a')
    {
        double strafeX = -d->dirY;
        double strafeY = d->dirX;
        if (map[(int)(d->posY)][(int)(d->posX + strafeX * moveSpeed)] == 0)
            d->posX += strafeX * moveSpeed;
        if (map[(int)(d->posY + strafeY * moveSpeed)][(int)(d->posX)] == 0)
            d->posY += strafeY * moveSpeed;
    }
    if (key == 65363)         // LEFT
    {
        double oldDirX = d->dirX;
        d->dirX = d->dirX * cos(-rotSpeed) - d->dirY * sin(-rotSpeed);
        d->dirY = oldDirX * sin(-rotSpeed) + d->dirY * cos(-rotSpeed);
        double oldPlaneX = d->planeX;
        d->planeX = d->planeX * cos(-rotSpeed) - d->planeY * sin(-rotSpeed);
        d->planeY = oldPlaneX * sin(-rotSpeed) + d->planeY * cos(-rotSpeed);
    }
    if (key == 65361)         // RIGHT
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = d->dirX;
      d->dirX = d->dirX * cos(rotSpeed) - d->dirY * sin(rotSpeed);
      d->dirY = oldDirX * sin(rotSpeed) + d->dirY * cos(rotSpeed);
      double oldPlaneX = d->planeX;
      d->planeX = d->planeX * cos(rotSpeed) - d->planeY * sin(rotSpeed);
      d->planeY = oldPlaneX * sin(rotSpeed) + d->planeY * cos(rotSpeed);
    }
    return (0);
}



void draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
    for (int y = start; y < end; y++)
        my_pixel_put(data, x, y, color);
}

void init_textures(t_data *data)
{
    int bpp, size_line, endian;

    // NORTH
    data->textures[NORTH] = mlx_xpm_file_to_image(
        data->mlx, NORTH_path,
        &data->tex_width[NORTH], &data->tex_height[NORTH]
    );
    if (!data->textures[NORTH])
        printf("Failed to load texture NORTH\n"), exit(1);
    data->tex_data[NORTH] = (int *)mlx_get_data_addr(
        data->textures[NORTH], &bpp, &size_line, &endian
    );
    printf("loaded texture\n");

    // SOUTH
    data->textures[SOUTH] = mlx_xpm_file_to_image(
        data->mlx, SOUTH_path,
        &data->tex_width[SOUTH], &data->tex_height[SOUTH]
    );
    if (!data->textures[SOUTH])
        printf("Failed to load texture SOUTH\n"), exit(1);
    data->tex_data[SOUTH] = (int *)mlx_get_data_addr(
        data->textures[SOUTH], &bpp, &size_line, &endian
    );
    printf("loaded texture\n");

    // EAST
    data->textures[EAST] = mlx_xpm_file_to_image(
        data->mlx, EAST_path,
        &data->tex_width[EAST], &data->tex_height[EAST]
    );
    if (!data->textures[EAST])
        printf("Failed to load texture EAST\n"), exit(1);
    data->tex_data[EAST] = (int *)mlx_get_data_addr(
        data->textures[EAST], &bpp, &size_line, &endian
    );
    printf("loaded texture\n");

    // WEST
    data->textures[WEST] = mlx_xpm_file_to_image(
        data->mlx, WEST_path,
        &data->tex_width[WEST], &data->tex_height[WEST]
    );
    if (!data->textures[WEST])
        printf("Failed to load texture WEST\n"), exit(1);
    data->tex_data[WEST] = (int *)mlx_get_data_addr(
        data->textures[WEST], &bpp, &size_line, &endian
    );
    printf("loaded texture\n");
}



void draw_scene_3d(t_data *data)
{
    int x = 0;
    while (x < WIDTH)
    {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        int mapX = (int)data->posX;
        int mapY = (int)data->posY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);

        double sideDistX;
        double sideDistY;

        int stepX, stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
        }

        // --- DDA ---
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map[mapY][mapX] > 0)
                hit = 1;
        }

        double perpWallDist;
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;

        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        /*****************************************************************/
        int textureIndex;
        if (side == 0) // hit a vertical wall
            textureIndex = (rayDirX > 0) ? WEST : EAST;
        else           // hit a horizontal wall
            textureIndex = (rayDirY > 0) ? NORTH : SOUTH;

        double wallX; // where exactly the wall was hit
        if (side == 0)
            wallX = data->posY + perpWallDist * rayDirY;
        else
            wallX = data->posX + perpWallDist * rayDirX;
        wallX = wallX - (int)wallX; // only keep the fractional part (0.0 - 1.0)

        int texX = (int)(wallX * (double)data->tex_width[textureIndex]);
        if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
            texX = data->tex_width[textureIndex] - texX - 1;

        double step = 1.0 * data->tex_height[textureIndex] / lineHeight;
        double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

        int y = 0;
        while (y < HEIGHT)
        {
            if (y < drawStart)
                my_pixel_put(data, x, y, data->c);
            else if (y > drawEnd)
                my_pixel_put(data, x, y, data->f);
            else
            {
                // Wall texture
                int texY = (int)texPos;
                if (texY >= data->tex_height[textureIndex])
                    texY = data->tex_height[textureIndex] - 1;
                texPos += step;

                int color = data->tex_data[textureIndex][texY * data->tex_width[textureIndex] + texX];
                my_pixel_put(data, x, y, color);
            }
            y++;
        }
        x++;
    }
}

void draw_minimap(t_data *data)
{
int tile = 10;
    
    int y = 0;
    while (y < MAP_H)
    {
        int x = 0;
        while (x < MAP_W)
        {
            int color = map[y][x] ? 0x555555 : 0x222222;
            int py = 0;
            while (py < tile)
            {
                int px = 0;
                while (px < tile)
                {
                    my_pixel_put(data, x * tile + px, y * tile + py, color);
                    px++;
                }
                py++;
            }
            x++;
        }
        y++;
    }
    // Player position on minimap
    int px = data->posX * tile;
    int py = data->posY * tile;
    int i = -2;
    while (i <= 2)
    {
        int j = -2;
        while (j <= 2)
        {
            my_pixel_put(data, px + i, py + j, 0xFFFFFF);
            j++;
        }
        i++;
    }
}


int render(t_data *data)
{
    ft_memset(data->addr, 0, HEIGHT * data->line_length);
    draw_scene_3d(data);
    draw_minimap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

void init_data(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");

    // Player starting position and direction
    data->posX = 4.5;
    data->posY = 4.5;
    data->dirX = -1;
    data->dirY = 0;
    data->planeX = 0;
    data->planeY = 0.66;

    // Ceiling and floor colors (0xRRGGBB)
    data->c = 0x87CEEB;
    data->f = 0x228B22;

    // Create main image
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img,
                                   &data->bits_per_pixel,
                                   &data->line_length,
                                   &data->endian);

    // zero out textures pointers
    for (int i = 0; i < 4; i++)
    {
        data->textures[i] = NULL;
        data->tex_data[i] = NULL;
        data->tex_width[i] = 0;
        data->tex_height[i] = 0;
    }
}


int main(void)
{
    t_data data;

    init_data(&data);
    init_textures(&data);
    mlx_loop_hook(data.mlx, render, &data);
    mlx_key_hook(data.win, handle_key, &data);
    mlx_hook(data.win, 17, 0, handle_close, &data);
    mlx_loop(data.mlx);
}
