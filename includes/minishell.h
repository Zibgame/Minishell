/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:22 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/17 19:24:05 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "librairies.h"
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# define PS1 "\001\033[1;34m\002MiniShell❯ \001\033[0m\002"

/* == SIGNALS == */
void		init_signal(void);
void		sig_handler(int sig);

/* == SHELL == */
void		shell_loop(t_shell *shell);
void		start_shell(t_shell *shell);
void		exec_cmd(t_shell *shell, char *line);
char		*read_line(void);
t_shell		*create_shell_struct(char **envp);
void		remove_empty_commands(t_cmd **cmd);
void		free_shell(t_shell *shell);

/* == VARS LINKED LIST == */
void		ft_lkladd_back(t_var_list **lst, t_var_list *new);
void		ft_lkladd_front(t_var_list **lst, t_var_list *new);
void		ft_lklclear(t_var_list **lst);
void		ft_lkldelone(t_var_list *lst);
int			ft_lklsize(t_var_list *lst);
t_var_list	*ft_lkllast(t_var_list *lst);
t_var_list	*ft_lklnew(char *name, char *value);
void		display_vars(t_var_list *vars);
char		*get_value(t_shell *shell, char *name);

/* == COMMAND COMMAND LIST == */
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void		ft_cmdadd_front(t_cmd **lst, t_cmd *new);
void		ft_cmdclear(t_cmd **lst);
void		ft_cmddelone(t_cmd *lst);
void		ft_lkl_modify(t_var_list **lst, char *value);
int			ft_cmdsize(t_cmd *lst);

t_cmd		*ft_cmdlast(t_cmd *lst);
t_cmd		*ft_cmdnew(char *name, int type);
t_cmd		extract_next_cmd(t_cmd *cmd);
int			command_type(t_cmd	*cmd);
void		clean_command_free(t_shell *shell);
char		**build_argv(t_cmd *cmd);

/* == EXECUTION == */
char		*get_cmd_path(t_shell *shell, char *cmd);
int			builtin_uses_stdin(int type);
int			finish(t_shell *shell, char *line);

/* == BUILTINS == */
int			is_builtins(char *name);
int			exec_builtins(t_shell *shell, char *line);
int			env(t_shell *shell);

char		*get_cmd_path(t_shell *shell, char *cmd);
int			is_builtins(char *name);
int			pwd(t_shell *shell);
int			unset(t_shell *shell);

int			apply_redirections(t_cmd *cmd);
void		free_shell(t_shell *shell);
int			apply_redirections(t_cmd *cmd);
char		*join_and_free(char *s1, char *s2);
void		recreate_envp(t_shell *shell);
int			print_header(char *path);
int			echo(t_shell *shell);
int			cd(t_shell *shell);
int			print_status(t_shell *shell);
int			exec_builtin_pipeline(t_shell *shell, t_cmd *cmd);
int			export(t_shell *shell);
int			echo_pipe(t_cmd *cmd);
int			pwd_pipe(void);
int			env_pipe(char **envp);
int			exec_builtin_pipe(t_shell *shell, t_cmd *cmd);
char		**clean_empty_args(char **args);
/* == OTHERS == */
void		clear(void);
void		set_value(t_shell **shell, char *to_change, char *value);

/* == Parsing == */
t_cmd		*parse_command(char *line);
int			has_parse_error(t_cmd *cmd);
void		extract_redirections(t_shell *shell, t_cmd *cmd);
int			comb_redir_oper_pipes(char *token);
int			redirect_split(t_cmd *cmd, char **to_fill);
void		set_value(t_shell **shell, char *to_change, char *value);
void		add_commands(t_cmd	**cmd, char **elems);
int			is_redirect(t_cmd *cmd);
char		**ft_split_charset(char const *s, char *c);
int			is_pipe(t_cmd *cmd);
t_cmd		*get_next_cmd(t_cmd *cmd);
int			is_operator_char(char c);
int			is_double_operator(char *s);
char		*strip_quotes(char *s);

/* == DEBUG == */
void		display_list(t_cmd	*cmd);

/* == Pipex ==*/
void		exec_pipeline(t_shell *shell, char *line);
int			has_pipe(t_cmd *cmd);

/* == Redirs == */
t_redir		*redir_new(t_redir_type type, char *target);
void		redir_add_back(t_redir **lst, t_redir *new);

/* == Parsing ==*/
char		**tokenize_line(char *line);
int			skip_spaces(char *s, int i);
int			read_quoted(char *s, int i, char quote);
int			read_unquoted(char *s, int i);
char		is_quoted(char *s);
int			handle_direct_path(t_shell *shell, char *cmd);

/* HEREDOC */
void		prepare_heredocs(t_shell *shell, t_cmd *cmd);
int			handle_heredoc(t_shell *shell, char *limiter);
void 		ft_redirclear(t_redir **red);
/* == expansion == */
void		expand_vars(t_shell *shell);
char		get_token_quote(char *s);
int			open_all_redirections(t_cmd *cmd);
void		dup_redirections(t_cmd *cmd);

void	signal_prompt(void);
void	signal_exec(void);
void	signal_child(void);
void	signal_heredoc(void);
void	set_signal_shell(t_shell *shell);

#endif
