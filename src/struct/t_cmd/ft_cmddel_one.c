/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmddel_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:03:23 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 20:24:05 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cmddelone(t_cmd *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	free(lst);
}
