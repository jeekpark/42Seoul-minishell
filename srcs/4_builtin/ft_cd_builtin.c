/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:39:21 by tnam              #+#    #+#             */
/*   Updated: 2023/06/02 08:56:50 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_builtin(t_exec_info *exec_info)
{
	char	*path;

	path = exec_info->cmd[1];
	if (path == NULL)
		exit (SUCCESS);
	if (chdir(path) == FAILURE)
	{
		g_child_exit_code = 1;
		exit (ft_perror(FAILURE));
	}
	exit (SUCCESS);
}
