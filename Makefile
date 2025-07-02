NAME = philo

CC = gcc
SRCS_DIR = src
OBJS_DIR = obj

CFLAGS = -Wall -Wextra -Werror -I.
HEADER = philo.h

SRCS = src/main.c src/parse.c src/utils.c src/threads.c src/time.c
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
