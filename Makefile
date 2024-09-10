.DEFAULT_GOAL := all

NAME 	= miniRT
DEBUG_NAME = debug.out

LIBFT_DIR = libft
LIBFT 	= $(LIBFT_DIR)/libft.a
MLX_DIR	= mlx
INC_DIR = include
LDFLAGS	= -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS	= -lm -lft -lmlx -framework OpenGL -framework AppKit

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -O3
INC		= -I $(LIBFT_DIR) -I $(MLX_DIR) -I $(INC_DIR)

ifdef DEBUG
	CFLAGS += -g3 -fsanitize=address 
endif

SRCS	:= \
	$(shell find src -name '*.c') \
	${wildcard bonus/*.c} \
	${wildcard GNL/*.c} \
	${wildcard parse/*.c} \
	${wildcard parse/objects/*.c}

OBJS	= $(SRCS:.c=.o) 
DEBUG_O = $(filter-out src/main.o, $(OBJS)) debug.o
# debug.o

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR) all

all : $(NAME)
debug : $(DEBUG_NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(DEBUG_NAME): $(LIBFT) $(DEBUG_O)
	$(CC) $(CFLAGS) $(INC) $(DEBUG_O) $(LDFLAGS) $(LDLIBS) -o $(DEBUG_NAME)

clean :
	rm -rf $(OBJS)
# rm -rf $(DEBUG_O)
# $(MAKE) -C $(LIBFT_DIR) clean

fclean :
	rm -rf $(OBJS) $(NAME)
	rm -rf $(DEBUG_O) $(DEBUG_NAME)
# $(MAKE) -C $(LIBFT_DIR) fclean

print :
	$(info target : $(DEBUG_O))

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re debug