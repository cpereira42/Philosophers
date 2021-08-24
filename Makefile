# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/27 00:08:05 by cpereira          #+#    #+#              #
#    Updated: 2021/08/23 09:37:19 by cpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER_DIR =	includes/

SDIR =	./srcs/
ODIR =	./objs/

SRCS =	$(SDIR)main.c \
		$(SDIR)timming.c \
		$(SDIR)actions.c \
		$(SDIR)utils.c

OBJS =	$(patsubst $(SDIR)%.c, $(ODIR)%.o, $(SRCS))

CC = clang
HEADERS = -I./$(HEADER_DIR)
C_FLAGS = -Wall -Werror -Wextra -g
C_SANIT = -fsanitize=address
L_FLAGS =  -lpthread


$(NAME): $(OBJS)
		@$(CC) $(OBJS) $(C_FLAGS) $(C_SANIT) $(HEADERS) $(L_FLAGS) -o $@
		@echo "\033[1;34mDone\033[0;37m"

$(ODIR)%.o: $(SDIR)%.c
		@mkdir -p $(ODIR)
		@$(CC) $(C_FLAGS) $(HEADERS) -c $< -o $@


all: philo

clean:
	@rm -rf $(ODIR)

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;33mCleaned\033[0;37m"

re: fclean all
