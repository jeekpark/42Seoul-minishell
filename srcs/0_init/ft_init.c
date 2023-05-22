/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:18:06 by tnam              #+#    #+#             */
/*   Updated: 2023/05/22 22:59:47 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(int argc, char **argv, char **envp, t_info *info)
{
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
	ft_sig_init();
	//ft_mini_envp_init(envp, info);
}
