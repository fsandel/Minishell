/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:53:44 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/27 13:11:07 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bs_loop(t_pars **pars, int set, int num, t_bs *bs)
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
	return (pars);
}
