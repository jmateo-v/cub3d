/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:06:04 by dogs              #+#    #+#             */
/*   Updated: 2026/01/10 20:52:29 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"
#include "MLX42.h"
#include "math.h"

#define WIDTH 800
#define HEIGHT 600
#define MOVE_SPEED 0.05
#define ROTATE_SPEED 0.05

// ERROR MESSAGES

#define ERR_MLX_INIT "Error failed to initialize MLX"
#define ERR_FRAME_INIT "Error: failed to create frame buffer"
#define ERR_IMG_TO_WIN "Error: failed to attach image to window"
#define ERR_TEXTURE_INIT "Error: failed to load textures"

typedef struct s_map
{
    char    **grid;
    int width;
    int height;
    uint32_t floor_color;
    uint32_t ceiling_color;
    char    *tex_n;
    char    *tex_s;
    char    *tex_w;
    char    *tex_e;
} t_map;

typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
}   t_player;

typedef struct s_ray
{
    double dir_x;
    double dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    bool hit;
    int side;
    double perp_wall_dist;
}   t_ray;

typedef struct s_game
{
    mlx_t *mlx;
    mlx_image_t *frame;
    t_map map;
    t_player player;
    t_ray ray;
    mlx_texture_t *tex_n;
    mlx_texture_t *tex_s;
    mlx_texture_t *tex_w;
    mlx_texture_t *tex_e;
    bool    key_w;
    bool    key_s;
    bool    key_a;
    bool    key_d;
    bool    key_left;
    bool    key_right;
}   t_game;

void    init_game(t_game *g);
void    init_hooks(t_game *g);
void handle_keys(mlx_key_data_t keydata, void *param);
void game_loop(void *param);
void move_foward(t_game *g);
void move_backwards(t_game *g);
void move_left(t_game *g);
void move_right(t_game *g);
void rotate_left(t_game *g);
void rotate_right(t_game *g);
void	render_frame(t_game *g);
void cast_rays(t_game *g);
void cast_single_ray(t_game *g, int x);
void compute_ray_dir(t_game *g, int x);
void compute_delta_dist(t_game *g);
void compute_step_and_side_dist(t_game *g);
void run_dda(t_game *g);
void compute_wall_dist(t_game *g);
void draw_wall_slice(t_game *g, int x);
void error_exit(const char *msg);
bool is_bounded(t_game *g, int x, int y);
void cleanup(t_game *g);
void close_game(void *param);
#endif