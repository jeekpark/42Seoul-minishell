# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 17:24:05 by tnam              #+#    #+#              #
#    Updated: 2023/05/22 21:55:38 by tnam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -f

INCLUDES		=	includes/

LIBFT_DIR		=	srcs/libft
LIBFT			=	libft.a
LIBFT_C			=	-L$(LIBFT_DIR) -lft

SRCS			=	srcs/main.c							\
					srcs/utils/ft_error.c				\
					srcs/utils/ft_perror.c				\
					srcs/utils/ft_cmd_not_found_error.c	\
					srcs/utils/ft_is_space.c			\
					srcs/utils/ft_is_operator.c			\
					srcs/utils/ft_is_redirect.c			\
					srcs/utils/ft_is_quote.c			\
					srcs/utils/ft_is_env.c				\
					srcs/utils/ft_is_heredoc.c			\
					srcs/utils/ft_free_tokens.c			\
					srcs/utils/ft_free_exec.c			\
					srcs/utils/ft_free_all.c			\
					srcs/ft_list/ft_list_del_node.c		\
					srcs/ft_list/ft_list_init.c			\
					srcs/ft_list/ft_list_push_back.c	\
					srcs/ft_list/ft_list_clear.c		\
					srcs/0_init/ft_init.c				\
					srcs/0_init/ft_sig_init.c			\
					srcs/0_init/ft_mini_envp_init.c		\
					srcs/1_parsing/ft_parse.c			\
					srcs/1_parsing/ft_count_token.c		\
					srcs/1_parsing/ft_tokenization.c	\
					srcs/1_parsing/ft_make_token.c		\
					srcs/1_parsing/ft_convert_env.c		\
					srcs/1_parsing/ft_remove_quote.c	\
					srcs/1_parsing/ft_syntax_check.c	\
					srcs/2_make_exec_info/ft_make_exec_info.c	\
					srcs/2_make_exec_info/ft_set_exec_info.c	\
					srcs/3_exec/ft_exec.c				\
					srcs/3_exec/ft_exec_cmd.c			\
					
					
OBJS			=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_C) -o $(NAME) \
	-lreadline -L${HOME}/.brew/opt/readline/lib \
	-L/usr/local/opt/readline/lib

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -I${HOME}/.brew/opt/readline/include \
	-I/usr/local/opt/readline/include -c $< -o $@ 

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY : all bonus clean fclean re