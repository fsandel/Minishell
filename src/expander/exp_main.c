/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:27:36 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/01 18:07:31 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addtocmds(t_pars **pars, t_x *x)
{
	int	i;

	i = 0;
	if (!x->o)
		x->o = array_add_line(x->o, "");
	if (x->o)
	{
		while (x->o[i])
		{
			pars[x->s]->cmd = array_add_line(pars[x->s]->cmd, x->o[i]);
			free(x->o[i]);
			i++;
		}	
		free(x->o);
	}
}

void	end_cmd(t_pars **pars, t_x *x)
{
	if (pars[x->s]->cmd[0] != NULL)
	{
		free_array(pars[x->s]->cmd);
		pars[x->s]->cmd = NULL;
		addtocmds(pars, x);
	}
}

void	cmd_expand(t_pars **pars, char **cmds, int s)
{
	t_x	x;
	int	i;

	x = (t_x){0, 0, 0, s, 0, 0, 0, (char **) NULL, (char *) NULL};
	while (cmds[x.n])
	{
		i = 0;
		x = (t_x){0, 0, x.p, x.s, x.n, 0, x.pd, x.o, (char *) NULL};
		while (TRUE && ft_strlen(pars[x.s]->cmd[x.n]))
		{
			normalstring(pars, &x);
			backslash(pars, &x);
			quotes(pars, &x);
			expanding(pars, &x);
			if (pars[x.s]->cmd[x.n][x.i] == '\0')
			{
				if (x.str != NULL)
					set_str(&x);
				break ;
			}
		}
		x.n++;
	}
	end_cmd(pars, &x);
}

t_pars	**expander(t_pars **pars)
{
	int	i;
	int	total;

	i = -1;
	total = pars[0]->total_cmd;
	while (++i < total)
		cmd_expand(pars, pars[i]->cmd, i);
	return (pars);
}
