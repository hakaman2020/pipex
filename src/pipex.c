/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 14:08:08 by hman          #+#    #+#                 */
/*   Updated: 2022/02/11 13:49:32 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>	// wait(), waitpid()
#include <sys/wait.h>	// wait(), waitpid()
#include <sys/stat.h>
#include <fcntl.h>

#include "../lib/libft/libft.h"
#include "commands.h"
#include "pipex.h"
#include "errors.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*commands;
	int			amount_commands;
	int			last_pid;
	int			last_exit_code;

	if (argc < 5)
	{
		write(1,
			"Usage: ./pipex inputfile \"command\" \"command\" outputfile\n", 57);
		return (1);
	}
	last_exit_code = 0;
	amount_commands = argc - 3;
	commands = create_commands_array(amount_commands, argv, envp);
	last_pid = start_pipe_process(argv, amount_commands, commands, envp);
	last_exit_code = wait_for_child_processes(last_pid, amount_commands);
	free_commands_array(amount_commands, commands);
	return (last_exit_code);
}

/*
**	the pipe process is setup and child processes are created
**	RETURN	process id of the last child process is returned
*/

int	start_pipe_process(char **argv, int amount_commands,
			t_command *commands, char **envp)
{
	int	command_counter;
	int	pid;

	command_counter = 1;
	while (command_counter <= amount_commands)
	{
		setup_pipe(commands, amount_commands, command_counter,
			argv[amount_commands + 2]);
		pid = fork();
		if (pid < 0)
			exit_on_error("Fork failed :", 1);
		else if (pid == 0)
		{
			if (command_counter == 1)
				exec_command(&commands[command_counter - 1], envp, 0, argv[1]);
			else if (command_counter < amount_commands)
				exec_command(&commands[command_counter - 1], envp, 1, NULL);
			else if (command_counter == amount_commands)
				exec_command(&commands[command_counter - 1], envp, 2, NULL);
		}
		else
			closing_parent_fds(&commands[command_counter -1], command_counter);
		command_counter++;
	}
	return (pid);
}

/*
**	the pipe is being setup and the relevant file descriptors are assigned to
**	the relevant command struct variables
*/
void	setup_pipe(t_command *commands, int amount_commands,
			int command_counter, char *outputfile)
{
	if (command_counter > 1)
		commands[command_counter - 1].input_fd
			= commands[command_counter - 2].output_fd[0];
	if (command_counter < amount_commands)
	{
		if (pipe(commands[command_counter - 1].output_fd) == -1)
			exit_on_error("Error :", 1);
	}
	else if (command_counter == amount_commands)
	{
		commands[command_counter - 1].output_fd[1] = open(outputfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (commands[command_counter - 1].output_fd[1] == -1)
			exit_on_error(outputfile, 1);
	}
}

/*
**	this function will execute the commmand after setting up the redirection of
**	STDIN and STDOUT. 
**	command_type :	0 for the first command
**					1 for a middle command
*					2 for the last commmand
*/

void	exec_command(t_command *command, char **envp, int command_type,
			char *filename)
{
	if (command_type == 0)
	{
		command->input_fd = open(filename, O_RDONLY);
		if (command->input_fd == -1)
			exit_on_error(filename, 1);
	}
	dup2(command->input_fd, 0);
	closing_fd(command->input_fd);
	dup2(command->output_fd[1], 1);
	closing_fd(command->output_fd[1]);
	if (command_type != 2)
		closing_fd(command->output_fd[0]);
	if (command->exist == 0)
		exit_command_error(command->command[0], 127);
	if (execve(command->command[0], command->command, envp) == -1)
		exit_on_error(command->command[0], 1);
}

/*
**	this will force the parent to wait for each of the created child processes 
**	to end and will return the exit code of the last child process
**	RETURN:	exit code of last child process
*/

int	wait_for_child_processes(int last_pid, int amount_commands)
{
	int	wstatus;
	int	command_counter;
	int	last_exit_code;

	waitpid(last_pid, &wstatus, 0);
	last_exit_code = WEXITSTATUS(wstatus);
	command_counter = 2;
	while (command_counter <= amount_commands)
	{
		wait(&wstatus);
		command_counter++;
	}
	return (last_exit_code);
}
