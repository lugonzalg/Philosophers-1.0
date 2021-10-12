NAME = philo

CC = Clang
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
AR = ar rcs

FILES = main \
		philosopher \
		memory_utils \
		time 

SRC = $(addsuffix .c, $(FILES))
OBJ = $(addsuffix .o, $(FILES))

.c.o: $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
