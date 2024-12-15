/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:16:32 by gualvare          #+#    #+#             */
/*   Updated: 2024/11/13 18:30:30 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	burning_ship_iter(t_complex *z, t_complex *c)
{
	z->x = fabs(z->x);
	z->y = fabs(z->y);
	*z = sum_complex(square_complex(*z), *c);
}

static void	man_jul(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		if (fractal->julia_x != 0)
			c->y = -1 * (fractal->julia_y);
		else
			c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (map(x, fractal) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, fractal) * fractal->zoom) + fractal->shift_y;
	man_jul(&z, &c, fractal);
	while (i < fractal->iterations_definition)
	{
		if (!ft_strncmp(fractal->name, "burningship", 11))
			burning_ship_iter(&z, &c);
		else
			z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color = map_iterations_to_color(fractal, i);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractal->img, fractal->color_f);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_con, fractal->mlx_win,
		fractal->img.img_ptr, 0, 0);
}
