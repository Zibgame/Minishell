/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:16:52 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/08 13:20:34 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cmdadd_front(t_cmd **lst, t_cmd *new)
{
	if (new != NULL)
	{
		if (lst != NULL)
		{
			(*lst)->prev = new;
			new->next = *lst;
			*lst = new;
		}
		else
			lst = &new;
	}
}
