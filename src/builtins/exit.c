/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:30:08 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/13 13:31:22 by aeherve          ###   ########.fr       */
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

int	finish(t_shell *shell)
{
	t_cmd		*arg;
	char		*clean;
	long long	code;

	printf("exit\n");
	arg = shell->cmd->next;
	if (!arg)
		exit((unsigned char)shell->last_return);
	clean = remove_all_quotes(arg->name);
	if (!clean || !parse_ll(clean, &code))
	{
		ft_printf_fd("minishell: exit: %s: numeric argument required\n",
			2, arg->name);
		free(clean);
		exit(2);
	}
	free(clean);
	if (arg->next)
	{
		ft_printf_fd("minishell: exit: too many arguments\n", 2);
		shell->last_return = 1;
		return (2);
	}
	exit((unsigned char)code);
}
