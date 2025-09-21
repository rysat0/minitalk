NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I . -I ft_printf/includes -I ft_printf/ft_libft

LIBFTPRINTF_DIR = ft_printf
LIBFTPRINTF = $(LIBFTPRINTF_DIR)/libftprintf.a

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = server.o
OBJS_CLIENT = client.o

all: $(LIBFTPRINTF) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBFTPRINTF_DIR)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFTPRINTF) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFTPRINTF) -o $(NAME_CLIENT)

server.o: server.c minitalk.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c server.c -o server.o

client.o: client.c minitalk.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c client.c -o client.o

clean:
	$(MAKE) -C $(LIBFTPRINTF_DIR) clean
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	rm -f $(LIBFTPRINTF)
	rm -f $(LIBFTPRINTF_DIR)/ft_libft/libft.a

fclean: clean
	$(MAKE) -C $(LIBFTPRINTF_DIR) fclean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
