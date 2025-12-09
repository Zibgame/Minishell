/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:51:28 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/09 17:10:07 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	verify_two(char	*to_check)
{
	if(to_check)
	{
		if (ft_strlen(to_check) > 2)
			return (2);
		if (ft_strlen(to_check) == 2)
			return (2 * (to_check[0] != to_check[1]));
	}
	return (0);
}

static int	m_split(t_cmd *cmd, char **to_fill, int size)
{
	int	i;
	int	len;
	int state;
	int words;

	i = 0;
	len = 0;
	words = 0;
	state = ft_isalnum(cmd->name[0]);
	to_fill = ft_calloc(size * sizeof(char *), 1);
	while (cmd->name[i])
	{
		if (state != ft_isalnum(cmd->name))
		{
			to_fill[words] = ft_strndup(&cmd->name[i - len], len);
			len = 0;
			words++;
		}
		len++;
		i++;
	}
	if (len > 1)
		to_fill[words++] = ft_strndup(&cmd->name[i - len], len);
	to_fill[words] = NULL;
	return (0);
}

int	redirect_split(t_cmd *cmd, char **to_fill)
{
	int	i;
	int	nb;
	int	nb_appear;
	
	i = -1;
	nb = 0;
	nb_appear = 0;
	while (cmd->name[++i])
	{
		if (cmd->name[i] == '<' || cmd->name[i] == '>')
		{
			nb++;
			if (nb == 3)
				return (2);
		}
		else
		{
			if (nb != 0)
				nb_appear += 1;
			nb = 0;
		}
	}
	if (nb != 0)
		return (verify_two(cmd->name));
	return (m_split(cmd, to_fill, (nb_appear * 2 + 2)));
}
