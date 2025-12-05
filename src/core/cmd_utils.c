/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:33:20 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 15:35:44 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*get_cmd_path(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*value;
	char	*full;
	int		i;

	value = get_value(shell, "PATH");
	if (!value)
		return (NULL);
	paths = ft_split(value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (free_array(paths), full);
		free(full);
		i++;
	}
	free_array(paths);
	return (NULL);
}
