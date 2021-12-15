NAME		= philo
CC			= clang
FLAGS		= -Wextra -Wall -Werror -g
INCLUDES 	= includes/
HDR			= ${INCLUDES}philosophers.h
SRC_DIR		= src/
SRC_FILES 	= eat.c init.c main.c observer.c think_live.c init_1.c \
			status_checker.c \
			utils/exit.c utils/atoi_err.c utils/print.c utils/time.c \
			utils/free_resources.c utils/atoi_err.c checker.c \
			utils/contains_nums.c utils/precise_sleep.c
SRC			= $(addprefix ${SRC_DIR}, ${SRC_FILES})
OBJ			= ${SRC:.c=.o}

%.o : 		%.c ${HDR} Makefile
				$(CC) $(FLAGS) -I$(INCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
				$(CC) $(FLAGS) -o $@ $^

clean:
				rm -f ${OBJ}
				rm -f ${OBJ}

fclean:		clean
				rm -f ${NAME}

re:			fclean all

.PHONY:		re all clean fclean