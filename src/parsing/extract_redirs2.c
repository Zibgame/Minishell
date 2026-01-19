/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_redirs2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:22:40 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/19 18:54:25 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_redir_type(char *name)
{
	if (!name)
		return (-1);
	if (!ft_strncmp(name, "<", 2))
		return (R_IN);
	if (!ft_strncmp(name, ">", 2))
		return (R_OUT);
	if (!ft_strncmp(name, ">>", 3))
		return (R_APPEND);
	if (!ft_strncmp(name, "<<", 3))
		return (R_HEREDOC);
	return (-1);
}