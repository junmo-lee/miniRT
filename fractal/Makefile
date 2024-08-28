.DEFAULT_GOAL := all

NAME	= fractol
NAME_B	= fractol_bouns

LIBFT_DIR	= ../libft
LIBFT	= $(LIBFT_DIR)/libft.a

MLX_DIR	= ../mlx

LDFLAGS	= -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS	= -lm -lft -lmlx -framework OpenGL -framework AppKit

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -O3
INC		= -I $(LIBFT_DIR) -I $(MLX_DIR) -I fractal.h
INC_B	= -I $(LIBFT_DIR) -I $(MLX_DIR) -I fractal_bonus.h

SRCS	= main.c \
			init.c parsing.c atoi_check_num.c \
			colormap.c \
			julia.c mandelbrot_set.c burning_ship.c \
			draw_fractal.c 
			
SRCS_B	= main_bonus.c \
			init_bonus.c parsing_bonus.c atoi_check_num_bonus.c \
			colormap_bonus.c \
			julia_bonus.c mandelbrot_set_bonus.c burning_ship_bonus.c \
			draw_fractal_bonus.c 

OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(SRCS_B:.c=.o)

$(LIBFT) :
	make -C $(LIBFT_DIR) all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME)

$(NAME_B): $(LIBFT) $(OBJS_B)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME_B)

all : $(NAME)

bonus : $(NAME_B)

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(OBJS_B)

fclean :
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(OBJS) $(OBJS_B) $(NAME) $(NAME_B)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all bonus clean fclean re