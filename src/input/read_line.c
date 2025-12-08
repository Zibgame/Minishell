/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:27:10 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 16:51:07 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_line(void)
{
	char	*line;

	while (1)
	{
		line = readline(PS1);
		if (!line)
			return (NULL);
		if (*line)
		{
			add_history(line);
			return (line);
		}
		free(line);
	}
}
