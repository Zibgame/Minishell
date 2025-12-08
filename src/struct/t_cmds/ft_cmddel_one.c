/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmddel_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:03:23 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 12:40:17 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cmddelone(t_cmd *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	free_array(lst->args);
	free(lst);
}
