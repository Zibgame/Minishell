/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:37:21 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/09 17:44:50 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "library/libft/libft.h"

enum e_types
{
	PARSEERROR = -1,
	BUILTINS,
	OPTION,
	REDIRECTION,
	PIPE,
	EXPANSION,
	ARGUMENT,
	OPERATOR,
	FILETOOPEN
};

enum e_file_type
{
	FFILE,
	EOFILE,
	HEREDOC	
};

typedef struct s_cmd
{
	int				fd;
	int				type;
	int				file_type;
	char			*name;
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
