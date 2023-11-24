/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:41:11 by dgarizad          #+#    #+#             */
/*   Updated: 2023/11/24 18:21:16 by vcereced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//DELETE THIS AT THE END OF THE PROJECT
void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putstr_fd(array[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
//DELETE THIS AT THE END OF THE PROJECT

/**
 * @brief This function is used to free all the pointers allocated
 * in the data structure regarding the map.
 * 
 * @param data 
 */
void	ft_free_maps(t_data *data)
{
	free(data->map.map_s);
	ft_abort(data->map.map_a, ft_arrlen(data->map.map_a));
	free(data->map.map_sclean);
	ft_abort(data->map.map_aclean, ft_arrlen(data->map.map_aclean));
}

/**
 * @brief Textures are allocated in the mlx_load_png function
 * and then converted to images in the mlx_texture_to_image function.
 * they also allocate memory for the pixels.
 * 
 * @param data 
 */
void	ft_free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < SPRITES_COUNT)
	{
		if (data->textures[i])
		{
			free(data->textures[i]->pixels);
			free(data->textures[i]);
		}
		i++;
	}
}
