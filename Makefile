# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: widraugr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 13:07:44 by widraugr          #+#    #+#              #
#    Updated: 2019/12/06 10:10:28 by widraugr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

LIBDIR = ./libft

MLXDIR = minilibx_macos

FILE_C = main.c\
		 init.c\
		 mandelbrot.c\
		 nephroida.c\
		 zoom.c

FLAGS =  -Wall -Wextra -Werror -I libft -I include -I $(MLXDIR) 

FMLXLIB = -L $(MLXDIR) -lmlx -framework OpenGL -framework AppKit

FLIB = -L ./libft -lftprintf 

DIRC = ./source/

VPATH = $(DIROBJ)

DIROBJ = ./obj/

OBJ = $(addprefix $(DIROBJ), $(FILE_C:.c=.o))

all : $(NAME)

$(NAME): $(DIROBJ) $(OBJ) 
	make -C $(LIBDIR)
	gcc $(FLAGS) $(OBJ) $(FLIB) $(FMLXLIB) -o $(NAME)
	make clean -C $(LIBDIR)

$(DIROBJ)%.o : $(DIRC)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ):
	mkdir -p $(DIROBJ)

clean:
	/bin/rm -rf $(DIROBJ)
	
fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C $(LIBDIR)
	
re: fclean all 
