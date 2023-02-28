/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:53:44 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/28 18:39:58 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backslash(t_pars **pars, t_x *x)
{
	if (pars[x->s]->cmd[x->n][x->i] == '\\'
		&& x->b == FALSE)
	{
		x->i++;
		x->b = TRUE;
	}
}

void	set_str(t_x *x)
{
	int	i;

	i = 0;
	if (x->str != NULL)
	{
		if (x->d == TRUE)
		{
			while (x->str[i])
				x->o[last(x->o) - 1] = str_append(x->o[last(x->o) - 1],
						x->str[i++]);
		}
		else
		{
			x->o = array_add_line(x->o, x->str);
		}
		free (x->str);
	}
	x->d = FALSE;
}

void	quotes(t_pars **pars, t_x *x)
{
	if (check(pars[x->s]->cmd[x->n][x->i], "\'\"") == TRUE
		&& x->b == FALSE)
	{
		if (check(pars[x->s]->cmd[x->n][0], "\'\"") == TRUE
			&& check(pars[x->s]->cmd[x->n][1], "\'\"") == TRUE
			&& pars[x->s]->cmd[x->n][2] == '\0')
		{
			x->str = ft_strdup("");
			x->i += 2;
		}
		else
		{
			if (pars[x->s]->cmd[x->n][x->i] == '\"')
				qq(pars, x);
			else
				q(pars, x);
		}
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
	{
		if (x->i != 0 && x->str != NULL)
			x->pd = TRUE;
		dollar(pars, x);
	}
}
