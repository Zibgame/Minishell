/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lklsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:02:52 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/19 15:06:24 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_lklsize(t_var_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	free_all(int sig)
{
	char	**false_argv;
	
	(void)sig;
	false_argv = ft_calloc(2, sizeof(char *));
	false_argv[0] = "./true";
	execve("/usr/bin/true", false_argv, NULL);
}