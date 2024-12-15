# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 18:40:27 by gualvare          #+#    #+#              #
#    Updated: 2024/11/13 19:08:12 by gualvare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCS = fractol.c init.c fractal_logic.c render.c events.c manage_colours.c arg_check.c
OBJS = $(SRCS:.c=.o)


CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iminilibx-linux -fsanitize=address

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext


END = \033[m
YELLOW = \033[33m


all: submodule $(NAME)

submodule:
	git submodule init
	git submodule update


$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo "\n$(YELLOW)Fractolizando...$(END)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)


%.o: %.c fractol.h libft/libft.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@




$(LIBFT):
	@echo "\n$(YELLOW)Construyendo libft...$(END)"
	@make -C $(LIBFT_DIR)


$(MLX_LIB):
	@echo "\n$(YELLOW)Construyendo MiniLibX...$(END)"
	@make -C $(MLX_DIR)


clean:
	@echo "\n$(YELLOW)Limpiando archivos...$(END)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR)


fclean: clean
	@echo "\n$(YELLOW)Limpiando todo...$(END)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all clean fclean re submodule
