/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lkladd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:16:52 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/05 14:12:53 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_lkladd_front(t_var_list **lst, t_var_list *new)
{
	if (new != NULL)
	{
		if (lst != NULL)
		{
			(*lst)->previous = new;
			new->next = *lst;
			*lst = new;
		}
		else
			lst = &new;
	}
}
