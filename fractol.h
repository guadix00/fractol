/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:16:45 by gualvare          #+#    #+#             */
/*   Updated: 2024/11/13 18:16:47 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "minilibx-linux/mlx.h" 
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# define SUCCES 0
# define FALSE 0
# define TRUE 1
# define ERROR 0
# define WIDTH 800
# define HEIGHT 800
# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3

typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_con;
	void	*mlx_win;
	t_img	img;
	double	escape_value;
	int		iterations_definition;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
	int		color_s;
	int		color_e;
	int		color_f;
	double	old_min;
	double	old_max;
	double	new_min;
	double	new_max;
}			t_fractal;

void			fractal_init(t_fractal *fractal);
double			atodbl(char *s);
double			map(double unscaled_num, t_fractal *fractal);
t_complex		sum_complex(t_complex z1, t_complex z2);
t_complex		square_complex(t_complex z);
void			fractal_render(t_fractal *fractal);
int				key_handler(int keysym, t_fractal *fractal);
int				close_handler(t_fractal *fractal);
int				mouse_handler(int button, int x, int y, t_fractal *fractal);
int				*init_colors(void);
int				get_color(int *colors, int size);
void			free_colors(int *colors);
unsigned int	map_iterations_to_color(t_fractal *fractal, int iteration);
int				check_usage(int argc, char *argv);
#endif