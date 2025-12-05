/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:37:21 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/05 13:22:50 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "library/libft/libft.h"

typedef struct s_command
{
	char	**line;
	bool	is_builtin;

}	t_command;

typedef struct s_var_list
{
	char				*name;
	char				*value;
	struct s_var_list	*previous;
	struct s_var_list	*next;
}	t_var_list;

typedef struct s_shell
{
	t_var_list	*envp;	
}	t_shell;

#endif