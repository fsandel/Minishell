/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:28:40 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/21 13:25:21 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre(t_pars **pars, int set, int num, t_ph *ph)
{
	while (pars[set]->cmd[num][ph->i] != '$')
		ph->pre[ph->j++] = pars[set]->cmd[num][ph->i++];
	ph->i++;
	ph->j = 0;
}

void	middle(t_pars **pars, int set, int num, t_ph *ph)
{
	while (check(pars[set]->cmd[num][ph->i], "$\n") == FALSE
		&& is_whitespace(pars[set]->cmd[num][ph->i]) == FALSE
		&& pars[set]->cmd[num][ph->i] != '\0'
		&& check(pars[set]->cmd[num][ph->i], "\"\'") == FALSE)
			ph->str[ph->j++] = pars[set]->cmd[num][ph->i++];
	ph->str[ph->j] = '\0';
}

void	post(t_pars **pars, int set, int num, t_ph *ph)
{
	ph->j = 0;
	while (pars[set]->cmd[num][ph->i] != '\0')
		ph->post[ph->j++] = pars[set]->cmd[num][ph->i++];
	ph->post[ph->j] = '\0';
	ph->i = 0;
}

int	retpath(t_pars **pars, int set, int num, t_ph *ph)
{
	if (ft_strnstr(pars[set]->cmd[num], "$?", ft_strlen(pars[set]->cmd[num])))
		return (errorput(pars, set, num, ph));
	free(pars[set]->cmd[num]);
	if (pars[set]->env[ph->i] != NULL)
	{
		pars[set]->cmd[num] = ft_strjoin(ph->pre, ph->str);
		pars[set]->cmd[num] = ft_strjoin(pars[set]->cmd[num], ph->post);
	}
	else
		pars[set]->cmd[num] = ft_strdup("");
	return (0);
}

int	path(t_pars **pars, int set, int num)
{
	t_ph	ph;

	ph = (t_ph){0, 0, (char *) NULL, (char *) NULL, (char *) NULL};
	ph.str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	ph.pre = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	ph.post = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	pre(pars, set, num, &ph);
	if (pars[set]->cmd[num][ph.i] != '?')
		middle(pars, set, num, &ph);
	else
		ph.i++;
	ph.str = array_get_line(pars[set]->env, ph.str);
	retpath(pars, set, num, &ph);
	return (0);
}
