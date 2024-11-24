NAME = minitalk

server: server.c
	gcc -Wall -Wextra -Werror server.c -o server

client: client.c
	gcc -Wall -Wextra -Werror client.c -o client

$(NAME): server client

all: server client

clean:
	rm -f server client

fclean: clean

re: clean all

.PHONY: all clean fclean re