# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 15:56:40 by jaubry--          #+#    #+#              #
#    Updated: 2024/12/11 21:48:55 by jaubry--         ###   ########.fr        #
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
SRCDIR		= .
OBJDIR		= .obj
DEPDIR		= .dep
INCDIR		= .
LIBFTDIR	= libft
MLXDIR		= minilibx-linux

# Output
NAME		= fdf
LIBFT		= $(LIBFTDIR)/libft.a

# Compiler and flags
WIDTH		= 1000
HEIGHT		= 1000

CC			= cc -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT)
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d
IFLAGS		= -I$(INCDIR) -I$(LIBFTDIR)/include -I$(MLXDIR)
LFLAGS		= -L$(MLXDIR) -lXext -lX11 -lm -lmlx
CF			= $(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS)

# VPATH
vpath %.c $(SRCDIR) $(LIBFTDIR)/$(SRCDIR)
vpath %.h $(INCDIR) $(LIBFTDIR)/$(INCDIR) $(MLXDIR)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR)

# Sources
SRCS		= main.c mlx_utils.c parse_map.c parse_map_utils.c vec.c \
			  str_utils.c utils.c math_utils.c map_utils.c mlx_hooks.c \
			  draw_utils.c

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.d)))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo -e "$(BLUE)Creating program $(UNDERLINE)$(NAME)$(RESET)$(BLUE)...$(RESET)"
	@$(CF) $^ $(LFLAGS) -o $@
	@echo -e "$(GREEN)$(BOLD)✓ Program $(UNDERLINE)$(NAME)$(RESET)$(GREEN)$(BOLD) successfully created!$(RESET)"

$(LIBFT):
	@echo -e "$(PURPLE)➜ Building $(UNDERLINE)libft$(RESET)"
	@$(MAKE) -s -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@echo -e "$(PURPLE)➜ Compiling $(UNDERLINE)$<$(RESET)"
	@$(CF) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	@echo -e "$(BLUE)Creating directory $(UNDERLINE)$@$(RESET)"
	@mkdir -p $@

clean:
	@$(MAKE) -s -C $(LIBFTDIR) clean
	@echo -e "$(RED)Cleaning $(UNDERLINE)$(NAME)$(RESET)$(RED) object files from $(UNDERLINE)$(OBJDIR)$(RESET)$(RED) and $(UNDERLINE)$(DEPDIR)$(RESET)"
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean:
	@$(MAKE) -s -C $(LIBFTDIR) fclean
	@echo -e "$(RED)Cleaning $(UNDERLINE)$(NAME)$(RESET)$(RED) object files from $(UNDERLINE)$(OBJDIR)$(RESET)$(RED) and $(UNDERLINE)$(DEPDIR)$(RESET)"
	@rm -rf $(OBJDIR) $(DEPDIR)
	@echo -e "$(RED)Removing program $(UNDERLINE)$(NAME)$(RESET)"
	@rm -f $(NAME)

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

.PHONY: all clean fclean re debug help

