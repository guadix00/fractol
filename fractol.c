/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:15:56 by gualvare          #+#    #+#             */
/*   Updated: 2024/11/13 18:24:53 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;
	int			check;

	if (argc != 1)
	{
		check = check_usage(argc, argv[1]);
		if (check == ERROR)
			exit(EXIT_FAILURE);
		fractal.name = argv[1];
		if (!ft_strncmp(argv[1], "julia", 5))
		{
			fractal.julia_x = atodbl(argv[2]);
			fractal.julia_y = atodbl(argv[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_con);
	}
	else
	{
		ft_putstr_fd("Wrong number of arguments", 2);
		exit(EXIT_FAILURE);
	}
}
