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
	${CC} ${CFLAGS} ${SRC} ${INC} -lpthread -o ${NAME}

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus fclean re
