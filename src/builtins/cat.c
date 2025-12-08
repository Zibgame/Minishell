/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:51:15 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 15:05:03 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	cat(char *path)
{
	int	fd;

	if (!path)
		return (ft_putstr_fd("cat: missing file\n", 2), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("cat: cannot open file\n", 2), 1);
	print_file(fd);
	close(fd);
	return (0);
}
