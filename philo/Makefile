NAME = philo
INCLUDES = -I ./includes
CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

FILES = main.c utils.c simulation.c
SRCDIR = ./src/
SRC = $(addprefix $(SRCDIR), $(FILES))
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY:		all re clean fclean