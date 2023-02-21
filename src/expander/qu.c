/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qu.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:25:53 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/21 12:09:38 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	findend(t_pars **pars, int set, int num, t_qu *qu)
{
	qu->last = qu->i++;
	while (TRUE && pars[set]->cmd[num][qu->i] != '\0')
	{
		if (pars[set]->cmd[num][qu->i] == '$'
			&& pars[set]->cmd[num][qu->last] == '\'')
			qu->r = 1;
		if (pars[set]->cmd[num][qu->i] == pars[set]->cmd[num][qu->last])
		{
			if (check_two(pars, set, num, qu->i) == TRUE)
				qu->str[qu->j++] = pars[set]->cmd[num][qu->i++];
			else
			{
				qu->i++;
				break ;
			}
		}
		else
			qu->str[qu->j++] = pars[set]->cmd[num][qu->i++];
	}
}

int	rm_quot(t_pars **pars, int set, int num)
{
	t_qu	qu;

	qu = (t_qu){0, 0, 0, 0, (char *) NULL};
	qu.str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	while (qu.i < ft_strlen(pars[set]->cmd[num]))
	{
		if (check_one(pars, set, num, qu.i) == TRUE)
			findend(pars, set, num, &qu);
		if (pars[set]->cmd[num][qu.i] == '\0')
			break ;
		if (check_three(pars, set, num, qu.i) == TRUE)
			qu.str[qu.j++] = pars[set]->cmd[num][qu.i++];
	}
	qu.str[qu.j] = '\0';
	free(pars[set]->cmd[num]);
	pars[set]->cmd[num] = ft_strdup(qu.str);
	free(qu.str);
	return (qu.r);
}
