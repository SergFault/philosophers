NAME	= philo_one
CC		= clang
FLAGS	= -Wextra -Wall -Werror -g
INCLUDES = includes/
HDR		= ${INCLUDES}philosophers.h
SRC_DIR	= src/
SRC_FILES = eat.c init.c main.c observer.c sleep_think.c status_checker.c \
			utils/exit.c utils/ft_atoi.c utils/print.c utils/time.c \
			utils/free_resources.c utils/atoi_err.c
SRC		= $(addprefix ${SRC_DIR}, ${SRC_FILES})
OBJ		= ${SRC:.c=.o}

%.o : %.c ${HDR}
		$(CC) $(FLAGS) -I$(INCLUDES) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $@ $^

clean:
			rm -f ${OBJ}
			rm -f ${OBJ}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		re all clean fclean