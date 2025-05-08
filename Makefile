NAME			= push_swap

LIBFT_DIR		= libs/libft/
LIBFT_A			= libft.a

CHK_DIR			= ./checker/
INC_DIR			= ./includes/
SRC_DIR			= ./src/
OBJ_DIR			= ./obj/
CHK				= checker
SRCS			= $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS			= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRCS:.c=.o))

RM				= rm -rf
CC				= cc
CFLAGS			= -O3 -Wall -Wextra -Werror -MMD -MP
CDEBUG			= -g3 -O0 -Wall -Wextra -Werror -D DEBUG=true
IFLAGS			= -I$(INC_DIR) -I$(LIBFT_DIR)
LFLAGS			= -L$(LIBFT_DIR) -lft
VOPTIONS		= --track-origins=yes --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-fds=yes --trace-children=yes --errors-for-leak-kinds=all

GR				= \e[92m
B				= \e[94m
G				= \e[90m
C				= \e[96m
IT				= \e[3m
NC				= \e[0m
BSIZE			= 50
TFILES			= $(words $(SRCS))
CFILES			= 0

GMIN			= -100
GMAX			= 100
GCOUNT			= 100
ifeq ($(origin ARG), undefined)
ARG 			:= $(shell python3 -c 'import random; print("\n".join(map(str, random.sample(range($(GMIN), $(GMAX) + 1), $(GCOUNT)))))' | tr '\n' ' ')
endif

define animate_dots
animate_dots() { \
	MSG="$$1"; \
	while :; do \
		printf "\r$$MSG.  "; sleep 0.2; \
		printf "\r$$MSG.. "; sleep 0.2; \
		printf "\r$$MSG..."; sleep 0.2; \
	done \
}
endef
export animate_dots


all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)
				@$(eval CFILES := $(shell echo $$(($(CFILES)+1))))
				@echo -n "⚙️ ["
				@for i in `seq 1 $(shell echo "$$(($(CFILES)*$(BSIZE)/$(TFILES)))")`; do \
					echo -n "$(GR)▆$(NC)" ; \
				done
				@for i in `seq 1 $(shell echo "$$(($(BSIZE)-$(CFILES)*$(BSIZE)/$(TFILES)))")`; do \
					echo -n "$(G)▆$(NC)" ; \
				done
				@echo -n "] $(shell echo "scale=2; $(CFILES)/$(TFILES) * 100" | bc)% [$(CFILES)/$(TFILES)] ➜ $(notdir $<)"
				@echo -n "\e[0K\r"

$(NAME):		title $(OBJS)
				@$(animate_dots); \
				if [ -f "$(NAME)" ]; then \
					NEWER=$$(find . -name '*.c' -newer $(NAME) -o -name '*.h' -newer $(NAME)); \
					if [ -z "$$NEWER" ]; then \
						echo "⚠️ No changes detected, no need for compilation."; \
					else \
						echo -n "\e[0K\r"; \
						(animate_dots "⚙️ Building libraries") & PID=$$!; \
						make -sC $(LIBFT_DIR); \
						kill $$PID 2>/dev/null; wait $$PID 2>/dev/null || true; \
						echo -n "\e[0K\r"; \
						(animate_dots "⚙️ Compiling executable") & PID=$$!; \
						$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS); \
						kill $$PID 2>/dev/null; wait $$PID 2>/dev/null || true; \
						echo -n "\e[0K\r"; \
						echo "✅ Compilation completed."; \
					fi; \
				else \
					echo -n "\e[0K\r"; \
					(animate_dots "⚙️ Building libraries") & PID=$$!; \
					make -sC $(LIBFT_DIR); \
					kill $$PID 2>/dev/null; wait $$PID 2>/dev/null || true; \
					echo -n "\e[0K\r"; \
					(animate_dots "⚙️ Compiling executable") & PID=$$!; \
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS); \
					kill $$PID 2>/dev/null; wait $$PID 2>/dev/null || true; \
					echo -n "\e[0K\r"; \
					echo "✅ Compilation completed."; \
				fi

bonus:			$(OBJS)
				@make -sC $(LIBFT_DIR)
				@make -sC $(CHK_DIR)
				@clear
				@echo "✅ Checker compilation completed."

clean:
				@make clean -sC $(LIBFT_DIR)
				@make clean -sC $(CHK_DIR)
				@$(RM) $(OBJ_DIR)
				@clear
				@echo "🆑 Clean completed."

fclean:			clean
				@make fclean -sC $(CHK_DIR)
				@$(RM) $(NAME)
				@clear
				@echo "✴️ Full clean completed."

re:				fclean all
				@echo -n "\e[1A\e[0K\r"
				@echo "🔄 Recompilation completed."

run:			all
				@echo "🚀 Running $(NAME).."
				@./$(NAME) $(ARG)

checker:		all bonus
				@echo "🚀 Running $(NAME) with $(CHK).."
				@./$(NAME) $(ARG) | ./$(CHK)/$(CHK) $(ARG)

count:			all
				@echo "🚀 Running $(NAME) with wc.."
				@./$(NAME) $(ARG) | wc -l

cdebug:			CFLAGS = $(CDEBUG)
cdebug:			fclean title $(OBJS)
				@$(animate_dots); \
				echo -n "\e[0K\r"; \
				(animate_dots "⚙️ Building libraries") & PID=$$!; \
				make -sC $(LIBFT_DIR); \
				kill $$PID 2>/dev/null; wait $$PID 2>/dev/null || true; \
				echo -n "\e[0K\r"; \
				(animate_dots "⚙️ Compiling executable") & PID=$$!; \
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS); \
				kill $$PID 2>/dev/null; wait $$PID 2>/dev/null || true; \
				echo -n "\e[0K\r"; \
				echo "✅ Compilation completed."

debug:			cdebug
				@echo "🚧 Running $(NAME) in debug mode.."
				@valgrind $(VOPTIONS) ./$(NAME) $(ARG)

forbidden:		all
				@nm $(NAME) | grep U

norminette:
				@norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR) > norminette.log 2>&1 || true
				@if grep -qE "Error|Warning" norminette.log; then \
					grep -E "Error|Warning" norminette.log; \
				else \
					echo "Norme: $(GR)OK!$(NC)"; \
				fi
				@$(RM) norminette.log

title:
				@clear
				@echo ""
				@echo "$(B)██████$(G)╗ $(B)██$(G)╗   $(B)██$(G)╗$(B)███████$(G)╗$(B)██$(G)╗  $(B)██$(G)╗    $(B)███████$(G)╗$(B)██$(G)╗    $(B)██$(G)╗ $(B)█████$(G)╗ $(B)██████$(G)╗"
				@echo "$(B)██$(G)╔══$(B)██$(G)╗$(B)██$(G)║   $(B)██$(G)║$(B)██$(G)╔════╝$(B)██$(G)║  $(B)██$(G)║    $(B)██$(G)╔════╝$(B)██$(G)║    $(B)██$(G)║$(B)██$(G)╔══$(B)██$(G)╗$(B)██$(G)╔══$(B)██$(G)╗"
				@echo "$(B)██████$(G)╔╝$(B)██$(G)║   $(B)██$(G)║$(B)███████$(G)╗$(B)███████$(G)║    $(B)███████$(G)╗$(B)██$(G)║ $(B)█$(G)╗ $(B)██$(G)║$(B)███████$(G)║$(B)██████$(G)╔╝"
				@echo "$(B)██$(G)╔═══╝ $(B)██$(G)║   $(B)██$(G)║╚════$(B)██$(G)║$(B)██$(G)╔══$(B)██$(G)║    ╚════$(B)██$(G)║$(B)██$(G)║$(B)███$(G)╗$(B)██$(G)║$(B)██$(G)╔══$(B)██$(G)║$(B)██$(G)╔═══╝"
				@echo "$(B)██$(G)║     ╚$(B)██████$(G)╔╝$(B)███████$(G)║$(B)██$(G)║  $(B)██$(G)║    $(B)███████$(G)║╚$(B)███$(G)╔$(B)███$(G)╔╝$(B)██$(G)║  $(B)██$(G)║$(B)██$(G)║"
				@echo "$(G)╚═╝      ╚═════╝ ╚══════╝╚═╝  ╚═╝    ╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝ $(NC)"
				@echo "$(G)$(IT)Authors: $(C)FonWasH $(G)($(C)juperez$(G))$(NC)"
				@echo ""

-include 		$(OBJS:.o=.d)
.PHONY: 		all bonus clean fclean re run checker count cdebug debug forbidden norminette title