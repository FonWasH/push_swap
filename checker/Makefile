NAME			= checker

LIBFT_DIR		= ../libs/libft/
LIBFT_A			= libft.a

INC_DIR			= ./includes/
SRC_DIR			= ./src/
OBJ_DIR			= ./obj/

SRCS			= $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS			= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRCS:.c=.o))

RM				= rm -rf
CC				= cc
CFLAGS			= -O3 -Wall -Wextra -Werror
CDEBUG			= -g3 -O0 -Wall -Wextra -Werror -D DEBUG=true
IFLAGS			= -I$(INC_DIR) -I$(LIBFT_DIR)
LFLAGS			= -L$(LIBFT_DIR) -lft


all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ../obj/*/*.o $(LFLAGS)

clean:
				@$(RM) $(OBJ_DIR)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

debug:			CFLAGS = $(CDEBUG)
debug:			fclean $(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ../obj/*/*.o $(LFLAGS)

.PHONY: 		all clean fclean re