.DEFAULT_GOAL := all

NAME 	= miniRT
DEBUG_NAME = debug.out

LIBFT_DIR = libft
LIBFT 	= $(LIBFT_DIR)/libft.a
MLX_DIR	= mlx
LDFLAGS	= -L$(LIBFT_DIR)  -L$(MLX_DIR)
LDLIBS	= -lm -lft -lmlx -framework OpenGL -framework AppKit

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror
INC		= -I $(LIBFT_DIR) -I $(MLX_DIR)

ifdef DEBUG_FLAG
	CFLAGS += -g3 -fsanitize=address
endif

SRCS	:= \
	${wildcard src/*.c}

# SRCS	= $(addprefix src/, $(SRCS))

OBJS	= $(SRCS:.c=.o) 

DEBUG_O = $(filter-out */main.o, $(OBJS)) debug.o


%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR) all

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(DEBUG_NAME): $(LIBFT) $(DEBUG_O)
	$(CC) $(CFLAGS) $(INC) $(DEBUG_O) $(LDFLAGS) $(LDLIBS) -o $(DEBUG_NAME)

clean :
	rm -rf $(OBJS)
	rm -rf $(DEBUG_O)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean :
	rm -rf $(OBJS) $(NAME)
	rm -rf $(DEBUG_O) $(DEBUG_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re