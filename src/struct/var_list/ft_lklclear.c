/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lklclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:34:42 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/17 19:41:12 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_lklclear(t_var_list **lst)
{
	t_var_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->name)
			free((*lst)->name);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
