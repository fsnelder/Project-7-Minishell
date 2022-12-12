/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 14:40:29 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 13:34:45 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "executor.h"
# include "executor_utils.h"
# include "parser.h"
# include "builtins.h"
# include "expand.h"
# include <stdbool.h>
# include "util.h"
# include <stdio.h>

typedef int	(*t_builtin_function)(const char **, const char**);

typedef struct s_command_info
{
	int			piped[2];
	int			input_fd;
	int			pid_index;
	t_command	*command;
}	t_command_info;

int		process_heredocs(t_list *commands);

int		dispatch_builtin(t_command *command, char **args);
bool	is_builtin(const char *name);
int		get_builtin_index(const char *name);
int		builtin_main_process(
			t_executor *executor, t_command *command);

int		execute_piped_command(
			t_executor *executor, t_command_info *info);
int		execute_pipe_sequence(t_executor *executor, t_list *commands);
int		handle_child_process(t_command *command);
int		set_pipe_redirections(int input, int output);
int		execute_piped_child(t_command_info *cinfo);

int		set_redirect(t_redirect *redirect, int file_mode, int dup_to);
int		set_redirection(t_redirect *redirect);
int		set_redirections(t_list *redirections);

char	*construct_full_path(const char *directory, const char *name);
char	*search_path(const char *path, const char *name);
int		find_command(char **out_path, char *name);
void	init_command_info(t_command_info *cinfo);

int		dup_std(int *std);
int		reset_std(int *std);

char	*heredoc_expand(const char *line);
char	*expand_delimiter(t_token *input);
bool	check_should_expand(t_token *input);

#endif
