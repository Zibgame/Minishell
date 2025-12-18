/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:44:14 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/18 11:12:31 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	type_of_char(int type, char c)
{
	if (c == '|')
		return (PIPE * (type != PIPE) + OPERATOR * (type == PIPE));
	if (c == '<' || c == '>')
		return (REDIRECTION * (type != REDIRECTION) + OPERATOR * (type == REDIRECTION));
	return (0);
}

char	*return_error(char *err_token, int pos, int type)
{
	char	*err_return;

	printf("{%s}=>(%d, %d)\n", err_token, pos, type_of_char(0, err_token[pos]) == type_of_char(0, err_token[pos+1]));
	if (pos % 2 != 0 && type_of_char(0, err_token[pos]) == type_of_char(0, err_token[pos+1]))
		pos++;
	else if (pos % 2 != 0)
		pos--;
	printf("{%s}=>(%d, %d)\n", err_token, pos, type);
	// pos -= 1 * (type_of_char(0, err_token[pos - 1]) != type);
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
			return(return_error(token, i + 1, actual));
		if (actual == REDIRECTION && (type == OPERATOR || type == PIPE))
		{
			printf("|%d|", i);
			return(return_error(token, i + 1, actual));
		}
		type = actual;
	}
	return (ft_strdup("newline"));
}

int	has_parse_error(t_cmd *cmd)
{
	char	*err;
	t_cmd	*tmp;

	tmp = ft_cmdlast(cmd);
	while (tmp)
	{
		if (tmp->type == PARSEERROR && ft_strncmp(tmp->name, "-", 2))
		{
			err = token_error(tmp->name);
			printf("bash: syntax error near unexpected token `%s'\n", \
				err);
			free(err);
			return (1);
		}
		tmp = tmp->prev;
	}
	return (0);
}
