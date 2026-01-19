/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:34:42 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/19 13:31:07 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_redirclear(t_redir **red)
{
	t_redir	*temp;

	if (!red)
		return ;
	while (*red)
	{
		temp = (*red)->next;
		free((*red)->target);
		free(*red);
		*red = temp;
	}
	*red = NULL;
}

void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->name);
		ft_redirclear(&(*lst)->redirs);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
