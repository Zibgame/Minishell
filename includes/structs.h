/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:37:21 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/05 11:06:18 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "library/libft/libft.h"

enum e_types
{
	TOREMOVE = -2,
	PARSEERROR = -1,
	BUILTINS,
	OPTION,
	REDIRECTION,
	PIPE,
	ARGUMENT,
	EXPANSION,
	OPERATOR,
	FILETOOPEN
};

typedef enum e_redir_type
{
	R_IN,      // <
	R_OUT,     // >
	R_APPEND,  // >>
	R_HEREDOC  // <<
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target; // fichier ou delimiter
	int				fd;      // utilisé pour heredoc
	struct s_redir	*next;
}	t_redir;


typedef struct s_cmd
{
	int				fd;
	int				type;
	int				file_type;
	char			*name;
	t_redir			*redirs;
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
	t_cmd		*cmd;
	char		**envp_tmp;
	t_var_list	*envp;
	int			last_return;
}	t_shell;

#endif
