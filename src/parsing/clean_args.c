/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:35:27 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/13 10:36:36 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	count_something(char **args, int *i, int *j)
{
	while (args[*i])
	{
		if (args[*i][0] != '\0')
			(*j)++;
		(*i)++;
	}
}

char	**clean_empty_args(char **args)
{
	int		i;
	int		j;
	char	**new;

	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	count_something(args, &i, &j);
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
