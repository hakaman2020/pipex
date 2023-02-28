/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 16:06:22 by hman          #+#    #+#                 */
/*   Updated: 2022/02/11 12:32:30 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "data.h"

void	free_commands_array(int amount_commands, t_command *commands);
int		start_pipe_process(char **argv, int amount_commands,
			t_command *commands, char **envp);
void	setup_pipe(t_command *commands, int amount_commands,
			int command_counter, char *outputfile);
void	exec_command(t_command *command, char **envp, int command_type,
			char *filename);
int		wait_for_child_processes(int last_pid, int amount_commands);

#endif