/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:46:36 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/22 11:22:04 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_input(t_pars **pars, int i)
{
	if (!pars)
		return (1);
	if (!pars[i])
		return (1);
	if (!pars[i]->cmd)
		return (1);
	if (!pars[i]->cmd[i])
		return (1);
	return (0);
}

void	free_exit(t_pars **pars, char **env)
{
	free_array(env);
	free_struct(pars);
	exit(g_error);
}

void	builtin(t_pars **pars, int i)
{
	if (check_empty_input(pars, i))
		return ;
	if (!ft_strncmp(pars[i]->cmd[0], "echo", 5))
		b_echo(pars[i]);
	if (!ft_strncmp(pars[i]->cmd[0], "cd", 3))
		pars[0]->env = b_cd(pars[i], pars[i]->env);
	if (!ft_strncmp(pars[i]->cmd[0], "pwd", 4))
		b_pwd(pars[i]);
	if (!ft_strncmp(pars[i]->cmd[0], "export", 7))
		pars[0]->env = b_export(pars[i]);
	if (!ft_strncmp(pars[i]->cmd[0], "unset", 6))
		pars[0]->env = b_unset(pars[i]);
	if (!ft_strncmp(pars[i]->cmd[0], "env", 4))
		b_env(pars[i]);
	if (!ft_strncmp(pars[i]->cmd[0], "exit", 5))
		b_exit(pars, pars[i]->env, i);
	if (!ft_strncmp(pars[i]->cmd[0], "echo", 5)
		|| !ft_strncmp(pars[i]->cmd[0], "cd", 3)
		|| !ft_strncmp(pars[i]->cmd[0], "pwd", 4)
		|| !ft_strncmp(pars[i]->cmd[0], "export", 7)
		|| !ft_strncmp(pars[i]->cmd[0], "unset", 6)
		|| !ft_strncmp(pars[i]->cmd[0], "env", 4))
		free_exit(pars, pars[0]->env);
}
