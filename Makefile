# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 15:56:40 by jaubry--          #+#    #+#              #
#    Updated: 2024/12/16 19:51:19 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

ifeq ($(filter bonus sbonus,$(MAKECMDGOALS)),)
    include Fdf/fdf.mk
endif

ifeq ($(MAKECMDGOALS), bonus)
	include Fdf-bonus/bonus.mk
endif

ifeq ($(MAKECMDGOALS), sbonus)
	include Fdf-sbonus/sbonus.mk
endif

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
OBJDIR		= .obj/$(SRCDIR)
DEPDIR		= .dep/$(SRCDIR)
LIBFTDIR	= libft
MLXDIR		= minilibx-linux

# Output
LIBFT		= $(LIBFTDIR)/libft.a

# Compiler and flags
WIDTH		= 1500
HEIGHT		= 1500

CC			= cc -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT)
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d
IFLAGS		= -I$(INCDIR) -I$(LIBFTDIR)/include -I$(MLXDIR)
LFLAGS		= -L$(MLXDIR) -lXext -lX11 -lm -lmlx
CF			= $(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS)

# VPATH
vpath %.c $(LIBFTDIR)/$(SRCDIR)
vpath %.h $(LIBFTDIR)/$(INCDIR) $(MLXDIR)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR)

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.d)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) | mlx
	@echo -e "$(BLUE)Creating program $(UNDERLINE)$(NAME)$(RESET)$(BLUE)...$(RESET)"
	$(CC) $(CFLAGS) $(IFLAGS) $^ $(LFLAGS) -o $@
	@echo -e "$(GREEN)$(BOLD)✓ Program $(UNDERLINE)$(NAME)$(RESET)$(GREEN)$(BOLD) successfully created!$(RESET)"

$(LIBFT):
	@echo -e "$(PURPLE)➜ Building $(UNDERLINE)libft$(RESET)"
	@$(MAKE) -s -C $(LIBFTDIR)

mlx:
	@echo -e "$(PURPLE)-> Building $(UNDERLINE)minilibx$(RESET)"
	@$(MAKE) -s -C $(MLXDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@echo -e "$(PURPLE)➜ Compiling $(UNDERLINE)$<$(RESET)"
	@$(CF) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	@echo -e "$(BLUE)Creating directory $(UNDERLINE)$@$(RESET)"
	@mkdir -p $@

clean:
	@$(MAKE) -s -C $(LIBFTDIR) clean
	@echo -e "$(RED)Cleaning $(UNDERLINE)$(NAME)$(RESET)$(RED) object files from $(UNDERLINE).obj$(RESET)$(RED) and $(UNDERLINE).dep$(RESET)"
	@rm -rf $(firstword $(subst /,\ ,$(OBJDIR))) $(firstword $(subst /,\ ,$(DEPDIR)))

fclean:
	@$(MAKE) -s -C $(LIBFTDIR) fclean
	@echo -e "$(RED)Cleaning $(UNDERLINE)$(NAME)$(RESET)$(RED) object files from $(UNDERLINE).obj$(RESET)$(RED) and $(UNDERLINE).dep$(RESET)"
	@rm -rf $(firstword $(subst /,\ ,$(OBJDIR))) $(firstword $(subst /,\ ,$(DEPDIR)))
	@echo -e "$(RED)Removing program $(UNDERLINE)$(NAME)$(RESET)"
	@rm -f fdf bonus sbonus

re: fclean all

debug:
	@echo -e "$(YELLOW)$(BOLD)⚠ Building in debug mode...$(RESET)"
	@$(MAKE) -s -C $(LIBFTDIR) debug
	@$(MAKE) -s CC="cc -g -D DEBUG=1 -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT)" -B $(OBJS)
	@$(MAKE) -s CC="cc -g -D DEBUG=1 -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT)" $(NAME)
	@echo -e "$(YELLOW)$(BOLD)✓ Debug build complete$(RESET)"

help:
	@echo "Available targets:"
	@echo "  all     : Build the program"
	@echo "  clean   : Remove object files"
	@echo "  fclean  : Remove object files and program"
	@echo "  re      : Rebuild everything"
	@echo "  debug   : Build with debug symbols"

-include $(DEPS)

.PHONY: all clean fclean re debug help mlx

