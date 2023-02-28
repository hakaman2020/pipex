/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 14:48:06 by hman          #+#    #+#                 */
/*   Updated: 2022/02/11 13:01:59 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "data.h"

void	exit_on_error(char *message, int error_code);
void	exit_command_error(char *message, int error_code);
void	closing_fd(int fd);
void	closing_parent_fds(t_command *command, int command_counter);

#endif