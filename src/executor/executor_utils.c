/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:46:35 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 19:55:50 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_error(char *cmd, char *og_cmd)
{
	int			error;
	struct stat	st;
	int			status;

	status = stat(og_cmd, &st);
	error = 0;
	if (!cmd)
	{
		error = 127;
		ft_err_print("minishell: %s: command not found\n", og_cmd, NULL, NULL);
	}
	else if (!status && S_ISDIR(st.st_mode))
	{
		error = 127;
		ft_err_print("minishell: %s: is a directory\n", og_cmd, NULL, NULL);
	}
	else
	{
		ft_err_print("minishell: %s ", og_cmd, NULL, NULL);
		perror("");
		error = 126;
	}
	return (error);
}

void	executor_exit(char *str, char **arr, t_pars **pars)
{
	free(str);
	free_array(arr);
	free_struct(pars);
	exit(g_error);
}
