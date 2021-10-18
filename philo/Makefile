NAME = philo

CC = Clang
CFLAGS = -Wall -Werror -Wextra
INC = -I -I./inc
RM = rm -rf
AR = ar rcs

FILES = src/main \
		src/philosopher \
		src/memory_utils \
		src/time 

SRC = $(addsuffix .c, $(FILES))

all: $(NAME)

$(NAME): ${SRC}
	@echo "\033[1;33m\t\tCompiling all source files into unique binary\033[0;m"
	${CC} ${CFLAGS} ${SRC} ${INC} -lpthread -o ${NAME}

clean:
	@echo "\033[1;34m\t\tNo objects to remove "

fclean: clean
	@echo "\033[1;31m\t\tRemoving ${NAME}\033[0;m"
	$(RM) $(NAME)
	$(RM) philo.dSYM

re: fclean all

.PHONY: all bonus fclean re
