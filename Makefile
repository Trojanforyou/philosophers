NAME = philo

cc = gcc
CFLAGS = -Wall -Wextra -Werror -I.

HEADER = philo.h

SRCS = src/main.c src/parse.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean re
