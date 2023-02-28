/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_locator_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 17:57:46 by hman          #+#    #+#                 */
/*   Updated: 2022/02/11 13:44:40 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "../lib/libft/libft.h"
#include "errors.h"
#include "path_locator_utils.h"

/*
**	attempts to find the environment variable PATH
**	RETURN	the index of the path variable in envp
**			-1 if the path variable is not found
*/

int	find_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*
**	attempt to find the program in the directories stored in the PATH variable
**	RETURN	the path to the program starting from root
**			NULL if program is not located in the directories searched
*/

char	*find_program_in_path(char **paths, char *program_name)
{
	int		i;
	int		file_exist;
	char	*absolute_path;
	char	*intermediate_path;

	i = 0;
	file_exist = -1;
	absolute_path = NULL;
	while (paths[i] != NULL && file_exist != 0)
	{
		intermediate_path = ft_strjoin(paths[i], "/");
		absolute_path = ft_strjoin(intermediate_path, program_name);
		free(intermediate_path);
		file_exist = access(absolute_path, F_OK);
		if (file_exist == -1)
		{
			free(absolute_path);
			absolute_path = NULL;
		}		
		i++;
	}
	return (absolute_path);
}
