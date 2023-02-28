/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:53:44 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/28 17:55:19 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	app(t_pars **pars, t_x *x)
{
	x->str = str_append(x->str, pars[x->s]->cmd[x->n][x->i++]);
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
		make_dollar(pars, x);
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
	int i;
	(void)pars;

	i = 0;
	if (x->str != NULL)
	{
		//printf("ADDING IN SET_STR:%s----d%i---ds%i--\n", x->str, x->d, x->ds);
		if (x->d == TRUE)
		{
			while(x->str[i])
			{

				x->out[last(x->out) - 1] = str_append(x->out[last(x->out) - 1], x->str[i]);
				i++;
			}
		}
		else
		{
			x->out = array_add_line(x->out, x->str);
		}
		//printf("OUTPUT SET_STR:%s:\n", x->out[last(x->out) - 1]);
/* 		i = 0;
		while (x->out[i])
			printf("%s\n", x->out[i++]); */
		//printf("-----------------\n");
		free(x->str);
	}
	x->d = FALSE;
}
/* void	set_str(t_pars **pars, t_x *x)
{
	if (x->str != NULL)
	{
		free(pars[x->s]->cmd[x->p]);
		pars[x->s]->cmd[x->p] = ft_strdup(x->str);
		//printf("OUTPUT:%s:\n", pars[x->s]->cmd[x->p]);
		x->p++;	
	}
} */

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

void	addtocmds(t_pars **pars, t_x *x)
{
	int	i;

	i = 0;
	if (!x->out)
		x->out = array_add_line(x->out, "");
	if (x->out)
	{
		while(i < last(x->out) && x->out)
		{
			pars[x->s]->cmd = array_add_line(pars[x->s]->cmd, x->out[i]);
			free(x->out[i]);
			//printf("%i:%s:%s:\n", i, pars[x->s]->cmd[i], x->out[i]);
			i++;
		}	
		free(x->out);
	}
}

void	cmd_expand(t_pars **pars, char **cmds, int s)
{
	t_x	x;
	int	i;

	x = (t_x){0, 0, 0, s, 0, 0, 0, 0, (char **) NULL, (char *) NULL};
	while (cmds[x.n])
	{
		i = 0;
		x = (t_x){0, 0, x.p, x.s, x.n, x.ds, x.pd, x.ds, x.out, (char *) NULL};
		//printf("NEEEEW STRIJNG-------%s--------\n", cmds[x.n]);
		while (TRUE && ft_strlen(pars[x.s]->cmd[x.n]))
		{
			//printf("-----------------\n");
			normalstring(pars, &x);
			//printf("ns:%i\n", x.d);
			backslash(pars, &x);
			//printf("bs:%i\n", x.d);
			quotes(pars, &x);
			//printf("qu:%i\n", x.d);
			expanding(pars, &x);
			//printf("expd:%i\n", x.d);
			if (pars[x.s]->cmd[x.n][x.i] == '\0')
			{
				if (x.str != NULL)
					set_str(pars, &x);
				break ;
			}
		}
/* 		printf("ONE STRING DONE: SUMMARY\n");
		i = 0;
		while (x.out[i])
			printf("%s\n", x.out[i++]);
		printf("---------------\n"); */
		x.n++;
	}
	if (pars[x.s]->cmd[0] != NULL)
	{
		free_array(pars[x.s]->cmd);
		pars[x.s]->cmd = NULL;
		addtocmds(pars, &x);	
	}
/* 	printf("EXP DONE--------------------------------------------------\n"); 
	printf("XOUT---------------\n");
	i = 0;
	while (x.out[i])
		printf("%s\n", x.out[i++]);
	printf("PARS---------------\n");
	i = 0;
	while (pars[x.s]->cmd[i])
		printf("%s\n", pars[x.s]->cmd[i++]);
	printf("END---\n"); */
}

t_pars	**expander(t_pars **pars)
{
	int	i;
	int	total;

	i = -1;
	//display_pars(pars);
	//printf("START\n");
	total = pars[0]->total_cmd;
	while (++i < total)
		cmd_expand(pars, pars[i]->cmd, i);
	//display_pars(pars);
	return (pars);
}
