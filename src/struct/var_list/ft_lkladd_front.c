/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lkladd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:34:31 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 12:34:32 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int main(void)
// {
//     t_list *a = ft_lstnew("world");
//     t_list *b = ft_lstnew("hello");
//     ft_lstadd_front(&a, b);
//     printf("%s\n", (char *)a->content);
//     return (0);
// }
