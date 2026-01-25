/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:30:08 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/25 18:05:56 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

static char	*remove_all_quotes(char *s)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

static int	parse_ll(char *s, long long *out)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i++] == '-')
			sign = -1;
	}
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		if (res > (LLONG_MAX - (s[i] - '0')) / 10)
			return (0);
		res = res * 10 + (s[i] - '0');
		i++;
	}
	*out = res * sign;
	return (1);
}

static int	exit_with_arg(t_shell *shell, t_cmd *arg, char *line)
{
	char		*clean;
	long long	code;

	clean = remove_all_quotes(arg->name);
	if (!clean || !parse_ll(clean, &code))
	{
		ft_printf_fd(
			"minishell: exit: %s: numeric argument required\n",
			2, arg->name);
		free(clean);
		free(line);
		free_shell(shell);
		exit(2);
	}
	free(clean);
	if (arg->next)
	{
		ft_printf_fd("minishell: exit: too many arguments\n", 2);
		shell->last_return = 1;
		return (2);
	}
	free(line);
	free_shell(shell);
	exit((unsigned char)code);
}

void	close_fd(void)
{
	int		fd;
	char	buff[1];

	fd = 3;
	while (fd < 1024)
	{
		if (read(fd, buff, 0) != -1)
			close(fd);
		fd++;
	}
}

int	finish(t_shell *shell, char *line)
{
	t_cmd	*arg;
	int		rn;

	printf("exit\n");
	arg = shell->cmd->next;
	close_fd();
	if (!arg)
	{
		rn = shell->last_return;
		free_shell(shell);
		if (line)
			free(line);
		exit((unsigned char)rn);
	}
	return (exit_with_arg(shell, arg, line));
}
