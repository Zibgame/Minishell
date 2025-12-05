/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:33:20 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 10:30:43 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd(char *cmd, char **env)
{
	char	**paths;
	char	*tmp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}
