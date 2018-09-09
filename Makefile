# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/17 17:27:16 by vveselov          #+#    #+#              #
#    Updated: 2018/09/06 19:08:56 by vveselov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

OBJ_DIR = ./

SRC_DIR = src/

INC_DIR = include/

SRC = main.cpp VM.cpp Factory.cpp

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

CC = clang++

CC_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

$(OBJ_DIR)%.o: %.cpp
	$(CC) -c $< -o $@ $(CC_FLAGS) -I $(INC_DIR)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

run:
	./$(NAME)

vpath %.cpp $(SRC_DIR)
