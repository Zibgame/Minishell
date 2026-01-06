/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:35:27 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/06 12:35:31 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**clean_empty_args(char **args)
{
	int		i;
	int		j;
	char	**new;

	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			j++;
		i++;
	}
	new = malloc(sizeof(char *) * (j + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			new[j++] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	new[j] = NULL;
	free(args);
	return (new);
}
