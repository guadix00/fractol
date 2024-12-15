/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:16:10 by gualvare          #+#    #+#             */
/*   Updated: 2024/11/13 18:30:04 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	free_tmp(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (ERROR);
}

static char	*change_case(char *tmp, char *argv)
{
	int	i;

	tmp = ft_calloc(ft_strlen(argv) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	ft_strlcpy(tmp, argv, ft_strlen(argv) + 1);
	while (tmp[i])
	{
		tmp[i] = ft_tolower(tmp[i]);
		i++;
	}
	return (tmp);
}

static int	check_arg(char *tmp)
{
	if (ft_strncmp(tmp, "mandelbrot", 10) != 0
		&& ft_strncmp(tmp, "julia", 5) != 0
		&& ft_strncmp(tmp, "burningship", 12) != 0)
	{
		ft_putstr_fd("Error-->Wrong fractal name\n", 2);
		ft_putstr_fd("Fractal options = mandelbrot, julia or burningship", 2);
		return (FALSE);
	}
	else
	{
		if (ft_strncmp(tmp, "mandelbrot", 10) == 0)
			return (MANDELBROT);
		else if (ft_strncmp(tmp, "julia", 5) == 0)
			return (JULIA);
		else if (ft_strncmp(tmp, "burningship", 12) == 0)
			return (BURNING_SHIP);
	}
	return (FALSE);
}

int	check_usage(int argc, char *argv)
{
	char	*tmp;
	int		check;

	tmp = NULL;
	check = 0;
	if ((ft_strncmp(argv, "julia", 5) == 0 && argc != 4)
		|| (ft_strncmp(argv, "julia", 5) != 0 && argc != 2))
	{
		ft_putstr_fd("Error--> Wrong number of arguments\n", 2);
		ft_putstr_fd("Fractol use ---> ./fractol [type of fractal]\n", 2);
		ft_putstr_fd("Julia -> ./fractol [fractal] [param z] [param c]", 2);
		free(tmp);
		return (ERROR);
	}
	else
	{
		tmp = change_case(tmp, argv);
		if (!tmp)
			return (free_tmp(tmp));
		check = check_arg(tmp);
		if (check == FALSE)
			return (free_tmp(tmp));
		free(tmp);
	}
	return (check);
}
