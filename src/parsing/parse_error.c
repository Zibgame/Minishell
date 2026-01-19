/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:44:14 by dadoune           #+#    #+#             */
/*   Updated: 2026/01/19 14:25:30 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	type_of_char(int type, char c)
{
	if (c == '|')
		return (PIPE * (type != PIPE) + OPERATOR * (type == PIPE));
	if (c == '<' || c == '>')
		return (REDIRECTION * (type != REDIRECTION) \
	+ OPERATOR * (type == REDIRECTION));
	return (0);
}

char	*return_error(char *err_token, int pos, int type)
{
	char	*err_return;

	if (pos % 2 != 0 && type_of_char(0, err_token[pos]) \
	== type_of_char(0, err_token[pos + 1]))
		pos++;
	else if (pos % 2 != 0)
		pos--;
	err_return = ft_calloc(ft_strlen(err_token), 1);
	err_return[0] = err_token[pos];
	if (err_token[++pos] && type_of_char(0, err_token[pos]) == type)
		err_return[1] = err_token[pos];
	return (err_return);
}

char	*token_error(char *token)
{
	int	i;
	int	type;
	int	actual;

	i = 0;
	actual = 0;
	if (token)
	{
		i = ft_strlen(token) - 1;
		type = type_of_char(0, token[i]);
	}
	while (i > 0 && token[--i])
	{
		actual = type_of_char(type, token[i]);
		if (actual == PIPE && (type == OPERATOR || type == REDIRECTION))
			return (return_error(token, i + 1, actual));
		if (actual == REDIRECTION && (type == OPERATOR || type == PIPE))
			return (return_error(token, i + 1, actual));
		type = actual;
	}
	return (ft_strdup("newline"));
}

int	has_parse_error(t_cmd *cmd)
{
	char	*err;
	t_cmd	*tmp;

	tmp = ft_cmdlast(cmd);
	if (tmp->type == REDIRECTION)
	{
		err = token_error(tmp->name);
		if (ft_strncmp(err, "newline", ft_strlen("newline")))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", err);
			free(err);
			return (1);
		}
		free(err);
	}
	while (tmp)
	{
		if (!tmp->name)
			return (0);
		if (tmp->type == PARSEERROR && ft_strncmp(tmp->name, "-", 2))
		{
			err = token_error(tmp->name);
			printf("minishell: syntax error near unexpected token `%s'\n", \
				err);
			free(err);
			return (1);
		}
		tmp = tmp->prev;
	}
	return (0);
}