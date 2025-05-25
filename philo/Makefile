# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: val <val@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 23:20:17 by val               #+#    #+#              #
#    Updated: 2025/05/25 19:03:08 by val              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	ANSI TEXT COLORS
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

#	ANSI BACKGROUND COLORS
BG_BLACK = \033[40m
BG_RED = \033[41m
BG_GREEN = \033[42m
BG_YELLOW = \033[43m
BG_BLUE = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN = \033[46m
BG_WHITE = \033[47m

#	STYLES
BOLD = \033[1m
DIM = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
HIDDEN = \033[8m

RESET = \033[0m
##################

DEBUG_VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=all --track-origins=yes -s

NAME = philo

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

VERBOSE = 0

ifeq ($(VERBOSE),1)
    SILENT =
else
    SILENT = @
endif

ifeq ($(VERBOSE),1)
    DUMP_OUT =
else
    DUMP_OUT = > /dev/null 2>&1
endif

SRC_FILES = \
	main.c \
	parse.c \
	write.c \
	structs.c \
	time_utils.c \
	mutex_variables.c \
	thread_monitoring.c \
	thread_philo.c \
	utils/ft_atoi.c \
	utils/ft_putstr_fd.c \
	utils/ft_strlen.c

SRC = $(patsubst %.c, $(SRC_DIR)/%.c, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRC))

CC = cc -g3 -fsanitize=thread
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I$(INC_DIR)
FLAGS = $(CFLAGS) -MMD -MP

all: $(NAME)

$(NAME): $(OBJ)
	$(SILENT)$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "$(BG_GREEN)>>> Program $(NAME) compiled!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(SILENT) mkdir -p $(dir $@)
	@echo "$(BLUE)>>> Compiling $<...$(RESET)"
	$(SILENT)$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)>>> Directory '$(OBJ_DIR)' created!$(RESET)"
	$(SILENT)mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)>>> Cleaning objects$(RESET)"
	$(SILENT)rm -rf $(OBJ_DIR) $(DUMP_OUT)

fclean: clean
	@echo "$(YELLOW)>>> Cleaning executable...$(RESET)"
	$(SILENT)rm -f $(NAME) $(DUMP_OUT)

re: fclean all

debug: all
	$(DEBUG_VALGRIND) ./$(NAME)

debug_env: all
	env -i $(DEBUG_VALGRIND) ./$(NAME)

debug_trueclean: all
	$(DEBUG_VALGRIND) env -i ./$(NAME)

-include $(DEP)

.PHONY: all cleanlibs clean fclean re makelibft debug debug_env debug_trueclean
