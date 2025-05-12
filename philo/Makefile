# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 21:37:02 by mgenoves          #+#    #+#              #
#    Updated: 2025/02/28 12:15:11 by mgenoves         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome del progetto
NAME = philo

# File sorgenti (con percorsi relativi)
SRCS = src/main.c \
        src/parse/check.c src/parse/utils.c \
        src/sim/init.c src/sim/routine.c src/sim/action.c src/sim/take_forks_utils.c src/sim/routine_utils.c \
		
# Cartella per gli oggetti (senza sottocartelle)
OBJ_DIR = obj

# Lista file oggetto (nomi piatti in obj/)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

# Compilatore e flag
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Percorsi di ricerca per i file .c
vpath %.c $(sort $(dir $(SRCS)))

# Obiettivo principale
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Regola generica per compilare i .o
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crea la cartella obj se manca
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Altre regole
all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

git:
	make fclean
	git add .
	git commit -m "update"
	git push

.PHONY: all clean fclean re git
