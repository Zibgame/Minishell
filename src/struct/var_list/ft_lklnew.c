/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lklnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:34:31 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 13:33:48 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_var_list	*ft_lklnew(char *name, char *value)
{
	t_var_list	*elem;

	elem = malloc(sizeof(t_var_list));
	if (!elem)
		return (NULL);
	elem->name = name;
	elem->value = value;
	elem->next = NULL;
	elem->previous = NULL;
	return (elem);
}
