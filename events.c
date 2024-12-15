/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:16:16 by gualvare          #+#    #+#             */
/*   Updated: 2024/11/13 18:16:18 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_con, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_con, fractal->mlx_win);
	mlx_destroy_display(fractal->mlx_con);
	free(fractal->mlx_con);
	exit(EXIT_SUCCESS);
}

static void	change_colors(t_fractal *fractal)
{
	int	*colors;

	colors = init_colors();
	if (!colors)
		return ;
	fractal->color_s = get_color(colors, 10);
	fractal->color_e = get_color(colors, 10);
	fractal->color_f = get_color(colors, 10);
	free_colors(colors);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == 65453)
		fractal->zoom *= 1.05;
	else if (keysym == 65451)
		fractal->zoom *= 0.95;
	else if (keysym == XK_1)
		fractal->iterations_definition += 10;
	else if (keysym == XK_2)
		fractal->iterations_definition -= 10;
	else if (keysym == 32)
		change_colors(fractal);
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	double	mouse_x_fractal;
	double	mouse_y_fractal;
	double	zoom_factor;

	zoom_factor = 1;
	mouse_x_fractal = (map(x, fractal) * fractal->zoom) + fractal->shift_x;
	mouse_y_fractal = (map(y, fractal) * fractal->zoom) + fractal->shift_y;
	if (button == Button5)
		zoom_factor = 1.05;
	else if (button == Button4)
		zoom_factor = 0.95;
	else
		return (0);
	fractal->zoom *= zoom_factor;
	fractal->shift_x = mouse_x_fractal - (map(x, fractal) * fractal->zoom);
	fractal->shift_y = mouse_y_fractal - (map(y, fractal) * fractal->zoom);
	fractal_render(fractal);
	return (0);
}
