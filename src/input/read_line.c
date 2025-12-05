/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:27:10 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 09:05:52 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_line(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
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
