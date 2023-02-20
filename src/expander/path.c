/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:28:40 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/20 22:38:49 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errorput(t_pars **pars, int set, int num, char *prepath, char *postpath)
{
	free(pars[set]->cmd[num]);
	pars[set]->cmd[num] = ft_strjoin(prepath, ft_itoa(g_error));
	pars[set]->cmd[num] = ft_strjoin(pars[set]->cmd[num], postpath);
	return (1);
}

int	path(t_pars **pars, int set, int num)
{
	int		i;
	int		j;
	char	*str;
	char	*path;
	char	*prepath;
	char	*postpath;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	prepath = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	postpath = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	while (pars[set]->cmd[num][i] != '$')
		prepath[j++] = pars[set]->cmd[num][i++];
	i++;
	j = 0;
	if (pars[set]->cmd[num][i] != '?')
	{
		while (check(pars[set]->cmd[num][i], "$\n") == FALSE
			&& is_whitespace(pars[set]->cmd[num][i]) == FALSE
			&& pars[set]->cmd[num][i] != '\0'
			&& check(pars[set]->cmd[num][i], "\"\'") == FALSE)
			str[j++] = pars[set]->cmd[num][i++];
	}
	else
		i++;
	str[j] = '\0';
	j = 0;
	while (pars[set]->cmd[num][i] != '\0')
		postpath[j++] = pars[set]->cmd[num][i++];
	postpath[j] = '\0';
	i = 0;
	while (pars[set]->env[i] && ft_strncmp(str, ft_substr(pars[set]->env[i], 0, ft_strlen(str)), ft_strlen(pars[set]->env[i])) != 0)
		i++;
	if (ft_strnstr(pars[set]->cmd[num], "$?", ft_strlen(pars[set]->cmd[num])))
		return (errorput(pars, set, num, prepath, postpath));
	free(pars[set]->cmd[num]);
	if (pars[set]->env[i] != NULL)
	{
		pars[set]->cmd[num] = ft_strjoin(prepath, ft_substr(pars[set]->env[i], ft_strlen(str) + 1, ft_strlen(pars[set]->env[i]) - ft_strlen(str)));
		pars[set]->cmd[num] = ft_strjoin(pars[set]->cmd[num], postpath);
	}
	else
		pars[set]->cmd[num] = ft_strdup("");
	return (0);
}
