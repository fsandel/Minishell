/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_no_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:44:44 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 20:38:55 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_cd(t_pars *pars)
{
	char	*wd;
	char	*new_dir;
	char	*temp;
	char	*env;

	if (!pars->cmd[1])
		chdir(getenv("HOME"));
	else if (pars->cmd[1][0] == '/')
		chdir(pars->cmd[1]);
	else
	{
		wd = getcwd(NULL, 0);
		temp = ft_strjoin(wd, "/");
		new_dir = ft_strjoin(temp, pars->cmd[1]);
		chdir(new_dir);
		free(temp);
		free(new_dir);
		free(wd);
	}
	return (0);
}

char	**b_export(t_pars *pars)
{
	int	i;

	i = 1;
	while (pars->cmd[i])
	{
		if (ft_strchr(pars->cmd[i], '='))
		{
			pars->env = arr_del_line(pars->env, pars->cmd[i]);
			pars->env = array_add_line(pars->env, pars->cmd[i]);
		}
		else
			perror(pars->cmd[i]);
		i++;
	}
	return (pars->env);
}

char	**b_unset(t_pars *pars)
{
	int	i;

	i = 1;
	while (pars->cmd[i])
		pars->env = arr_del_line(pars->env, pars->cmd[i++]);
	return (pars->env);
}

int	b_exit(t_pars **pars)
{
	free_struct(pars);
	exit(0);
	return (-1);
}
