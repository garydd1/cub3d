/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayban.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:02:13 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/22 21:41:06 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function is used to rotate a victor
 * relative to the origin of the map.
 * receives a vector and an angle in radians
 * modifies x and y of the vector into the new coordinates
 * that the vector will have after rotation.
 * @param victor 
 * @param angle 
 */
void rotate_victor(t_victor *victor, double angle)
{
	double	x;
	double	y;

	x = victor->x;
	y = victor->y;
	victor->x = x * cos(angle * M_PI / 180) - y * sin(angle * M_PI / 180);
	victor->y = x * sin(angle * M_PI / 180) + y * cos(angle * M_PI / 180);
}

void ft_draw_line2(mlx_image_t *img, unsigned int x, int start, unsigned int end, int color, t_data *data, int texx)
{
    if (!img || !img->pixels || !data || !data->sprites[WALL_E] || !data->sprites[WALL_E]->pixels)
        return;

    unsigned int y = start;
    while (y <= end && y < img->height && x < img->width)
    {
        ((uint32_t*)img->pixels)[y * img->width + x] = color;
        y++;
    }

    if (color == 0)
    {
        int texHeight = data->sprites[WALL_E]->height;
        int texWidth = data->sprites[WALL_E]->width;
        y = start;
        while (y <= end && y < img->height && x < img->width)
        {
            int texY = (y - start) * texHeight / (end - start);
            if (texY < 0 || texY >= texHeight || texx < 0 || texx >= texWidth)
            {
                y++;
                continue;
            }

            uint32_t texColor = ((uint32_t*)data->sprites[WALL_E]->pixels)[texY * texWidth + texx];
            if (y >= 0 && y < img->height && x >= 0 && x < img->width)
                ((uint32_t*)img->pixels)[y * img->width + x] = texColor;
            y++;
        }
    }
}

void drawLineTexture_bonus(double x1, double y1, double y2, int column_texture, t_data *data, int j)
{
	double dy;//pantalla y significa WALL-HEIGHT y esta distancia es la que hay que pintar el sprite proporcionalmente
	double steps;
	mlx_image_t* img;
	int row_texture;//textura
	uint32_t color;
	int n;
	float step_y_texture;
	j = 0;
	img = data->sprites[WALL_E];
	steps = fabs(y2 -y1);//
	step_y_texture = (float)img->height/(float)steps;
	dy = 1;//pantalla es 1 pa la textura
	n = 0;
	if (data->ray.perpwalldist < 1)
	{
		// int lineheight = (int)(((data->map.mlx->height)) / data->ray.perpwalldist);
		int lineheight = (int)steps;
		if (lineheight > data->map.mlx->height)
			lineheight = data->map.mlx->height;
		int drawstart = data->map.mlx->height / 2 - lineheight / 2;
		if (drawstart < 0 || drawstart >= data->map.mlx->height)
			drawstart = 0;
		int drawend = lineheight / 2 + data->map.mlx->height / 2;
		if (drawend >= data->map.mlx->height || drawend < 0)
			drawend = data->map.mlx->height;
		double textStep = 1.0 * img->height / lineheight * data->ray.perpwalldist;
		// if (textStep > img->height)
		// 	textStep = img->height;
		int y = drawstart;
		while (y < drawend)
		{
			row_texture = (int)((y - data->map.mlx->height / 2) * textStep + img->height / 2);
			while (row_texture < 0) {
				row_texture += img->height;
			}
			while (row_texture >= (int)img->height) {
				row_texture -= img->height;
			}
			color = ((uint32_t*)img->pixels)[row_texture * img->width + column_texture];
			if(color != 0)
				((uint32_t*)data->map.img3d->pixels)[((int)y1 * data->map.mlx->width + (int)x1)] = color;

			y++;
			y1++;
			n++;
		}
	}else {
	while ((int)fabs(y2 - y1))
	{
		if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= data->map.mlx->height)
		{
			row_texture = floor(step_y_texture * n);
			color = ((uint32_t*)img->pixels)[row_texture * img->width + column_texture];
			if(color != 0)
				((uint32_t*)data->map.img3d->pixels)[((int)y1 * data->map.mlx->width + (int)x1)] = color;
		}
		y1 += dy;
		n++;
	}}
}

