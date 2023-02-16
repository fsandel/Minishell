/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_no_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:44:44 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/16 16:21:08 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_pwd(char	*new, char **env)
{
	char	*old;
	char	*old_string;
	char	*new_string;

	old = array_get_line(env, "PWD");
	if (old)
	{

		old_string = ft_strjoin("OLDPWD=", old);
		free(old);
		env = arr_del_line(env, "OLDPWD");
		env = array_add_line(env, old_string);
		free(old_string);
	}
	new_string = ft_strjoin("PWD=", new);
	env = arr_del_line(env, "PWD");
	env = array_add_line(env, new_string);
	free(new_string);
	return (env);
}
char	**b_cd(t_pars *pars, char **env)
{
	char	*wd;
	char	*new_dir;
	char	*temp;
	
	if (!pars->cmd[1])
	{
		new_dir = array_get_line(env, "HOME");
		if (!new_dir)
			return(ft_putstr_fd("minishell: cd: HOME not set\n", 2), env);
	}
	else if (pars->cmd[1][0] == '/')
	{
		new_dir = ft_strdup(pars->cmd[1]);
		ft_putendl_fd(new_dir, 1);
	}
	else
	{
		wd = getcwd(NULL, 0);
		temp = ft_strjoin(wd, "/");
		new_dir = ft_strjoin(temp, pars->cmd[1]);
		free(temp);
		free(wd);
	}
	env = update_pwd(new_dir, env);
	if (chdir(new_dir))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(pars->cmd[1]);
	}
	free(new_dir);
	return (env);
}

char	**b_export(t_pars *pars)
{
	int	i;
	int	error;

	error = 0;
	i = 1;
	if (pars->amount == 1)
		return (ft_putendl_fd("When no arguments are given, the results are unspecified.\nhttps://www.man7.org/linux/man-pages/man1/export.1p.html", 1), pars->env);
	while (pars->cmd[i])
	{
		if (ft_isalpha(pars->cmd[i][0]))
		{
			pars->env = arr_del_line(pars->env, pars->cmd[i]);
			pars->env = array_add_line(pars->env, pars->cmd[i]);
		}
		else
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(pars->cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			error = 1;
		}
		i++;
	}
	g_error = error;
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

int	string_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
void	free_all(char **arr, t_pars **pars)
{
	free_array(arr);
	free_struct(pars);
}

char	**b_exit(t_pars **pars, char **env)
{
	if (pars[0]->cmd[1] && !string_is_digit(pars[0]->cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(pars[0]->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_all(env, pars);
		exit(255);
	}
	if (pars[0]->amount > 2)
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), g_error = 1, env);
	if (pars[0]->cmd[1])
		g_error = ft_atoi(pars[0]->cmd[1]);
	free_all(env, pars);
	exit(g_error);
}
