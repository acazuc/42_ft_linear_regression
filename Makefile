TRAIN_NAME = ft_train

ESTIMATE_NAME = ft_estimate

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Ofast

INCLUDES_PATH = include/

SRCS_PATH = src/

SRCS_NAME = ft_estimate.c \
			ft_train.c \
			common.c \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: odir $(OBJS) $(TRAIN_NAME) $(ESTIMATE_NAME)

$(ESTIMATE_NAME):
	@echo " - Making $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJS_PATH)ft_estimate.o $(OBJS_PATH)common.o

$(TRAIN_NAME):
	@echo " - Making $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJS_PATH)ft_train.o $(OBJS_PATH)common.o

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
