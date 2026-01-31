/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:06:04 by dogs              #+#    #+#             */
/*   Updated: 2026/01/31 15:54:43 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#include "libft.h"
#include "get_next_line.h"
#include "MLX42.h"
#include <math.h>
#include <fcntl.h>

#define WIDTH 800
#define HEIGHT 600
#define MOVE_SPEED 0.05
#define ROTATE_SPEED 0.05
#define MOUSE_ROT_SPEED 0.025
#define PADDING 0.2
#define MM_SCALE 12
#define MM_WALL 0x44444455
#define MM_FLOOR 0xAAAAAA55
#define MM_DOOR 0xFFD70055
#define PLAYER_COLOR 0x00FFFF88
#define DOOR_SPEED 4.5f
#define INTERACT_REACH 2.25f
#define DELTA_TIME 0.016f

// ERROR MESSAGES

#define ERR_MLX_INIT "Error: failed to initialize MLX"
#define ERR_FRAME_INIT "Error: failed to create frame buffer"
#define ERR_IMG_TO_WIN "Error: failed to attach image to window"
#define ERR_TEXTURE_INIT "Error: failed to load textures"
#define ERR_DOOR_MALLOC "Error: malloc failed at init_doors"
#define ERR_SPRITE_MALLOC "Error: malloc failed at init_sprites"
#define ERR_ARG_COUNT "Error: input only one argument (the map)"
#define ERR_VALID_FILE "Error: map must end in .cub and be accessible"
#define ERR_VALID_CHARS "Error: invalid chars detected in file"
#define ERR_NO_TEXTURE "Error: empty or duplicated texture"
#define ERR_TEXTURE_MALLOC "Error: malloc failed saving textures"
#define ERR_VALID_TEXTURE "Error: invalid texture"
#define ERR_NO_COLOR "Error: empty or duplicated color"
#define ERR_VALID_COLOR "Error: invalid color"
#define ERR_MAP_MALLOC "Error: malloc failed copying map"
#define ERR_VALID_MAP "Error: invalid values detected in map"
#define ERR_MORE_PLAYER "Error: more than one player found"
#define ERR_NO_PLAYER "Error: no player character found"
#define ERR_MISSING_VALS "Error: missing textures/colors"

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

typedef struct s_door
{
    int x;
    int y;
    bool open;
    int orientation;
    float prog;
    float speed;
} t_door;

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
    bool hit_door;
    int door_index;
    bool draw_door;
    bool door_is_hit_tile;
}   t_ray;

typedef struct s_slice
{
    int start;
    int end;
    int tex_x;
    int tex_y;
    int line_h;
}   t_slice;

typedef struct s_anim
{
    mlx_image_t *frames[5];
    int frame_count;
    int current;
    int timer;
}   t_anim;

typedef struct s_sprite
{
    int x;
    int y;
    t_anim anim;
} t_sprite;

typedef struct s_sprctx
{
    int         i;
    t_sprite    *s;
    t_anim      *a;
    double      tx;
    double      ty;
    int         dx;
    int         dy;
    mlx_image_t *img;
}   t_sprctx;


typedef struct	s_parse
{
	int	file_fd;
	char	**arr_file;
	int	floor_r;
	int	floor_g;
	int	floor_b;
	int	ceiling_r;
	int	ceiling_g;
	int	ceiling_b;
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	f;
	bool	c;
	bool	map;
}	t_parse;

typedef struct s_game
{
    mlx_t *mlx;
    mlx_image_t *frame;
    mlx_image_t *minimap;
	t_parse	parse;
    t_map map;
    t_player player;
    t_ray ray;
    mlx_texture_t *tex_n;
    mlx_texture_t *tex_s;
    mlx_texture_t *tex_w;
    mlx_texture_t *tex_e;
    mlx_texture_t *tex_d;
    t_door  *doors;
    int n_doors;
    int last_mouse_x;
    t_sprite *sprites;
    int n_sprites;
}   t_game;

void    init_game(t_game *g, int argc, char **argv);
void	init_map(t_game *g);
void	init_player(t_game *g, int x, int y, int pos);
void init_doors(t_game *g);
void    init_hooks(t_game *g);
void handle_keys(mlx_key_data_t keydata, void *param);
void game_loop(void *param);
void move_foward(t_game *g);
void move_backwards(t_game *g);
void move_left(t_game *g);
void move_right(t_game *g);
void rotate_camera(t_game *g, double angle);
void interact(t_game *g);
void	render_frame(t_game *g);
void cast_rays(t_game *g);
void cast_single_ray(t_game *g, int x);
void compute_ray_dir(t_game *g, int x);
void compute_delta_dist(t_game *g);
void compute_step_and_side_dist(t_game *g);
void run_dda(t_game *g);
void compute_wall_dist(t_game *g);
void draw_wall_slice(t_game *g, int x);
void	draw_minimap(t_game *g);
void error_exit(const char *msg);
bool is_bounded(t_game *g, int x, int y);
bool is_wall(t_game *g, double x, double y);
bool is_door_closed(t_game *g, int x, int y);
int find_door_index(t_game *g, int x, int y);
void cleanup(t_game *g);
void close_game(void *param);
void update_doors(t_game *g, float dt);
void update_mouse(t_game *g);
void init_anim(mlx_t *mlx, t_anim *anim);
void init_sprites(t_game *g);
void anim_sprites(t_game *g);
void render_sprites(t_game *g);

//PARSING

void	initial_parsing(t_game *g, int argc, char **argv);
int	copy_file(t_parse *parse);
int	check_valid_file(char *str, t_parse *parse);
void	init_parse(t_game *g);
void	verify_line(t_game *g, char *line, int pos);
void	verify_texture(t_game *g, char *line, int *i);
void	verify_colors(t_game *g, char *line, int *i);
void	verify_map(t_game *g, int pos);
void	obtain_ceiling_colors(t_game *g, char *line, int *i);
void	obtain_floor_colors(t_game *game, char *line, int *i);
void	save_colors(t_game *g, char *color, int *found, int location);
void	copy_tmp_map(t_game *g, int pos);
int	get_array_len(char **array);
int	alt_atoi(char *str, int *num);
char	*alt_strjoin(char const *s1, char const *s2);

#endif
