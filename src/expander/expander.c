/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:02:39 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 17:32:44 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bs_loop(t_pars **pars, int set, int num, t_bs *bs)
{
	while (TRUE)
	{
		if (pars[set]->cmd[num][bs->i] == '\\')
		{
			if (bs->b == TRUE)
			{
				if (pars[set]->cmd[num][bs->i] == '$')
					bs->r = 1;
				bs->str[bs->j++] = pars[set]->cmd[num][bs->i++];
				bs->b = FALSE;
			}
			else if (bs->b == FALSE)
			{
				bs->i++;
				bs->b = TRUE;
			}
		}
		else if (pars[set]->cmd[num][bs->i] != '\0')
			bs->str[bs->j++] = pars[set]->cmd[num][bs->i++];
		else
			break ;
	}
}

int	rm_bs(t_pars **pars, int set, int num)
{
	t_bs	bs;

	bs = (t_bs){0, 0, 0, 0, (char *) NULL};
	bs.str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	bs_loop(pars, set, num, &bs);
	bs.str[bs.j] = '\0';
	free(pars[set]->cmd[num]);
	pars[set]->cmd[num] = ft_strdup(bs.str);
	free(bs.str);
	return (bs.r);
}

void	cmd_expand(t_pars **pars, char **cmds, int set)
{
	int	num;
	int	v;

	v = 0;
	num = 0;
	while (cmds[num])
	{
		if (ft_strchr(pars[set]->cmd[num], '\'')
			|| ft_strchr(pars[set]->cmd[num], '\"'))
			v = rm_quot(pars, set, num);
		if (ft_strchr(pars[set]->cmd[num], '\\'))
			v = rm_bs(pars, set, num);
		if (ft_strchr(pars[set]->cmd[num], '$') && v == 0)
			path(pars, set, num);
		num++;
	}
}

t_pars	**expander(t_pars **pars)
{
	int	i;
	int	total;

	i = 0;
	total = pars[0]->total_cmd;
	while (i < total)
	{
		cmd_expand(pars, pars[i]->cmd, i);
		i++;
	}
	print_exp(pars);
	return (pars);
}
