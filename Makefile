SDIR	=	src
SRCS	=	$(shell ls $(SDIR))

ODIR	=	obj
OBJS	=	$(addprefix $(ODIR)/,$(SRCS:.c=.o))

IDIR	=	inc
INC		=	$(shell ls $(IDIR))
INCLUDE	=	$(addprefix $(IDIR)/,$(INC))

ILIB	=	-I$(shell brew --prefix readline)/include -Ilibft/inc
SLIB	=	-L$(shell brew --prefix readline)/lib -lreadline -Llibft/lib -lft -lncurses

NAME	=	minishell

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -rf

# ----------------Colors------------------------------------------------------
BLUE	=	\033[0;34m
CYAN	=	\033[1;36m
GREEN	=	\033[1;32m
RED		=	\033[0;31m
YELLOW	=	\033[1;33m
PURPLE	=	\033[1;35m
CLEAR	=	\033[m
# ----------------------------------------------------------------------------

all: $(NAME)

$(ODIR)/%.o: $(SDIR)/%.c $(INCLUDE)
	@mkdir -p $(@D)
	@echo "$(BLUE)Compiling $(GREEN)$(basename $(@F))$(CLEAR)"
	@$(CC) $(CFLAGS) $(ILIB) -I$(IDIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(BLUE)Creating  $(CYAN)libft$(CLEAR)"
	@make -C libft
	@echo "$(BLUE)Building  $(CYAN)$(NAME)$(CLEAR)"
	@$(CC) $(OBJS) $(SLIB) -o $(NAME)

clean:
	@make -C libft clean
	@echo "$(RED)Deleting $(PURPLE)objects$(CLEAR)"
	@$(RM) $(ODIR)

fclean:	clean
	@make -C libft fclean
	@echo "$(RED)Deleting $(YELLOW)$(NAME)$(CLEAR)"
	@$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re