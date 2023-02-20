/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_in_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:42:15 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/20 14:51:15 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo(t_pars *pars)
{
	int	line;
	int	i;

	i = 1;
	line = 1;
	while (pars->cmd[i] && !ft_strncmp(pars->cmd[i], "-n", 3))
	{
		line = 0;
		i++;
	}
	while (pars->cmd[i])
	{
		ft_putstr_fd(pars->cmd[i++], STDOUT);
		if (pars->cmd[i])
			ft_putchar_fd(' ', STDOUT);
	}
	if (line)
		ft_putchar_fd('\n', STDOUT);
	g_error = 0;
}

void	b_pwd(t_pars *pars)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pars->cmd[0]);
		exit(1);
	}
	else
	{
		ft_putendl_fd(wd, STDOUT);
		free(wd);
	}
	g_error = 0;
}

void	b_env(t_pars *pars)
{
	int	i;

	i = 0;
	if (pars->amount > 1)
	{
		ft_putendl_fd("minishell: env: no arguments for env", 2);
		exit(1);
	}
	while (pars->env[i])
	{
		if (ft_strchr(pars->env[i], '='))
			ft_putendl_fd(pars->env[i], STDOUT);
		i++;
	}
	g_error = 0;
}
