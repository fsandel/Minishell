/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:30:26 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/18 13:30:49 by fsandel          ###   ########.fr       */
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
	char	*wd;
	char	*new_dir;
	char	*temp;

	if (!pars->cmd[1])
	{
		new_dir = array_get_line(env, "HOME");
		if (!new_dir)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), env);
	}
	else if (pars->cmd[1][0] == '/')
	{
		new_dir = ft_strdup(pars->cmd[1]);
		ft_putendl_fd(new_dir, 1);
	}
	else
		cd_get_realtive_dir(pars->cmd[1]);
	env = update_pwd(new_dir, env);
	if (chdir(new_dir))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(pars->cmd[1]);
	}
	free(new_dir);
	return (env);
}
