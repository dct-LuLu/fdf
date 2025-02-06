NAME		= fdf

DIR			= Fdf
SRCDIR		= $(DIR)/src
INCDIR		= $(DIR)/include

SRCS		= main.c mlx_draw_utils.c parse_map.c parse_map_utils.c \
			  str_utils.c utils.c math_utils.c map_utils.c mlx_hooks.c \
			  draw_map.c vec2.c vec3.c img_utils.c

SRCS		:= $(addprefix $(SRCDIR)/, $(SRCS))

vpath %.c $(SRCDIR)
vpath %.h $(INCDIR)
