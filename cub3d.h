/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:38:02 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/21 17:49:12 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "./lib/MLX42/include/MLX42/MLX42.h"
#include "./libft/libft.h"

#define HEIGHT						data->mlx->height
#define WIDTH 						data->mlx->width
#define WIDTH_IMG_TITLE 			data->mlx->width * 0.9
#define HEIGHT_IMG_TITLE 			data->mlx->height * 0.4
#define WIDTH_IMG_TITLE_MAP			data->mlx->width
#define HEIGTH_IMG_TITLE_MAP		data->mlx->height
# define HEIGHT_MAP_GAME    (int)(HEIGHT *0.3)
# define WIDTH_MAP_GAME     (int)(WIDTH *0.3)
# define SCALE_X			(WIDTH_MAP_GAME/data->map.width)
# define SCALE_Y			(HEIGHT_MAP_GAME/data->map.height)
# define DIST_FACTOR 0.05 
# define DIST_FACTOR_STEVEN 0.01

# define BUFFER_SIZE 70


# define INPUT_NBR "WRONG NUMBER OF ARGUMENTS\n"
# define INPUT_EXT "Wrong extention"
# define INPUT_OPN "Can't open file or doesn't exist\n"
# define READ_ERR "Can't read file or is empty\n"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RST "\033[0m"
# define YELLOW "\033[0;33m"
# define FOV 60
# define PPC 40
# define MOVE_SPEED 0.05
# define MINIMAP_SCALE 12
# define NORTH 0
# define EAST 1
# define FLOOR 0
# define CEILING 1

typedef enum e_sprites{
	WALL_N,
	WALL_S,
	WALL_E,
	WALL_W,
	PISTOL,
	PISTOL_BANG,
	ENEMY,
	BAULT,
	DOOR,
	SPRITES_COUNT
} t_sprites;

typedef enum e_textures{
	TEX_N,
	TEX_S,
	TEX_E,
	TEX_W,
	TEX_COUNT
} t_textures;

typedef struct s_victor
{
	double	x;
	double	y;
}	t_victor;

typedef struct	s_map
{
	char		*map_s;
	char		**map_a;
	char		*map_sclean;
	char		**map_aclean; // mapa CHAR **
	int			width;  //LARGO
	int			height;	//ALTO
	int			bytes;
	int			ppc;
	int			minimap_scale;
	int			colors[2];
	mlx_t		*mlx;
	mlx_image_t	*img3d;
	mlx_image_t	*mini;
}	t_map;

typedef struct	s_title
{
	mlx_image_t*		title_img;
	mlx_image_t*		title_map;
	mlx_image_t*		start_img;
	char				**TEMP;//modificar al array del mapa real
	char				**arr;//Titulo!!!
	int 				color_up;
	int					flag;
	int					heigth;
	int					length;
	int					screen_width;
	int					screen_heigth;
	float 				boom;
}	t_title;

typedef struct	s_player
{
	t_victor	pos;
	t_victor	vdir;
	t_victor	plane;
	int 		mouse_x;
	int 		mouse_y;
	int			vertical;
	double 		step_v;
	int			step_count;
}	t_player;

typedef struct s_bonus
{
	int 		cell_step_bonus[10];
	int 		current_cell_bonus[10];
	char 		flag_bonus[10];
	int			type_wall_bonus[10];
	float 		distance[10];
	
}	t_bonus;

typedef struct s_cast
{
	float 	ray_length;
	int 	cell_x_step;
	float 	ray_x_start;
	float 	ray_x_direction;
	float 	ray_x_unit_length;
	float 	ray_x_length;
	int 	current_x_cell;
	int 	cell_y_step;
	float 	ray_y_start;
	float 	ray_y_direction;
	float 	ray_y_unit_length;
	float 	ray_y_length;
	int 	current_y_cell;

	int 		cell_step;
	int 		current_cell;
	char 		flag;
	int			type_wall;//1 wall 8 roto 7 zombie
	/*----------------------------------*/
	t_bonus		bonus;
/*------------------------------------------*/
}	t_cast;

