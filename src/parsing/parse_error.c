/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:44:14 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/16 03:00:11 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*token_error(char *token)
{
	(void)token;
	return (NULL);
}

int	has_parse_error(t_cmd *cmd)
{
	// t_cmd	*tmp;
	(void)cmd;
	// tmp = cmd;
	// while (tmp)
	// {
	// 	if (tmp->type == PARSEERROR && ft_strncmp(tmp->name, "-", 2))
	// 	{
	// 		printf("bash: syntax error near unexpected token `%s'\n",
	// 			tmp->name);
	// 		return (1);
	// 	}
	// 	tmp = tmp->next;
	// }
	return (0);
}