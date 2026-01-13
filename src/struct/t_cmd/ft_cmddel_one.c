/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmddel_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:03:23 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/13 18:27:47 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cmddelone(t_cmd *lst)
{
	t_redir	*tmp;
	
	if (!lst)
		return ;
	free(lst->name);
	while (lst->redirs)
	{
		tmp = lst->redirs->next;
		free(lst->redirs->target);
		free(lst->redirs);
		lst->redirs = tmp;
	}
	free(lst);
}
