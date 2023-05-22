/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:18:43 by tnam              #+#    #+#             */
/*   Updated: 2023/05/22 22:20:25 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_make_path(t_exec_info *exec_info, char *path)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		exit(EXIT_FAILURE);
	result = ft_strjoin(temp, exec_info->cmd_path);
	if (result == NULL)
	{
		free(temp);
		exit(EXIT_FAILURE);
	}
	free(temp);
	return (result);
}

static int	ft_find_cmd(t_exec *exec, t_exec_info *exec_info)
{
	size_t	i;
	char	*cmd_path;

	if (access(exec_info->cmd_path, X_OK) == SUCCESS)
		return (SUCCESS);
	i = 0;
	while (exec->path_envp[i])
	{
		cmd_path = ft_make_path(exec_info, exec->path_envp[i]);
		if (access(cmd_path, X_OK) == SUCCESS)
		{
			exec_info->cmd_path = cmd_path;
			return (SUCCESS);
		}
		free(cmd_path);
		i++;
	}
	return (FAILURE);
}

void	ft_exec_cmd(t_info *info, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{
	if (ft_find_cmd(exec, exec_info) == FAILURE)
	{
		ft_free_all(parse, exec);
		ft_cmd_not_found_error(exec_info);
	}
	else
	{
		execve(exec_info->cmd_path, exec_info->cmd, info->envp); // test
	}
}
