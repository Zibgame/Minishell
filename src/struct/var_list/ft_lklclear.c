/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lklclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:34:42 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 12:49:13 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_var_list **lst, void (*del)(void *))
{
	t_var_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

// void del(void *p) { free(p); }
// int main(void)
// {
//     t_var_list *a = ft_lstnew(strdup("one"));
//     ft_lstadd_back(&a, ft_lstnew(strdup("two")));
//     ft_lstclear(&a, del);
//     return (0);
// }
