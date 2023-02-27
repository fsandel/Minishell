/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:53:44 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/27 13:11:07 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	app(t_pars **pars, t_x *x)
{
	x->str = str_append(x->str, pars[x->s]->cmd[x->n][x->i++]);
}

void	find_dollar(t_pars **pars, t_x *x)
{
	char	*tmp;
	char	*tmpp;
	int		j;
	int		i;

	j = 0;
	i = 0;
	tmp = ft_calloc(sizeof(char), ft_strlen(pars[x->s]->cmd[x->n]));
	while (check(pars[x->s]->cmd[x->n][x->i], "$\n\\\"\'") == FALSE
		&& is_whitespace(pars[x->s]->cmd[x->n][x->i]) == FALSE
		&& pars[x->s]->cmd[x->n][x->i] != '\0'
		&& check(pars[x->s]->cmd[x->n][x->i], "\"\'") == FALSE)
			tmp[j++] = pars[x->s]->cmd[x->n][x->i++];
	tmp[j] = '\0';
	tmpp = array_get_line(pars[x->s]->env, tmp);
	free(tmp);
	if (tmpp != NULL)
	{
		while (tmpp[i])
			x->str = str_append(x->str, tmpp[i++]);
	}
	free(tmpp);
}

void	pute(t_x *x)
{
	char *tmp;
	char *tmpp;

	x->i += 2;
	tmp = ft_strdup(ft_itoa(g_error));
	if (x->str == NULL)
		x->str = ft_strdup(tmp);
	else
	{
		tmpp = ft_strjoin(x->str, tmp);
		free(x->str);
		x->str = ft_strdup(tmpp);
		free(tmpp);
	}
	free(tmp);
}

void	dollar(t_pars **pars, t_x *x)
{
	if (ft_isalpha(pars[x->s]->cmd[x->n][x->i + 1]) == TRUE
		||check(pars[x->s]->cmd[x->n][x->i + 1], "_") == TRUE)
	{
		x->i++;
		find_dollar(pars, x);
	}
	else
	{
		if (pars[x->s]->cmd[x->n][x->i + 1] == '?')
			pute(x);
		else if (!check(pars[x->s]->cmd[x->n][x->i + 1], "\"\'"))
			app(pars, x);
		else if (check(pars[x->s]->cmd[x->n][x->i + 1], "\"\'")
					&& check(pars[x->s]->cmd[x->n][x->i - 1], "\"\'"))
			app(pars, x);
		else
			x->i++;
	}
}

void	backslash(t_pars **pars, t_x *x)
{
	if (pars[x->s]->cmd[x->n][x->i] == '\\'
		&& x->b == FALSE)
	{
		x->i++;
		x->b = TRUE;
	}
}

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
		x = (t_x){0, 0, x.p, x.s, x.n, (char *) NULL};
		while (TRUE && pars[x.s]->cmd[x.n][x.i] != '\0')
		{
			normalstring(pars, &x);
			//printf("N:%s||at:%c:%i\n", x.str, pars[x.s]->cmd[x.n][x.i], x.i);
			backslash(pars, &x);
			//printf("B:%s||at:%c:%i\n", x.str, pars[x.s]->cmd[x.n][x.i], x.i);
			quotes(pars, &x);
			//printf("Q:%s||at:%c:%i\n", x.str, pars[x.s]->cmd[x.n][x.i], x.i);
			expanding(pars, &x);
			//printf("E:%s||at:%c:%i\n", x.str, pars[x.s]->cmd[x.n][x.i], x.i);
			if (pars[x.s]->cmd[x.n][x.i] == '\0' || x.i > 20)
			{
				set_str(pars, &x);
				//printf("BROKEN HERE:------------\n");
				break ;
			}
		}
		x.n++;
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
