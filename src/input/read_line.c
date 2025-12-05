/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:27:10 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 10:31:00 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
