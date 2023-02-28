/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/09 17:52:09 by hman          #+#    #+#                 */
/*   Updated: 2022/02/04 16:41:44 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "data.h"

void		find_in_path_dirs(char **paths, t_command *command);
t_command	*update_commands_paths(int amount_commands,
				t_command *commands, char **envp);
t_command	*create_commands_array(int amount_commands, char *argv[],
				char **envp);
void		free_2d_char_array(char **array);
void		free_commands_array(int amount_commands, t_command *commands);

#endif
