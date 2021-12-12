NAME 	= philo

CC 		= clang
CFLAGS 	= -Wall -Werror -Wextra -g3 -fsanitize=address
INC 	= -I inc/
LIB		= -L -lpthread
RM		= rm -rf

FILES	= src/main \
		  src/philosopher \
		  src/philo_tasks \
		  src/time 

SRC 	= $(addsuffix .c, $(FILES))
OBJ 	= $(addsuffix .o, $(FILES))

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

$(NAME): $(OBJ)
	@echo "\033[1;33m\t\tCompiling all source files into unique binary\033[0;m"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	@echo "\033[1;31m\t\tRemoving $(NAME)\033[0;m"
	$(RM) $(NAME)
	$(RM) philo.dSYM

re: fclean all

.PHONY: all bonus clean fclean re
