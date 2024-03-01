CC = gcc
NAME = pipex
CFLAGS = -Wall -Wextra -Werror

SRC_PATH = src/
PRINTF_PATH = ft_printf/
PRINTF = $(PRINTF_PATH)/libftprintf.a
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
		parsing2.c\
		pipex.c \
		process.c \
		ft_free.c \
		ft_strncmp.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ	= $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME)

$(PRINTF):
	$(MAKE) -C $(PRINTF_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c #ft_printf/ft_printf.h header/pipex.h
	$(CC) $(CFLAGS) -I ft_printf/ -I header -c $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(PRINTF)

clean :
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(PRINTF_PATH) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(PRINTF_PATH) fclean

re : fclean all

.PHONY: clean fclean re all
