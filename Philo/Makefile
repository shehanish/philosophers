
NAME        := philo
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -g -pthread 
SRCS        :=  ft_check_args.c\
				ft_init.c\
				ft_routines_check.c\
				ft_threads.c\
				main.c \
				ft_time.c\
				ft_utils.c\
				ft_utils1.c\
				ft_eat.c\
			
                    
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@echo "Compilation of $(NAME) ..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(NAME) created ✔️"
			
all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "Deleting $(NAME) objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "Deleting $(NAME) binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re

