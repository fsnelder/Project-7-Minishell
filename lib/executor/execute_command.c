/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/12 11:39:15 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 11:40:45 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "executor.h"
#include "executor_utils.h"
#include <unistd.h>

char	*construct_full_path(const char *directory, const char *name)
{
	char	*temp;
	char	*full_path;

	temp = malloc_check(ft_strjoin(directory, "/"));
	full_path = malloc_check(ft_strjoin(temp, name));
	free(temp);
	return (full_path);
}

char	*search_path(const char *path, const char *name)
{
	char	**paths;
	int		i;
	char	*full_path;

	paths = malloc_check(ft_split(path, ':'));
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = construct_full_path(paths[i], name);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

int	find_command(char **out_path, char *name)
{
	const char	*path;

	*out_path = name;
	if (ft_strchr(name, '/'))
		return (SUCCESS);
	path = getenv("PATH");
	if (!path)
		return (COMMAND_NOT_FOUND);
	*out_path = search_path(path, name);
	if (!*out_path)
		return (COMMAND_NOT_FOUND);
	return (SUCCESS);
}

void	init_command_info(t_command_info *cinfo)
{
	cinfo->input_fd = -1;
	cinfo->pid_index = 0;
	cinfo->command = NULL;
	ft_memset(cinfo->piped, -1, 2 * sizeof(int));
}
