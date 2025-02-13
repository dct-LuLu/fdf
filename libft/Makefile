# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 01:19:17 by jaubry--          #+#    #+#              #
#    Updated: 2025/01/10 09:11:49 by jaubry--         ###   ########lyon.fr    #
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
SRCDIR		= src
OBJDIR		= .obj/
DEPDIR		= .dep/
INCDIR		= include
DPRINTF_DIR	= $(SRCDIR)/ft_dprintf
DHANDL_DIR	= $(DPRINTF_DIR)/handlers
GNL_DIR		= $(SRCDIR)/get_next_line

# Output
NAME		= libft.a

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d
IFLAGS		= -I$(INCDIR)
CF			= $(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS)

AR			= ar
ARFLAGS		= rcs

# VPATH
vpath %.c $(SRCDIR) $(DPRINTF_DIR) $(DHANDL_DIR) $(GNL_DIR)
vpath %.h $(INCDIR)
vpath %.o $(OBJDIR)
vpath %.d $(DEPDIR)

# Regular libft sources
SRCS		= ft_atoi.c ft_isascii.c ft_memcmp.c ft_putendl_fd.c \
			  ft_strdup.c ft_strlen.c ft_strtrim.c ft_bzero.c \
              ft_isdigit.c ft_memcpy.c ft_putnbr_fd.c ft_striteri.c \
              ft_strmapi.c ft_substr.c ft_calloc.c ft_isprint.c \
              ft_memmove.c ft_putstr_fd.c ft_strjoin.c ft_strncmp.c \
              ft_tolower.c ft_isalnum.c ft_itoa.c ft_memset.c \
              ft_split.c ft_strlcat.c ft_strnstr.c ft_toupper.c \
              ft_isalpha.c ft_memchr.c ft_putchar_fd.c ft_strchr.c \
              ft_strlcpy.c ft_strrchr.c strr_utils.c ratoi.c \
              ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
              ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
              ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
              freejoin.c count_tokens.c is_in.c ft_strndup.c ft_strcmp.c \
              ft_strstr.c

# Printf and dprintf sources
DPRINTF_SRCS= ft_handlers_utils.c ft_put_hex.c ft_putnbr.c write_utils.c
DPRINTF_SRCS:= $(addprefix $(DHANDL_DIR)/, $(DPRINTF_SRCS)) \
			   $(DPRINTF_DIR)/ft_dprintf.c

GNL_SRCS	= get_next_line.c get_next_line_utils.c
GNL_SRCS	:= $(addprefix $(GNL_DIR)/, $(GNL_SRCS))

SRCS		+= $(DPRINTF_SRCS) $(GNL_SRCS)

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.o=.d)))
INCLUDES	= libft.h ft_dhandlers.h get_next_line.h



all: $(NAME)

$(NAME): $(OBJS)
	@echo -e "$(BLUE)Creating library $(UNDERLINE)$(NAME)$(RESET)$(BLUE)...$(RESET)"
	@$(AR) $(ARFLAGS) $@ $^
	@echo -e "$(GREEN)$(BOLD)✓ Library $(UNDERLINE)$(NAME)$(RESET)$(GREEN)$(BOLD) successfully created!$(RESET)"

$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR)
	@echo -e "$(PURPLE)➜ Compiling $(UNDERLINE)libft/$<$(RESET)"
	@$(CF) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	@echo -e "$(BLUE)Creating directory $(UNDERLINE)libft/$@$(RESET)"
	@mkdir -p $@

debug: CFLAGS += -g
debug:
	@echo -e "$(YELLOW)$(BOLD)⚠ Building $(NAME) in debug mode...$(RESET)"
	@$(MAKE) -s -B
	@echo -e "$(YELLOW)$(BOLD)✓ $(NAME) debug build complete$(RESET)"

help:
	@echo "Available targets:"
	@echo "  all     : Build the library"
	@echo "  clean   : Remove object files"
	@echo "  fclean  : Remove object files and library"
	@echo "  re      : Rebuild everything"

clean:
	@echo -e "$(RED)Cleaning temporary libft files from $(UNDERLINE)$(OBJDIR)$(RESET)$(RED) and $(UNDERLINE)$(DEPDIR)$(RESET)"
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean: clean
	@echo -e "$(RED)Removing library $(UNDERLINE)$(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re debug help
