/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 14:08:11 by hman          #+#    #+#                 */
/*   Updated: 2022/02/11 13:50:39 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//this function will parse the commands and create a 3 dimensional array 
//to be used by the pipex program for execve()

#include <stdlib.h>
#include <unistd.h>

#include "../lib/libft/libft.h"
#include "errors.h"
#include "commands.h"
#include "path_locator_utils.h"

/*
**	attempt to find the command in the directories indicated by PATH and update
**	the command struct where necessary
*/

void	find_in_path_dirs(char **paths, t_command *command)
{
	char	*full_path_command;
	char	*temp;

	full_path_command = find_program_in_path(paths, command->command[0]);
	if (full_path_command != NULL)
	{
		temp = command->command[0];
		command->command[0] = full_path_command;
		free(temp);
		command->exist = 1;
	}
}

/*
** update each command to it's full path if found and set exist variable to 1
** RETURN	an array of t_command structs with the command full path updated 
** 			where possible
*/

t_command	*update_commands_paths(int amount_commands,
	t_command *commands, char **envp)
{
	int		found;
	char	**paths;
	int		i;

	found = find_env_path(envp);
	if (found != -1)
	{
		paths = ft_split(&envp[found][5], ':');
		if (paths == NULL)
			exit_on_error("Error: ", 1);
	}
	i = 0;
	while (i < amount_commands)
	{
		if (commands[i].command[0] == NULL)
			;
		else if (access(commands[i].command[0], F_OK) == 0)
			commands[i].exist = 1;
		else if (found != -1)
			find_in_path_dirs(paths, &commands[i]);
		i++;
	}
	if (found != -1)
		free_2d_char_array(paths);
	return (commands);
}

/*
**	it will attempt to create an array of t_command structs with argv
**	RETURN	array of t_command structs with the each command and it's arguments
*/

t_command	*create_commands_array(int amount_commands, char *argv[],
	char **envp)
{
	t_command	*commands;
	int			i;

	commands = malloc((amount_commands) * sizeof(t_command));
	if (commands == NULL)
		exit_on_error("Error: ", 1);
	i = 0;
	while (i < amount_commands)
	{
		commands[i].command = ft_split(argv[i + 2], ' ');
		commands[i].exist = 0;
		i++;
	}
	commands = update_commands_paths(amount_commands, commands, envp);
	return (commands);
}

/*
**	function to free a 2d char array
*/

void	free_2d_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
**	function to free the array of t_command structs
*/

void	free_commands_array(int amount_commands, t_command *commands)
{
	int	i;

	i = 0;
	while (i < amount_commands)
	{
		free_2d_char_array(commands[i].command);
		i++;
	}
	free(commands);
}
