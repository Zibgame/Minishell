/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:37:21 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/05 11:26:17 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdbool.h>
# include "library/libft/libft.h"

typedef struct s_command
{
	char	**line;
	bool	is_builtin;

}	t_command;

typedef struct s_var_list
{
	char			*name;
	char			*value;
	t_var_list		*previous;
	t_var_list		*next;
}	t_var_list;

typedef struct s_shell
{
	t_var_list	*envp;	
}	t_shell;
