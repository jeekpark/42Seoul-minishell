/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:35:23 by tnam              #+#    #+#             */
/*   Updated: 2023/05/29 15:44:16 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_path_check(char *cmd_path)
{
	DIR	*dir;

	dir = opendir(cmd_path);
	if (dir != NULL)
	{
		ft_printf_err("%s: is a directory\n", cmd_path);
		exit(126);
	}
	if (cmd_path == NULL || access(cmd_path, X_OK) == SUCCESS)
		return (SUCCESS);
	if (cmd_path[0] == '\0')
		return (FAILURE);
	return (SUCCESS);
}
