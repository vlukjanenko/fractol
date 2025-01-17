# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majosue <majosue@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 10:14:46 by majosue           #+#    #+#              #
#    Updated: 2020/03/13 16:53:53 by majosue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  fractol
HEADER = fractol.h fractol_opencl.h
INCLUDES = -I libft/ -I minilibx_macos/
MINILIBX = minilibx_macos/libmlx.a
LIBFT = libft/libft.a
COMPILERC = gcc
FLAGS = -Wall -Wextra -Werror 
SOURCES  =  fractol.c  ft_events.c ft_opencl_init.c ft_init.c ft_actions.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(MINILIBX) $(LIBFT)
	$(COMPILERC) -o $(NAME) $(OBJECTS) $(INCLUDES) -L minilibx_macos/ -lmlx -framework OpenGL -framework Appkit -framework OpenCL -L libft/ -lft
	
$(LIBFT): libft/*.c libft/*.h	
	$(MAKE) -sC  libft/

$(MINILIBX): minilibx_macos/*.c minilibx_macos/*.h
	$(MAKE) -sC minilibx_macos/

%.o: %.c $(HEADER)
	$(COMPILERC) $(FLAGS) $(INCLUDES) -o $@ -c $< 

clean:
	@rm -f $(OBJECTS)
	$(MAKE) -sC libft/ clean
	$(MAKE) -sC minilibx_macos/ clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -sC libft/ fclean
	$(MAKE) -sC minilibx_macos/ clean

re: fclean all