/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:44:14 by dadoune           #+#    #+#             */
/*   Updated: 2026/01/26 12:58:37 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_err(char *err)
{
	if (!err)
	{
		ft_printf_fd("minishell: syntax error near unexpected token "
			"`newline'\n", 2);
		return (1);
	}
	else if (!ft_strncmp(err, ".", ft_strlen(err)))
	{
		ft_printf_fd("minishell: .: filename argument required\n"
			".: usage: . filename [arguments]\n", 2);
		return (1);
	}
	ft_printf_fd("minishell: syntax error near unexpected token "
		z"`%s'\n", 2, err);
	return (1);
}

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
	t_cmd	*tmp;

	if (!cmd || !cmd->name)
		return (0);
	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == PARSEERROR || (tmp->name && \
			!ft_strncmp(tmp->name, ".", ft_strlen(tmp->name)) && !tmp->prev))
			return (print_err(tmp->name));
		tmp = tmp->next;
	}
	return (0);
}
