/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:34:42 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 13:20:55 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->name);
		free_array((*lst)->args);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

// void del(void *p) { free(p); }
// int main(void)
// {
//     t_cmd *a = ft_lstnew(strdup("one"));
//     ft_lstadd_back(&a, ft_lstnew(strdup("two")));
//     ft_lstclear(&a, del);
//     return (0);
// }
