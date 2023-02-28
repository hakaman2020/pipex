/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 14:48:02 by hman          #+#    #+#                 */
/*   Updated: 2022/02/11 13:45:18 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //exit
#include <stdio.h>
#include <unistd.h>

#include "../lib/libft/libft.h"
#include "errors.h"

/*
**	exit when an error has been encountered
*/

void	exit_on_error(char *message, int error_code)
{
	perror(message);
	exit(error_code);
}

/*
**	exit when a command has not been found
*/

void	exit_command_error(char *message, int error_code)
{
	ft_putstr_fd(message, 2);
	write(2, ": command not found\n", 20);
	exit(error_code);
}

/*
**	attempt to close the given file descriptor
*/

void	closing_fd(int fd)
{
	if (fd != -1 && close(fd) == -1)
		exit_on_error("Error :", 1);
}

/*
**	closes the file descriptor that are no longer needed after a fork()
*/

void	closing_parent_fds(t_command *command, int command_counter)
{
	if (command_counter != 1)
		closing_fd(command->input_fd);
	closing_fd(command->output_fd[1]);
}
