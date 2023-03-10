/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:41 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 14:13:35 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_pwd(char	*new, char **env)
{
	char	*old;
	char	*old_string;
	char	*new_string;
	char	*new2;

	(void)new;
	old = array_get_line(env, "PWD");
	if (old)
	{
		old_string = ft_strjoin("OLDPWD=", old);
		free(old);
		env = arr_del_line(env, "OLDPWD");
		env = array_add_line(env, old_string);
		free(old_string);
	}
	new2 = getcwd(NULL, 0);
	new_string = ft_strjoin("PWD=", new2);
	free(new2);
	env = arr_del_line(env, "PWD");
	env = array_add_line(env, new_string);
	free(new_string);
	return (env);
}

char	*cd_get_realtive_dir(char *cmd)
{
	char	*ret;
	char	*wd;
	char	*temp;

	wd = getcwd(NULL, 0);
	temp = ft_strjoin(wd, "/");
	ret = ft_strjoin(temp, cmd);
	free(wd);
	free(temp);
	return (ret);
}

char	**b_cd(t_pars *pars, char **env)
{
	char	*new_dir;

	if (!pars->cmd[1])
	{
		new_dir = array_get_line(env, "HOME");
		if (!new_dir)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", STDERR), env);
	}
	else if (pars->cmd[1][0] == '/')
		new_dir = ft_strdup(pars->cmd[1]);
	else
		new_dir = cd_get_realtive_dir(pars->cmd[1]);
	g_error = chdir(new_dir) * -1;
	env = update_pwd(new_dir, env);
	if (g_error)
	{
		ft_putstr_fd("minishell: cd: ", STDERR);
		perror(pars->cmd[1]);
	}
	return (free(new_dir), env);
}
