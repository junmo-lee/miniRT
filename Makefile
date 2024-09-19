.DEFAULT_GOAL := all

NAME 	= miniRT
NAME_B	= miniRT_bonus

DEBUG_NAME = debug.out
DEBUG_NAME_B = debug_bonus.out

LIBFT_DIR = libft
LIBFT 	= $(LIBFT_DIR)/libft.a
MLX_DIR	= mlx
GNL_DIR	= GNL
INC_DIR = include

LDFLAGS	= -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS	= -lm -lft -lmlx -framework OpenGL -framework AppKit

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -O3
INC		= -I $(LIBFT_DIR) -I $(MLX_DIR) -I $(GNL_DIR) -I $(INC_DIR)

ifdef DEBUG
	CFLAGS += -g3 -fsanitize=address 
endif

SRCS	:= \
	$(shell find src -name '*.c') \
	${wildcard bonus/*.c} \
	${wildcard GNL/*.c} \
	${wildcard parse/*.c} \
	${wildcard parse/objects/*.c}

SRCS_B	:= \
	$(shell find src_bonus -name '*.c') \
	${wildcard bonus/*.c} \
	${wildcard GNL/*.c} \
	${wildcard parse_bonus/*.c} \
	${wildcard parse_bonus/objects/*.c}

OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(SRCS_B:.c=.o)

DEBUG_O = $(filter-out src/main.o, $(OBJS)) debug.o
DEBUG_B_O = $(filter-out src_bonus/main.o, $(OBJS_B)) debug_bonus.o

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR) all

all : $(NAME)
bonus : $(NAME_B)

debug : $(DEBUG_NAME)
debug_bonus	: $(DEBUG_NAME_B)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(NAME_B) : $(LIBFT) $(OBJS_B)
	$(CC) $(CFLAGS) $(INC) $(OBJS_B) $(LDFLAGS) $(LDLIBS) -o $(NAME_B)

$(DEBUG_NAME): $(LIBFT) $(DEBUG_O)
	$(CC) $(CFLAGS) $(INC) $(DEBUG_O) $(LDFLAGS) $(LDLIBS) -o $(DEBUG_NAME)

$(DEBUG_NAME_B): $(LIBFT) $(DEBUG_B_O)
	$(CC) $(CFLAGS) $(INC) $(DEBUG_B_O) $(LDFLAGS) $(LDLIBS) -o $(DEBUG_NAME_B)

clean :
	rm -rf $(OBJS) $(OBJS_B)
	rm -rf $(DEBUG_O) $(DEBUG_B_O)
# rm -rf $(DEBUG_O)
# $(MAKE) -C $(LIBFT_DIR) clean

fclean :
	rm -rf $(OBJS) $(NAME)
	rm -rf $(OBJS_B) $(NAME_B)
	rm -rf $(DEBUG_O) $(DEBUG_NAME)
	rm -rf $(DEBUG_B_O) $(DEBUG_NAME_B)
# $(MAKE) -C $(LIBFT_DIR) fclean

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re debug debug_bonus