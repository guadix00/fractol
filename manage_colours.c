/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_colours.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:16:53 by gualvare          #+#    #+#             */
/*   Updated: 2024/11/13 18:32:06 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	*init_colors(void)
{
	int	*colors;

	colors = (int *)malloc(sizeof(int) * 10);
	if (!colors)
		return (NULL);
	colors[0] = 0xFF0000;
	colors[1] = 0x00FF00;
	colors[2] = 0x0000FF;
	colors[3] = 0xFFFF00;
	colors[4] = 0xFF00FF;
	colors[5] = 0x00FFFF;
	colors[6] = 0xFFFFFF;
	colors[7] = 0x000000;
	colors[8] = 0xFFA500;
	colors[9] = 0x800080;
	return (colors);
}

int	get_color(int *colors, int size)
{
	static int	index;
	int			color;

	color = colors[index];
	index = (index + 1) % size;
	return (color);
}

void	free_colors(int *colors)
{
	free(colors);
}

unsigned int	map_iterations_to_color(t_fractal *fractal, int iteration)
{
	double			normalized_value;
	unsigned int	color;

	if (iteration < 0)
		return (fractal->color_s);
	else if (iteration >= fractal->iterations_definition)
		return (fractal->color_e);
	normalized_value = (double)iteration / fractal->iterations_definition;
	color = (unsigned int)((1.0 - normalized_value) * fractal->color_s
			+ normalized_value * fractal->color_e);
	return (color);
}