typedef struct s_macro_data
{
	t_title			title;
	mlx_t			*mlx;
	t_map			map;
	t_player		player;
	mlx_image_t		*sprites[SPRITES_COUNT];
	mlx_texture_t	*textures[TEX_COUNT];
	char 			*paths[TEX_COUNT];
	bool			bonus;

	/*------VICTOR------*/
	t_cast		cast;
	mlx_image_t* mapp;//************************CAMBIAR NOMBRE A MAP IMAGEN 
	mlx_image_t* game;
	mlx_image_t* wall_img;
	mlx_image_t* broken;
	mlx_image_t* zombie;
	mlx_image_t* grass;
	mlx_image_t* aura;
	double 		px;
	double 		py;
	double 		steven_x;
	double 		steven_y;
	double 		angle_steven;
	double 		angle;
	int			phase;
	//int 		size;
	int			screen_width;  // guarda la ventana para resize
	int			screen_heigth; // guarda la ventana para resize
	
}	t_data;

//RENDER

void ft_draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color);
void drawLineTexture(double x1, double y1, double x2, double y2, int column_texture, t_data *data);

//MAPCHECK
bool	ft_mapcheck(char **argv, t_data *data);
int		ft_check_colors(t_data *data, int line_reached);
int		ft_check_paths(t_data *data, int line_reached);

//PARSING_ELEMENTS
int		ft_parse_elements(t_data *data);
int		ft_check_elements(t_data *data, char **elements);
void	ft_special_abort(char **arr, int len);

//UTILS
void	ft_error(char *err);
void	msg_error(char *err);
void	ft_print_array(char **array);
int		ft_ismap(char *line, char *str);
char	**ft_abort(char **new_array, unsigned int i);

//UTILS2
void	ft_free_maps(t_data *data);
int		ft_arrlen(char **arr);
void	ft_free_textures(t_data *data);

//TEXTURE PARSING
bool	ft_texture_parse(t_data *data, int flag);

//MAPCHECK2
bool	ft_clean_map(t_data *data, int i);
bool	ft_check_chars(t_data *data);

//MAPANAL
bool	ft_map_anal(t_data *data);

//MAPANAL2
void	ft_space_check_aux(t_data *data, int i, int j);

//GAME
void	ft_game(t_data *data);


//MINISPRITES
void	ft_load_minisprites(t_data *data);

//RAY BAN
void	ray_bang(t_data *data);
void	rotate_victor(t_victor *victor, double angle);

//DRAWLINE
void	ft_draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color);

//MOVEMENTS
void	verticals_w(t_data *data);
void	verticals_s(t_data *data);
void	laterals_a(t_data *data);
void	laterals_d(t_data *data);
void	mouse(t_data *data);

//VICTOR
void 	ft_intro(mlx_t*mlx, t_data *data);
void 	draw_title(t_data * data);
void	draw_title_map(t_data *data);
void	ft_intro_loop(t_data		*data);
int		ft_changed_resolution(t_data *data);
void 	drawLine(double x1, double y1, double x2, double y2, int color, mlx_image_t *ptr, t_data *data);
int		set_color(float y, t_data *data);
char	*ft_parse_title(t_data *data);
char 	**ft_skip_sp_arr(char **arr);
void	ft_draw_start_texture(float wallheight, float wallweight, float column, t_data *data);
void 	ft_move_players(t_data *data);
void 	ft_check_door(t_data *data);
double ft_degre_to_radian(double degre);
double radianes_a_grados(double radianes);
void ft_draw_minimap(t_data *data);
void draw_raycast_map(mlx_image_t *map, t_data *data);
float rays(mlx_image_t *map, t_data *data, float angle);
int into_limits(t_data *data);
int get_value_map(t_data *data);
void set_params_colision(int n, t_data *data);
void raycast_game(mlx_image_t *game, t_data *data);
float fix_fish_eye(float distance, float angle, float angle_player);
int last_colision_arr(int *arr);
void drawLineTexture_bonus(double x1, double y1, double y2, int column_texture, t_data *data, int j);
void ft_draw_steven(float wallheight, float column, t_data *data);
void normalize_angle(double *angulo_me, double *angle_steven_from_me);
void ft_draw_steven(float wallheight, float column, t_data *data);
void draw_steven_sprite(t_data *data);

#endif