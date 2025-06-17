NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

HEADER = philo.h

SRCS = src/main.c src/parse.c src/utils.c src/threads.c src/time.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
