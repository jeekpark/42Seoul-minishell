/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:39:21 by tnam              #+#    #+#             */
/*   Updated: 2023/05/26 14:51:16 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_builtin(t_exec_info *exec_info)
{
	char	*path;

	path = exec_info->cmd[1];
	if (path == NULL)
		return (SUCCESS);
	if (chdir(path) == FAILURE)
	{
		g_child_exit_code = 1;
		return (ft_perror(FAILURE));
	}
	return (SUCCESS);
}
