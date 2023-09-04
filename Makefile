NAME					=				ray

CC						=				cc
CCFLAGS					=				-Wall -Werror -Wextra

LIB						=				-lglut -lGL -lGLU -lm

RM						=				rm -rf

SRC						=				raycaster.c \
										$(addprefix utils/, check_lines.c \
															display.c \
															draw.c \
															math.c \
															moves.c \
															read_map.c)

OBJ						=				$(SRC:%.c=%.o)

all:					$(NAME)

$(NAME):				$(OBJ)
						$(CC) $(CCFLAGS) $(OBJ) $(LIB) -o $(NAME)

clean:
						$(RM) $(OBJ)

fclean:					clean
						$(RM) $(NAME)

re:						fclean all

.PHONY:					all clean fclean re