# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbeauzam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 13:59:02 by tbeauzam          #+#    #+#              #
#    Updated: 2017/04/01 01:22:24 by chkropok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1		=	lem-in
NAME2		=	visualizer
CC			=	clang
FLAGS		=	-Wall -Wextra -Werror
SRC_NAME1	=	main_lem_in.c \
				lem_in_print.c
SRC_NAME2	=	lem_in_read.c \
				lem_in_parsing.c \
				lem_in_get_ants_and_rooms.c \
				lem_in_rooms.c \
				lem_in_links.c \
				lem_in_find_path.c
SRC_NAME3	=	main_visu.c \
				visu_check_output.c \
				visu_handle.c \
				visu_windows.c \
				visu_inputs.c \
				visu_title.c \
				visu_map.c \
				visu_ui.c \
				visu_line_drawing.c
OBJ_NAME1	=	$(SRC_NAME1:.c=.o)
OBJ_NAME2	=	$(SRC_NAME2:.c=.o)
OBJ_NAME3	=	$(SRC_NAME3:.c=.o)
SRC_PATH	=	./src
OBJ_PATH	=	./obj
SRC1			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME1))
SRC2			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME2))
SRC3			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME3))
OBJ1			=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME1))
OBJ2			=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME2))
OBJ3			=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME3))
INC			=	-I ./include -I ./libft/include
INC_FILE1	=	./include/lem_in.h
INC_FILE2	=	./include/lem_in_visu.h
LFT			=	-L ./libft -lft
NCURSES		=	-lcurses

.PHONY: all, make_lft, clean, fclean, lft_clean, lft_fclean, re

all:				make_lft $(NAME1) $(NAME2)


$(NAME1):			$(OBJ1) $(OBJ2)
	@$(CC) $(FLAGS) -o $(NAME1) $(OBJ1) $(OBJ2) $(LFT)
	@echo "Lem_in executable Done!"

$(NAME2):			$(OBJ2) $(OBJ3)
	@$(CC) $(FLAGS) -o $(NAME2) $(OBJ2) $(OBJ3) $(LFT) $(NCURSES)
	@echo "Visu executable Done!"

$(OBJ_PATH)/%.o:		$(SRC_PATH)/%.c $(INC_FILE1) $(INC_FILE2)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:				lft_clean
	@rm -f $(OBJ1) $(OBJ2) $(OBJ3)
	@rmdir $(OBJ_PATH) 2> /dev/null || :
	@echo "Objects of Lem_in and Visu Cleaned!"

fclean:				lft_fclean clean
	@rm -f $(NAME1) $(NAME2)
	@echo "Executables of Lem_in and Visu Cleaned!"
	@echo "Everything have been exterminated, Sir!"


make_lft:
	@$(MAKE) -C ./libft all

lft_clean:
	@$(MAKE) -C ./libft clean

lft_fclean:
	@$(MAKE) -C ./libft fclean


re:					fclean all
