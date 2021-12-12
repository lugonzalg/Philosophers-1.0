NAME = philo_bonus
CC = Clang
CFLAGS = -Wall -Werror -Wextra
INC = -I -I./inc
RM = rm -rf
SRC_DIR = src/


FILES = main_bonus \
		philosopher_bonus \
		memory_utils_bonus \
		time_bonus

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} ${SRC} -c $^ -o $@

$(NAME): ${SRC}
	@echo "\033[1;33m\t\tCompiling all source files into unique binary\033[0;m"
	${CC} ${CFLAGS} ${SRC} ${INC} -lpthread -o ${NAME}

clean:
	@echo "\033[1;34m\t\tNo objects to remove "

fclean: clean
	@echo "\033[1;31m\t\tRemoving ${NAME}\033[0;m"
	$(RM) $(NAME)
	$(RM) philo_bonus.dSYM

re: fclean all

.PHONY: all fclean re
