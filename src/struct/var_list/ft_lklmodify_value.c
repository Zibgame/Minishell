/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lklmodify_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:23:17 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/09 13:15:16 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_lkl_modify(t_var_list **lst, char *value)
{
	if (lst && *lst)
	{
		free((*lst)->value);
		(*lst)->value = value;
	}
}