// // void drawLineTexture_bonus(t_data *data, int x, t_img *img, int lineheight)
// void drawLineTexture_bonus(double x1, double y1, double y2, int column_texture, t_data *data, int j)
// {
//     // Calculate drawstart and drawend based on player's distance from the wall
// 	mlx_image_t* img;
//     img = data->sprites[WALL_E];
// 	uint32_t color;
// 	int lineheight = (int)(((data->map.mlx->height)) / data->ray.perpwalldist);
// 		if (lineheight > data->map.mlx->height)
// 			lineheight = data->map.mlx->height;
// 		int drawstart = data->map.mlx->height / 2 - lineheight / 2;
// 		if (drawstart < 0 || drawstart >= data->map.mlx->height)
// 			drawstart = 0;
// 		int drawend = lineheight / 2 + data->map.mlx->height / 2;
// 		if (drawend >= data->map.mlx->height || drawend < 0)
// 			drawend = data->map.mlx->height;

//     // Calculate textStep based on player's distance from the wall
//     double textStep = 1.0 * img->height / lineheight * data->ray.perpwalldist;
//     if (textStep > img->height)
//         textStep = img->height;

//     // Draw the texture
// 	y2 = drawend -data->player.step_v;
// 	j = 0;
//   // Calculate the offset based on the player's vertical position
// double offset = (data->player.step_v - data->map.mlx->height / 2) * textStep;

// // Draw the texture
// // Draw the texture
// // Draw the texture
// // Draw the texture
// int n = 0;
// for (int y = drawstart; y < drawend; y++)
// {
//     int row_texture;
//     if (data->ray.perpwalldist < 1) {
//         // When the player is close to the wall, only draw a portion of the texture
//         row_texture = (int)((y - data->map.mlx->height / 2) * textStep + img->height / 2);
//     } else {
//         // When the player is far from the wall, draw the whole texture
//         row_texture = (int)(textStep * n - offset);
//     }
//     while (row_texture < 0) {
//         row_texture += img->height;
//     }
//     while (row_texture >= (int)img->height) {
//         row_texture -= img->height;
//     }
//     // Draw the texture pixel at (x, y) using the color at (column_texture, row_texture)
//     color = ((uint32_t*)img->pixels)[row_texture * img->width + column_texture];
//     if(color != 0)
//         ((uint32_t*)data->map.img3d->pixels)[((int)y1 * data->map.mlx->width + (int)x1)] = color;
   
//     y1++;
//     n++;
// }
// }

