/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_locator_utils.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 17:58:05 by hman          #+#    #+#                 */
/*   Updated: 2022/02/03 15:37:12 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_LOCATOR_UTILS_H
# define PATH_LOCATOR_UTILS_H

# include "data.h"

int		find_env_path(char **envp);
char	*find_program_in_path(char **paths, char *progam_name);
int		is_command_local(char *program_name);

#endif