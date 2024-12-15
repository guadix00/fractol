/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:16:38 by gualvare          #+#    #+#             */
/*   Updated: 2024/11/13 18:29:25 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mlx_error(t_fractal *fractal)
{
	if (fractal)
	{
		if (fractal->img.img_ptr)
			mlx_destroy_image(fractal->mlx_con, fractal->img.img_ptr);
		if (fractal->mlx_win)
			mlx_destroy_window(fractal->mlx_con, fractal->mlx_win);
		if (fractal->mlx_con)
		{
			mlx_destroy_display(fractal->mlx_con);
			free(fractal->mlx_con);
		}
	}
	exit(EXIT_FAILURE);
}

static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iterations_definition = 40;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->color_s = 0x000000;
	fractal->color_e = 0xFFFFFF;
	fractal->color_f = 0xFF0000;
	fractal->new_min = -2;
	fractal->new_max = 2;
	fractal->old_min = 0;
	fractal->old_max = WIDTH;
}

static void	event_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_win, KeyPress, KeyPressMask, key_handler, fractal);
	mlx_hook(fractal->mlx_win, ButtonPress, ButtonPressMask, mouse_handler,
		fractal);
	mlx_hook(fractal->mlx_win, DestroyNotify, StructureNotifyMask,
		close_handler, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_con = mlx_init();
	if (fractal->mlx_con == NULL)
	{
		ft_putstr_fd("MLX Failed", 2);
		mlx_error(fractal);
	}
	fractal->mlx_win = mlx_new_window(fractal->mlx_con,
			WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_win == NULL)
	{
		ft_putstr_fd("MLX Failed", 2);
		mlx_error(fractal);
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_con, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		ft_putstr_fd("MLX Failed", 2);
		mlx_error(fractal);
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	event_init(fractal);
	data_init(fractal);
}
