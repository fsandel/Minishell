/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:02:39 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/24 15:03:40 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	app(t_pars **pars, t_x *x)
{
	while (TRUE)
	{
		if (pars[x->s]->cmd[x->n][x->i] == '$')
			dollar(pars, x);
		else if (pars[x->s]->cmd[x->n][x->i] == '\\')
			backslash(pars, x);
		else if (pars[x->s]->cmd[x->n][x->i] == '\"'
				&& x->b == FALSE)
		{
			x->i++;
			break ;
		}
		else if (pars[x->s]->cmd[x->n][x->i] != '\0'
				&& x->b == TRUE)
		{
			app(pars, x);
			x->b = FALSE;
		}
		else if (pars[x->s]->cmd[x->n][x->i] != '\0')
			app(pars, x);
	}
}

void	q(t_pars **pars, t_x *x)
{
	x->i++;
	while (pars[x->s]->cmd[x->n][x->i] != '\'')
		app(pars, x);
	x->i++;
}

void	set_str(t_pars **pars, t_x *x)
{
	if (x->str != NULL)
	{
		free(pars[x->s]->cmd[x->p]);
		pars[x->s]->cmd[x->p] = ft_strdup(x->str);
		//printf("OUTPUT:%s:\n", pars[x->s]->cmd[x->p]);
		x->p++;	
	}
}

void	quotes(t_pars **pars, t_x *x)
{
	if (check(pars[x->s]->cmd[x->n][x->i], "\'\"") == TRUE
		&& x->b == FALSE)
	{
		if (pars[x->s]->cmd[x->n][x->i] == '\"')
			qq(pars, x);
		else
			q(pars, x);
	}
}

void	normalstring(t_pars **pars, t_x *x)
{
	while (check(pars[x->s]->cmd[x->n][x->i], "$\\\'\"") == FALSE
			&& pars[x->s]->cmd[x->n][x->i] != '\0')
		app(pars, x);
	if (check(pars[x->s]->cmd[x->n][x->i], "\'\"") == TRUE
		&& x->b == TRUE)
	{
		app(pars, x);
		x->b = FALSE;
	}
	if (pars[x->s]->cmd[x->n][x->i] == '\\' && x->b == TRUE)
		app(pars, x);
}

void	expanding(t_pars **pars, t_x *x)
{
	if (pars[x->s]->cmd[x->n][x->i] == '$')
		dollar(pars, x);
}

void	rmv_rest(t_pars **pars, t_x *x)
{
	while(x->p <= x->n && pars[x->s]->cmd[x->p])
	{
		//printf("FREEING:%s:\n", pars[x->s]->cmd[x->p]);
		/* free(pars[x->s]->cmd[x->p]); */
		ft_bzero(pars[x->s]->cmd[x->p], ft_strlen(pars[x->s]->cmd[x->p]));
		x->p++;
	}
}

void	cmd_expand(t_pars **pars, char **cmds, int s)
{
	t_x	x;

	x = (t_x){0, 0, 0, s, 0, (char *) NULL};
	while (cmds[x.n])
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
	rmv_rest(pars, &x);
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
