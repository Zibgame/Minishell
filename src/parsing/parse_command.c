/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:59:45 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/09 14:00:41 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse_command(char *line)
{
	char	**splitted_command;
	
	splitted_command = ft_split(line, ' ');
	if (!splitted_command)
		return (NULL);
	
	//type attribution
}