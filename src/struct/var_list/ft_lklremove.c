/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lklremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:36:50 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 15:37:23 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_lklremove(t_var_list **lst, t_var_list *node)
{
	if (!lst || !*lst || !node)
		return ;
	if (node->previous)
		node->previous->next = node->next;
	else
		*lst = node->next;
	if (node->next)
		node->next->previous = node->previous;
	free(node->name);
	free(node->value);
	free(node);
}
