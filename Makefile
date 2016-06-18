CC = gcc

CFLAGS = -Wall -Wextra -Werror -Ofast

INCLUDES_PATH = includes/

SRCS_PATH = srcs/

SRCS_NAME = ft_estimate.c \
			ft_train.c \
			common.c \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = objs/

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: odir build

build: $(OBJS)
	@echo " - Making $(NAME)"
	@$(CC) $(CFLAGS) -o ft_estimate objs/ft_estimate.o objs/common.o
	@$(CC) $(CFLAGS) -o ft_train objs/ft_train.o objs/common.o

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLUDES_PATH)

odir:
	@mkdir -p $(OBJS_PATH)

clean:
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	@echo " - Cleaning executable"
	@rm -f ft_estimate
	@rm -f ft_train

re: fclean all

.PHONY: clean fclean re odir
