/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:18:43 by tnam              #+#    #+#             */
/*   Updated: 2023/05/24 14:58:05 by tnam             ###   ########.fr       */
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

	if (exec_info->cmd_path == NULL
		|| access(exec_info->cmd_path, X_OK) == SUCCESS)
		return (SUCCESS);
	if (exec_info->cmd_path[0] == '\0')
		return (FAILURE);
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

static void	ft_set_fd(t_exec *exec, t_exec_info *exec_info)
{
	ft_set_pipe_fd(exec, exec_info);
	ft_set_redirect_fd(exec_info);
	if (exec_info->infile_fd != NONE)
	{
		if (dup2(exec_info->infile_fd, STDIN_FILENO) == FAILURE)
			exit (ft_perror(errno));
		if (close(exec_info->infile_fd) == FAILURE)
			exit (ft_perror(errno));
	}
	if (exec_info->outfile_fd != NONE)
	{
		if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
			exit (ft_perror(errno));
		if (close(exec_info->outfile_fd) == FAILURE)
			exit (ft_perror(errno));
	}
}

static char	**ft_make_envp(t_list *mini_envp)
{
	char	**envp;
	size_t	count;
	t_node	*node;

	count = 0;
	node = mini_envp->front_node;
	while (node->next_node != NULL)
	{
		count++;
		node = node->next_node;
	}
	envp = (char **)ft_calloc(count + 1, sizeof(char *));
	count = 0;
	node = mini_envp->front_node;
	while (node->next_node != NULL)
	{
		envp[count] = (char *)node->content;
		node = node->next_node;
	}
	return (envp);
}

void	ft_exec_cmd(t_info *info, t_parse *parse,
	t_exec *exec, t_exec_info *exec_info)
{
	if (ft_is_builtin(exec_info) == FALSE
		&& ft_find_cmd(exec, exec_info) == FAILURE)
	{
		printf("%s: command not found\n", exec_info->cmd[0]);
		ft_free_all(parse, exec);
		exit(127);
	}
	else
	{
		ft_set_fd(exec, exec_info);
		if (exec_info->cmd_path == NULL)
			exit (EXIT_SUCCESS);
		if (ft_is_builtin(exec_info) == TRUE)
			ft_exec_builtin(info, parse, exec, exec_info);
		else
			execve(exec_info->cmd_path, exec_info->cmd,
				ft_make_envp(&info->mini_envp));
	}
}
