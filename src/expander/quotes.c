/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:39:28 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/28 18:39:51 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qq(t_pars **pars, t_x *x)
{
	x->i++;
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
