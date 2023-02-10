/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:46:36 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 13:54:07 by fsandel          ###   ########.fr       */
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

int	b_pwd(t_pars *pars)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	ft_putendl_fd(wd, STDOUT);
	free(wd);
	exit(0);
	return (-1);
}

char	**b_export(t_pars *pars)
{
	int	i;

	i = 1;
	while(pars->cmd[i])
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

int	b_exit(t_pars **pars)
{
	free_struct(pars);
	exit(0);
	return (-1);
}

void	builtin(t_pars *pars)
{
	if (!pars || !pars->cmd[0])
		return ;
	if (!ft_strncmp(pars->cmd[0], "echo", 5))
		b_echo(pars);
	if (!ft_strncmp(pars->cmd[0], "cd", 3))
		b_cd(pars);
	if (!ft_strncmp(pars->cmd[0], "pwd", 4))
		b_pwd(pars);
	if (!ft_strncmp(pars->cmd[0], "export", 7))
		b_export(pars);
	if (!ft_strncmp(pars->cmd[0], "unset", 6))
		b_unset(pars);
	if (!ft_strncmp(pars->cmd[0], "env", 4))
		b_env(pars);
	if (!ft_strncmp(pars->cmd[0], "exit", 5))
		exit(0);
}
