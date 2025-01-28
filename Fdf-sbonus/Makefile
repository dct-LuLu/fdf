# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 13:56:12 by jaubry--          #+#    #+#              #
#    Updated: 2025/01/28 10:42:01 by jaubry--         ###   ########.fr        #
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
SRCDIR		= src
OBJDIR		= ../.obj/$(SRCDIR)
DEPDIR		= ../.dep/$(SRCDIR)
LIBFTDIR	= ../libft
MLXDIR		= ../minilibx-linux
PADIR		= ../portaudio
PAINSTALL	= $(PADIR)/install

# Output
NAME		= ../oscilloscope_visualizer
LIBFT		= $(LIBFTDIR)/libft.a
MLX			= $(MLXDIR)/libmlx.a
PA			= $(PAINSTALL)/lib/libportaudio.a

# Compiler and flags
WIDTH		= 1000
HEIGHT		= 1000

CC			= cc -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT)
CFLAGS		= -Wall -Wextra -Werror -D_REENTRANT
DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d
IFLAGS		= -I$(INCDIR) -I$(LIBFTDIR)/include -I$(MLXDIR) -I$(PAINSTALL)/include -I/usr/include/pipewire-0.3 -I/usr/include/spa-0.2 
LFLAGS		= -L$(MLXDIR) -L$(LIBFTDIR) -L$(PAINSTALL)/lib -L$(HOME)/.local/lib -lXext -lX11 -lm -lmlx -lft -lrt -lasound -pthread -lportaudio -lpipewire-0.3 -lpulse -lpulse-simple -Wl,-rpath=$(realpath $(PAINSTALL)/lib)
CF			= $(CC) $(CFLAGS) $(IFLAGS)

# VPATH
vpath %.c $(LIBFTDIR)/$(SRCDIR) $(SRCDIR)
vpath %.h $(LIBFTDIR)/$(INCDIR) $(MLXDIR) $(INCDIR)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR)

SRCS		= pulse_audio_fader.c

SRCS		:=$(addprefix $(SRCDIR)/, $(SRCS))
OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.d)))

#gcc main.c libportaudio.a -lrt -lm -lasound -ljack -pthread -o YOUR_BINARY

all: $(NAME)

$(NAME): $(PA) $(LIBFT) $(MLX) $(OBJS)
	@echo -e "$(BLUE)Creating program $(UNDERLINE)$(NAME)$(RESET)$(BLUE)...$(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) $^ $(LFLAGS) -o $@
	@echo -e "$(GREEN)$(BOLD)✓ Program $(UNDERLINE)$(NAME)$(RESET)$(GREEN)$(BOLD) successfully created!$(RESET)"

$(LIBFT):
	@echo -e "$(PURPLE)➜ Building $(UNDERLINE)libft$(RESET)"
	@$(MAKE) -s -C $(LIBFTDIR)

$(MLX):
	@echo -e "$(PURPLE)-> Building $(UNDERLINE)minilibx$(RESET)"
	@$(MAKE) -s -C $(MLXDIR)

$(PA): $(PAINSTALL)
	@echo -e "$(PURPLE)-> Building $(UNDERLINE)portaudio$(RESET)"
	# we enter in the pa_stable dir to avoid junk file in the position where the user calls make
	@echo -e "$(PURPLE)Installing PortAudio to: $(UNDERLINE)$(realpath $(PAINSTALL))$(RESET)"
	# wasnt able to setup some sort of auto configure, because calling it from the makefile doesnt seem to work
	#"cd $(realpath $(PADIR))/pa_stable_v190700_20210406 && ./configure --with-alsa --without-jack --without-sndio --without-oss --prefix=$(realpath $(PAINSTALL))")

	make -C $(PADIR)/pa_stable_v190700_20210406
	make -C $(PADIR)/pa_stable_v190700_20210406 install

$(PAINSTALL):
	@echo -e "$(BLUE)Creating directory $(UNDERLINE)$@$(RESET)"
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@echo -e "$(PURPLE)➜ Compiling $(UNDERLINE)$<$(RESET)"
	@$(CF) $(DFLAGS) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	@echo -e "$(BLUE)Creating directory $(UNDERLINE)$@$(RESET)"
	@mkdir -p $@

-include $(DEPS)

.PHONY: all
