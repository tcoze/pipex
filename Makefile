CC = gcc
NAME = pipex
CFLAGS = -Wall -Wextra -Werror

SRC_PATH = src/
OBJ_PATH = obj/

SRC =	ft_bzero.c\
		ft_calloc.c\
		ft_memset.c\
		ft_split.c\
		ft_strchr_str.c\
		ft_strjoin.c\
		ft_strlcpy.c\
		ft_strlen.c\
		parsing.c\
		pipex.c \
		process.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ	= $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJ_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re all
