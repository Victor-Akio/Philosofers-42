NAME	=	philo

CC		=	clang

DIR		=	srcs/
OBJ_DIR	=	obj/
SUB_DIR	=	obj/philo

FLAG	=	-c		\
			-Wall	\
			-Wextra	\
			-Werror

INCLUDE	=	-I include/

RM		=	@/bin/rm -rf

FILES		=	main.c			\
				init.c			\
				help.c			\
				printer.c		\
				manager.c		\
				time.c			\
				utils.c			\
				lib.c	

SRCS	=	$(addprefix $(DIR), $(FILES))
OBJ		=	$(SRCS:$(DIR)%.c=$(OBJ_DIR)%.o)

all		:	$(NAME)

obj/%.o	:	srcs/%.c
			@mkdir -p $(OBJ_DIR) $(SUB_DIR)
			$(CC) -g3 $(FLAG) $(INCLUDE) $< -o $@

$(NAME)	:	$(OBJ)
			$(CC) -fsanitize=address -o $@ $^

clean	:
			for dir in $(MODULES); do	\
				$(MAKE) clean -C $$dir;	\
			done
			$(RM) $(OBJ_DIR)


fclean	:	clean
			@$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re