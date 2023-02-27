/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:48:13 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/27 16:30:03 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*check_path_access(t_pars *pars, char *path)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(1, ft_strlen(pars->cmd[0]) + ft_strlen(path) + 2);
	while (path[i] != '\0')
	{
		tmp[i] = path[i];
		i++;
	}
	tmp[i++] = '/';
	while (pars->cmd[0][j] != '\0')
		tmp[i++] = pars->cmd[0][j++];
	if (access(tmp, F_OK) == 0)
		return (tmp);
	else
		return (free(tmp), NULL);
}

char	*check_path(t_pars *pars, char **path)
{
	int		c;
	char	*tmp;

	c = 0;
	if (pars && pars->cmd && access(pars->cmd[0], F_OK) == 0
		&& (pars->cmd[0][0] == '.' || pars->cmd[0][0] == '/'))
		return (ft_strdup(pars->cmd[0]));
	while (path && path[c] && pars && pars->cmd && pars->cmd[0]
		&& pars->cmd[0][0] != '.' && pars->cmd[0][0] != '/')
	{
		tmp = check_path_access(pars, path[c++]);
		if (tmp)
			return (tmp);
	}
	tmp = ft_strjoin("./", pars->cmd[0]);
	if (!path && access(tmp, F_OK) == 0)
		return (tmp);
	return (free(tmp), NULL);
}
