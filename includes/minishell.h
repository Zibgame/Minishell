/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:22 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 12:46:02 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "librairies.h"

void		init_signal(void);
void		sig_handler(int sig);
void		shell_loop(t_shell *shell);
void		start_shell(t_shell *shell);
void		exec_cmd(t_shell *shell, char *line);

char		*read_line(void);

/* == LKL == */
void		ft_lkladd_back(t_var_list **lst, t_var_list *new);
void		ft_lkladd_front(t_var_list **lst, t_var_list *new);
void		ft_lklclear(t_var_list **lst);
void		ft_lkldelone(t_var_list *lst);
int			ft_lklsize(t_var_list *lst);
t_var_list	*ft_lkllast(t_var_list *lst);
t_var_list	*ft_lklnew(char *name, char *value);

void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void		ft_cmdadd_front(t_cmd **lst, t_cmd *new);
void		ft_cmdclear(t_cmd **lst);
void		ft_cmddelone(t_cmd *lst);
int			ft_cmdsize(t_cmd *lst);
t_cmd		*ft_cmdlast(t_cmd *lst);
t_cmd		*ft_cmdnew(char *name, char **args);

void		display_vars(t_var_list *vars);
char		*get_value(t_shell *shell, char *name);

t_shell		*create_shell_struct(char **envp);

char	*get_cmd_path(t_shell *shell, char *cmd);
int	is_builtins(char *name);
int	exec_builtins(t_cmd cmd, t_shell *shell);
int	env(t_cmd *cmd, t_shell *shell);
int	pwd(t_cmd *cmd, t_shell *shell);
t_cmd	create_command(char *line);
int	finish(t_cmd *cmd, t_shell *shell);

#endif
