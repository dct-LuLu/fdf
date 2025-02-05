# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 13:56:12 by jaubry--          #+#    #+#              #
#    Updated: 2025/02/05 20:09:16 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

# Colors and formatting
GREEN		= \e[1;32m
BLUE		= \e[1;34m
RED			= \e[1;31m
YELLOW		= \e[1;33m
PURPLE		= \e[1;35m
UNDERLINE	= \e[4m
BOLD		= \e[1m
RESET		= \e[0m

# Directories
INCDIR		= include
#SRCDIR		= src
#SRCDIR		= audio_tests
SRCDIR		= testo
OBJDIR		= ../.obj/$(SRCDIR)
DEPDIR		= ../.dep/$(SRCDIR)
LIBFTDIR	= ../libft
MLXDIR		= ../minilibx-linux-edit

# Output
NAME		= ../oscilloscope_visualizer
LIBFT		= $(LIBFTDIR)/libft.a
MLX			= $(MLXDIR)/libmlx.a

# Variables
WIDTH		= 1000
HEIGHT		= 1000
GLASS		= 0
DEBUG		= 0

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -D_REENTRANT -Ofast 
#-g3
CFLAGS		:= $(CFLAGS) -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT) \
			   -D DEBUG=$(DEBUG) -D GLASS=$(GLASS)
DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d
IFLAGS		= -I$(INCDIR) -I$(LIBFTDIR)/include -I$(MLXDIR) \
			  -I$(PAINSTALL)/include -I/usr/include/pipewire-0.3 \
			  -I/usr/include/spa-0.2 
LFLAGS		= -L$(MLXDIR) -L$(LIBFTDIR) \
			  -L$(HOME)/.local/lib -lXext -lX11 -lXrender -lm -lmlx -lft -lrt \
			  -lasound -pthread -lpipewire-0.3 -lpulse \
			  -lpulse-simple -Wl,-rpath=$(realpath $(PAINSTALL)/lib)
CF			= $(CC) $(CFLAGS) $(IFLAGS)

# VPATH
vpath %.c $(LIBFTDIR)/$(SRCDIR) $(SRCDIR)
vpath %.h $(LIBFTDIR)/$(INCDIR) $(MLXDIR) $(INCDIR)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR)

#SRCS		= better_alsa_faders.c
SRCS		= mlx_feur.c mlx_utils.c vec2.c math_utils.c mlx_hooks.c better_alsa_faders.c osci.c color.c
#main.c audio_utils.c img_utils.c mlx.c mlx_hooks.c vec2.c

SRCS		:=$(addprefix $(SRCDIR)/, $(SRCS))
OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.d)))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo -e "$(BLUE)Creating program $(UNDERLINE)$(NAME)$(RESET)$(BLUE)...$(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) $^ $(LFLAGS) -o $@
	@echo -e "$(GREEN)$(BOLD)✓ Program $(UNDERLINE)$(NAME)$(RESET)$(GREEN)$(BOLD) successfully created!$(RESET)"

$(LIBFT):
	@echo -e "$(PURPLE)➜ Building $(UNDERLINE)libft$(RESET)"
	@$(MAKE) -s -C $(LIBFTDIR)

$(MLX):
	@echo -e "$(PURPLE)-> Building $(UNDERLINE)minilibx$(RESET)"
	@$(MAKE) -s -C $(MLXDIR) "CFLAGS=-DSTRINGPUTX11 -Ofast \
		-Wno-deprecated -Wno-return-type -Wno-parentheses -Wno-pointer-sign"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@echo -e "$(PURPLE)➜ Compiling $(UNDERLINE)$<$(RESET)"
	@$(CF) $(DFLAGS) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	@echo -e "$(BLUE)Creating directory $(UNDERLINE)$@$(RESET)"
	@mkdir -p $@

-include $(DEPS)

.PHONY: all
