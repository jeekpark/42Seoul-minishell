/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:43:09 by tnam              #+#    #+#             */
/*   Updated: 2023/04/27 20:17:05 by tnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_make_token(t_parse *parse, t_token_type type)
{
	parse->tokens[parse->tokens_i].type = type;
	ft_strlcpy(parse->temp_str, &parse->line[parse->start_i],
		parse->line_i - parse->start_i + 2);
	parse->tokens[parse->tokens_i].str = ft_strdup(parse->temp_str);
	if (parse->tokens[parse->tokens_i].str == NULL)
		return (ft_error("Failed malloc token->str", FAILURE));
	parse->tokens_i++;
	return (SUCCESS);
}