void drawLine(double x1, double y1, double x2, double y2, int color, mlx_image_t *ptr)
{
	double dx = x2 - x1;
	double dy =  y2 -y1;
	double steps;

	if ((abs)((int)dx) >= (abs)((int)dy))
		steps = (fabs)(dx);
	else
		steps = (fabs)(dy);
	dx = dx / steps;
	dy = dy / steps;
	while ((int)fabs(x2 - x1) || (int)fabs(y2 - y1))
	{
		if(x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
			mlx_put_pixel(ptr, (int)x1, (int)y1, color);
		x1 += dx;
		y1 += dy;
	}
}
//CCHECKPOINT
void	ray_render(t_data *data)
{
	double	wallx;
	int		texx;
	int		lineheight;
	int		drawstart;
	int		drawend;

	if (data->ray.side == 0)
	{
		data->ray.perpwalldist = (data->ray.sidedistx -  data->ray.deltadistx);
		wallx = data->player.pos.y + data->ray.perpwalldist * data->ray.raydiry;	
		wallx -= floor((wallx));
		texx = (int)(wallx * (double)data->sprites[WALL_E]->width) % (data->sprites[WALL_E]->width);
	}
	else
	{
		data->ray.perpwalldist = (data->ray.sidedisty -  data->ray.deltadisty);
		wallx = data->player.pos.x + data->ray.perpwalldist * data->ray.raydirx;
		wallx -= floor((wallx));
		texx = (int)(wallx * (double)data->sprites[WALL_E]->width) % (data->sprites[WALL_E]->width);
	}
	lineheight = (int)(((data->map.mlx->height)) / data->ray.perpwalldist);
	if (lineheight > data->map.mlx->height)
		lineheight = data->map.mlx->height;
	drawstart = data->map.mlx->height / 2 - lineheight / 2;
	if (drawstart < 0 || drawstart >= data->map.mlx->height)
		drawstart = 0;
	drawend = lineheight / 2 + data->map.mlx->height / 2;
	if (drawend >= data->map.mlx->height || drawend < 0)
		drawend = data->map.mlx->height;
	drawLine(data->ray.x, 0, data->ray.x, drawstart -data->player.step_v, data->map.colors[CEILING], data->map.img3d);
	drawLineTexture_bonus(data->ray.x, drawstart -data->player.step_v, drawend -data->player.step_v, texx, data, 0);
	drawLine(data->ray.x, drawend -data->player.step_v, data->ray.x, data->map.mlx->height, data->map.colors[FLOOR], data->map.img3d);
}

void	ray_checkwall(t_data *data)
{
	while (data->ray.hit == 0)
		{
			if (data->ray.sidedistx < data->ray.sidedisty)
			{
				data->ray.sidedistx += data->ray.deltadistx;
				data->ray.mapx += data->ray.stepx;
				data->ray.side = NORTH;
			}
			else
			{
				data->ray.sidedisty += data->ray.deltadisty;                                                                                                                                
				data->ray.mapy += data->ray.stepy;
				data->ray.side = EAST;
			}
			if (data->ray.mapx >= 0 && data->ray.mapx < data->map.width  && data->ray.mapy >= 0 && data->ray.mapy < data->map.height )
			{
				if (data->map.map_aclean[data->ray.mapy][data->ray.mapx] == '1')
					data->ray.hit = 1;
			}
		}
}

void	ray_checkdir(t_data *data)
{
	if (data->ray.raydirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedistx = (data->player.pos.x - data->ray.mapx) * \
		data->ray.deltadistx;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedistx = (data->ray.mapx + 1.0 - data->player.pos.x) * \
		data->ray.deltadistx;
	}
	if (data->ray.raydiry < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedisty = (data->player.pos.y - data->ray.mapy) * \
		data->ray.deltadisty;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedisty = (data->ray.mapy + 1.0 - data->player.pos.y) * \
		data->ray.deltadisty;
	}
}

/**
 * @brief Here we update
 * the ray direction according to the pixel we are drawing
 * and the player position. 
 * 
 * @param data 
 */
void ray_update(t_data *data)
{	
	data->ray.camerax = 2 * data->ray.x / \
	(double)(data->map.width * data->map.ppc) - 1;
	data->ray.raydirx = data->player.vdir.x + \
	data->player.plane.x * data->ray.camerax;
	data->ray.raydiry =data->player.vdir.y + \
	data->player.plane.y * data->ray.camerax;
	data->ray.mapx = (int)data->player.pos.x;
	data->ray.mapy = (int)data->player.pos.y;
	if (data->ray.raydirx == 0)
		data->ray.raydirx = 0.001;
	if (data->ray.raydiry == 0)
		data->ray.raydiry = 0.001;
	data->ray.deltadistx = fabs(1 / data->ray.raydirx);
	// data->ray.deltadistx = sqrt(1 + (data->ray.raydiry * data->ray.raydiry) / (data->ray.raydirx * data->ray.raydirx));
	data->ray.deltadisty = fabs(1 / data->ray.raydiry);
	// data->ray.deltadisty = sqrt(1 + (data->ray.raydirx * data->ray.raydirx) / (data->ray.raydiry * data->ray.raydiry));
	data->ray.hit = 0;
}
//chekcpoint
void ray_bang(t_data *data)
{
	data->ray.x = 0;
	while (data->ray.x < data->map.mlx->width)
	{
		ray_update(data);
		ray_checkdir(data);
		ray_checkwall(data);
		ray_render(data);
		data->ray.x++;
	}	
}
