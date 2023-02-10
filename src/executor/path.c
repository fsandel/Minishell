/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:48:13 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 15:51:14 by fsandel          ###   ########.fr       */
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

char	*check_path(t_pars *pars, char **path)
{
	int		i;
	int		j;
	int		c;
	char	*tmp;

	c = 0;
	while (path && path[c])
	{
		i = 0;
		j = 0;
		tmp = ft_calloc(1, ft_strlen(pars->cmd[0]) + ft_strlen(path[c]) + 2);
		while (path[c][i] != '\0')
		{
			tmp[i] = path[c][i];
			i++;
		}
		tmp[i++] = '/';
		while (pars->cmd[0][j] != '\0')
			tmp[i++] = pars->cmd[0][j++];
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		c++;
	}
	return (NULL);
}
