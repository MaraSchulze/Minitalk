NAME = minitalk
FLAGS = -Wextra -Wall -Werror
SERVER = server.c ft_strlen.c ft_itoa.c
CLIENT = client.c ft_atoi.c
SERVER_OBJECTS = $(SERVER:.c=.o)
CLIENT_OBJECTS = $(CLIENT:.c=.o)

all : $(NAME)

$(NAME) : server client

both : server client

bonus : server client

server : $(SERVER_OBJECTS)
	gcc $(FLAGS) -g -fsanitize=address $(SERVER_OBJECTS) -o server

client : $(CLIENT_OBJECTS)
	gcc $(FLAGS) -g -fsanitize=address $(CLIENT_OBJECTS) -o client

%.o : %.c
	gcc $(FLAGS) -g -c $< 

clean :
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)

fclean : clean
	rm -f server client

re : fclean all
