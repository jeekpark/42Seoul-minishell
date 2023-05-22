/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:21:28 by tnam              #+#    #+#             */
/*   Updated: 2023/05/22 22:03:16 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parent(t_exec *exec, t_exec_info *exec_info)
{
	if (close(exec_info->pipe_fd[OUT]) == FAILURE)
		return (ft_perror(FAILURE));
	if (exec->prev_pipe_fd != NONE)
	{
		if (close(exec->prev_pipe_fd) == FAILURE)
			return (ft_perror(FAILURE));
	}
	if (exec_info->use_pipe == TRUE)
		exec->prev_pipe_fd = exec_info->pipe_fd[IN];
	return (SUCCESS);
}

static int	ft_make_child(t_info *info, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{
	exec_info->pid = fork();
	if (exec_info->pid == FAILURE)
	{
		ft_free_all(parse, exec);
		return (ft_perror(FAILURE));
	}
	else if (exec_info->pid == CHILD)
		ft_exec_cmd(info, parse, exec, exec_info);
	else
	{
		if (ft_parent(exec, exec_info) == FAILURE)
		{
			ft_free_all(parse, exec);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	ft_wait_child(t_exec *exec)
{
	int	child_status;

	exec->exec_arr_i = 0;
	while (exec->exec_arr_i < exec->exec_arr_size)
	{
		if (waitpid(-1, &child_status, 0) == FAILURE)
			return (ft_perror(FAILURE));
		exec->child_exit_code = WEXITSTATUS(child_status);
		exec->exec_arr_i++;
	}
	return (SUCCESS);
}

int	ft_exec(t_info *info, t_parse *parse, t_exec *exec)
{
	t_exec_info	*exec_info;

	while (exec->exec_arr_i < exec->exec_arr_size)
	{
		exec_info = &exec->exec_arr[exec->exec_arr_i];
		if (exec_info->use_pipe == TRUE)
		{
			if (pipe(exec_info->pipe_fd) == FAILURE)
			{
				ft_free_all(parse, exec);
				return (ft_perror(FAILURE));
			}
		}
		if (ft_make_child(info, parse, exec, exec_info) == FAILURE)
			return (FAILURE);
		exec->exec_arr_i++;
	}
	ft_wait_child(exec);
	return (SUCCESS);
}
