/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:37:21 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/05 10:35:04 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdbool.h>
# include "library/libft/libft.h"

typedef struct s_command
{
	char	**line;
	bool	is_builtin;

}	t_command;

typedef struct s_shell
{
	t_list	*env;
}	t_shell;
