/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:49:54 by jeekpark          #+#    #+#             */
/*   Updated: 2023/05/26 14:32:29 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static void	ft_exit_builtin_arg_check(t_exec *exec, size_t i, int sign_flag)
{
	while (exec->exec_arr[exec->exec_arr_i].cmd[1][i])
	{
		if (ft_isnum(exec->exec_arr[exec->exec_arr_i].cmd[1][i]))
			i++;
		else
		{
			ft_printf_err("exit\nexit: %s: numeric argument required\n",
				exec->exec_arr[exec->exec_arr_i].cmd[1]);
			exit(255);
		}
	}
	if (i == 1 && sign_flag == TRUE)
	{
		ft_printf_err("exit\nexit: %s: numeric argument required\n",
			exec->exec_arr[exec->exec_arr_i].cmd[1]);
		exit(255);
	}
}

static int	ft_exit_builtin_isnum(t_exec *exec)
{
	size_t	i;
	int		sign_flag;

	sign_flag = FALSE;
	i = 0;
	if ((exec->exec_arr[exec->exec_arr_i].cmd[1][0] == '-')
		|| (exec->exec_arr[exec->exec_arr_i].cmd[1][0] == '+'))
	{
		sign_flag = TRUE;
		i++;
	}
	ft_exit_builtin_arg_check(exec, i, sign_flag);
	return (SUCCESS);
}

int	ft_exit_builtin(t_list *mini_envp, t_parse *parse, t_exec *exec)
{
	int	exit_value;

	if ((exec->exec_arr[exec->exec_arr_i].cmd[1]) == NULL)
	{
		ft_list_clear(mini_envp);
		ft_free_all(parse, exec);
		exit(0);
	}
	if (exec->exec_arr[exec->exec_arr_i].cmd[2])
	{
		ft_printf_err("exit: too many arguments\n");
		g_child_exit_code = 1;
		return (FAILURE);
	}
	if (ft_exit_builtin_isnum(exec) == FAILURE)
		return (FAILURE);
	exit_value = ft_atoi(exec->exec_arr[exec->exec_arr_i].cmd[1]);
	ft_list_clear(mini_envp);
	ft_free_all(parse, exec);
	printf("exit\n");
	exit(exit_value);
}
