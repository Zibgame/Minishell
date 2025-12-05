/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lkladd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:34:31 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 12:51:14 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lklstadd_front(t_var_list **lst, t_var_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	new->prevouis = NULL;
	*lst = new;
}

// int main(void)
// {
//     t_var_list *a = ft_lstnew("world");
//     t_var_list *b = ft_lstnew("hello");
//     ft_lstadd_front(&a, b);
//     printf("%s\n", (char *)a->content);
//     return (0);
// }
