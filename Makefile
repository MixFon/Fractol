# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: widraugr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 13:07:44 by widraugr          #+#    #+#              #
#    Updated: 2019/11/18 18:07:57 by widraugr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

NAMEBIN = libft

FILE_C =	main.c
#-Wall -Wextra -Werror
FLAGS =  -I libft -I include -I minilibx 

FMLXLIB = -L minilibx -lmlx -framework OpenGL -framework AppKit

FLIB = -L ./libft -lftprintf 

DIRC = ./source/

VPATH = $(DIROBJ)

DIROBJ = ./obj/

OBJ = $(addprefix $(DIROBJ), $(FILE_C:.c=.o))

all : $(NAME)

$(NAME): $(DIROBJ) $(OBJ) 
	gcc $(FLAGS) $(OBJ) $(FLIB) $(FMLXLIB) -o $(NAME)

$(DIROBJ)%.o : $(DIRC)%.c
	gcc -g $(FLAGS) -c $< -o $@

$(DIROBJ):
	mkdir -p $(DIROBJ)

clean:
	/bin/rm -rf $(DIROBJ)
	
fclean: clean
	/bin/rm -f $(NAME)
	
re: fclean all 
