/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:30:14 by tnam              #+#    #+#             */
/*   Updated: 2023/05/18 15:11:43 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* print test function */
void	print_tokens(t_parse *parse)
{
	char	*type;

	printf("\n=========\n");
	for (size_t i = 0; i < parse->token_count; i++)
	{
		if (parse->tokens[i].type == WORD)
			type = "WORD";
		if (parse->tokens[i].type == PIPE)
			type = "PIPE";
		if (parse->tokens[i].type == REDIRECT)
			type = "REDIRECT";
		printf("Token%zu type = %s\n", i + 1, type);
		printf("Token%zu str = %s\n", i + 1, parse->tokens[i].str);
		printf("---------\n");
	}
	printf("=========\n\n");
}

static void	ft_parse_execute(t_info *info, t_parse *parse, t_exec *exec)
{
	if (ft_parse(info, parse) == FAILURE)
		return ;
	if (ft_make_exec_info(parse, exec) == FAILURE)
		return ;
	print_tokens(parse); // test
	ft_free_tokens(parse, parse->token_count);
	ft_free_exec(exec, exec->exec_arr_size);
}

void leaks() // memory leak test
{
	system("leaks -q $PPID");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info		info;
	t_parse		parse;
	t_exec		exec;

	atexit(leaks); // memory leaks test
	ft_init(argc, argv, envp, &info);
	while (TRUE)
	{
		parse.line = readline("whine 🍷 ");
		if (parse.line == NULL)
		{
			ft_list_clear(&info.mini_envp);
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[9C", STDOUT_FILENO);
			printf("exit\n");
			return (EXIT_SUCCESS);
		}
		add_history(parse.line);
		ft_parse_execute(&info, &parse, &exec);
		free(parse.line);
	}
	return (EXIT_SUCCESS);
}
