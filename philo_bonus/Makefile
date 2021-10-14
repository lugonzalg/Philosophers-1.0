NAME = philo_bonus
CC = Clang
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
INC = -I -I./inc
RM = rm -rf
SRC_DIR = src/


FILES = main_bonus \
		philosopher_bonus \
		memory_utils_bonus \
		time_bonus

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

all: $(NAME)

$(NAME): ${SRC}
	${CC} ${CFLAGS} ${SRC} ${INC} -lpthread -o ${NAME}

fclean:
	$(RM) $(NAME)
	$(RM) philo_bonus.dSYM

re: fclean all

.PHONY: all bonus fclean re
