/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:37:21 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/09 11:15:31 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "library/libft/libft.h"

enum e_types
{
	BUILTINS,
	ARGUMENT,
	OPTION,
	REDIRECTION,
	PIPE,
	EXPANSION
};

enum e_file_type
{
	FILE,
	EOFILE,
	HEREDOC	
};

typedef struct s_cmd
{
	int				type;
	char			*name;
	char			**args;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_var_list
{
	char				*name;
	char				*value;
	struct s_var_list	*previous;
	struct s_var_list	*next;
}	t_var_list;

typedef struct s_shell
{
	t_cmd		*actual_command;
	char		**envp_tmp;
	t_var_list	*envp;
}	t_shell;

#endif
