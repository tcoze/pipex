NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

MY_SOURCES = ft_putchar_fd.c \
			 ft_putstr_fd.c \
			 ft_printf.c \
			 ft_strlen.c \
			 ft_putnbr_fd.c \
			 ft_putnbr_base.c \
			 ft_blen.c \
			 ft_putnbr_adress.c \

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CC = cc

$(NAME) : $(MY_OBJECTS)
	ar rc $(NAME) $(MY_OBJECTS)

clean :
	rm -f $(MY_OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

all : $(NAME)

bonus :
	$(MAKE) $(NAME) $(MY_SOURCES)

%.o : %.c ft_printf.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean fclean re all
