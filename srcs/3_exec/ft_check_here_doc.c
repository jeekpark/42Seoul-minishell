/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:58:51 by tnam              #+#    #+#             */
/*   Updated: 2023/05/24 14:28:06 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_here_doc(t_redirect *redirect)
{
	char	*input;
	char	*limiter;
	int		temp_fd;

	temp_fd = open("/tmp/whine", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (temp_fd == FAILURE)
		return (ft_perror(FAILURE));
	limiter = ft_strjoin(redirect->value, "\n");
	if (limiter == NULL)
		return (ft_error("limiter malloc failed.", FAILURE));
	while (TRUE)
	{
		write(1, "> ", 2);
		input = get_next_line(STDIN_FILENO);
		if (!input || ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(temp_fd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	free(limiter);
	if (close(temp_fd) == FAILURE)
		return (ft_perror(FAILURE));
	return (SUCCESS);
}

int	ft_check_here_doc(t_exec *exec)
{
	t_exec_info	*exec_info;
	t_redirect	*redirect;

	exec->exec_arr_i = 0;
	while (exec->exec_arr_i < exec->exec_arr_size)
	{
		exec_info = &exec->exec_arr[exec->exec_arr_i];
		exec_info->redirect_i = 0;
		while (exec_info->redirect[exec_info->redirect_i].value != 0)
		{
			redirect = &exec_info->redirect[exec_info->redirect_i];
			if (redirect->type == HERE_DOC)
				if (ft_get_here_doc(redirect) == FAILURE)
					return (FAILURE);
			exec_info->redirect_i++;
		}
		exec->exec_arr_i++;
	}
	return (SUCCESS);
}
