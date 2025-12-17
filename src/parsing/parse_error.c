/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:44:14 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/17 21:44:33 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	type_of_char(int type, char c)
{
	if (c == '|')
		return (PIPE * (type != PIPE) + OPERATOR * (type == PIPE));
	if (c == '<' || c == '>')
		return (REDIRECTION * (type != REDIRECTION) + OPERATOR * \
		(type == REDIRECTION));
	return (0);
	
}

char	*return_error(char *err_pos)
{
	char	*err_token;

	err_token = ft_calloc(ft_strlen(err_pos), 1);
	return (err_token);
}

char	*token_error(char *token)
{
	int	i;
	int	type;
	int	actual;

	i = 0;
	actual = 0;
	if (token)
		type = type_of_char(0, token[i]);
	while (token[++i])
	{
		actual = type_of_char(type, token[i]);
		if (actual == PIPE && type == OPERATOR)
			return("|");
		if (actual == REDIRECTION && type == OPERATOR)
		{
			
			if (token[i] == '<')
				return("<");
			return(">");
		}
		type = actual;
	}
	return (NULL);
}

int	has_parse_error(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = ft_cmdlast(cmd);
	while (tmp)
	{
		if (tmp->type == PARSEERROR && ft_strncmp(tmp->name, "-", 2))
		{
			printf("bash: syntax error near unexpected token `%s'\n", \
				token_error(tmp->name));
			return (1);
		}
		tmp = tmp->prev;
	}
	return (0);
}