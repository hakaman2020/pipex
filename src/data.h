/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/28 17:50:48 by hman          #+#    #+#                 */
/*   Updated: 2022/02/10 21:26:45 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_command
{
	char	**command;
	int		exist;
	int		input_fd;
	int		output_fd[2];
}				t_command;

#endif