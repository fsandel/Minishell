/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_in_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:42:15 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 20:38:52 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_echo(t_pars *pars)
{
	int	line;
	int	i;

	i = 1;
	line = 1;
	if (pars->cmd[1] && !ft_strncmp(pars->cmd[1], "-n", 3))
	{
		line = 0;
		i++;
	}
	while (pars->cmd[i])
	{
		ft_putstr_fd(pars->cmd[i++], STDOUT); //remove quotes
		if (pars->cmd[i])
			ft_putchar_fd(' ', STDOUT);
	}
	if (line)
		ft_putchar_fd('\n', STDOUT);
	exit(0);
	return (-1);
}

int	b_pwd(t_pars *pars)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	ft_putendl_fd(wd, STDOUT);
	free(wd);
	exit(0);
	return (-1);
}

int	b_env(t_pars *pars)
{
	int	i;

	i = 0;
	while (pars->env[i])
	{
		ft_putendl_fd(pars->env[i++], STDOUT);
	}
	exit(0);
	return (-1);
}
