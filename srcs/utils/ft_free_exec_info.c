/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:06:35 by tnam              #+#    #+#             */
/*   Updated: 2023/05/18 17:04:01 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exec(t_exec *exec, size_t exec_size)
{
	size_t	i;

	i = 0;
	while (i < exec_size)
	{
		/* exec_info들의 free 추가 필요 */
		free(exec->exec_arr[i].cmd);
		i++;
	}
	free(exec->exec_arr);
}
