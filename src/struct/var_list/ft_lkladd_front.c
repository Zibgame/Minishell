/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lkladd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:16:52 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/05 13:32:40 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lkladd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		if (lst != NULL)
		{
			new->next = *lst;
			*lst = new;
		}
		else
			lst = &new;
	}
}
