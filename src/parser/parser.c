/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:05 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/06 10:32:22 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars **setup_struct(t_list *list);
int	count_commands(t_list *list);
t_pars	**fill_struct(t_list *list, t_pars **pars);

void	display_pars(t_pars **pars)
{
	int	i;
	int	total;
	int	j;

	total = pars[0]->total_cmd;
	i = 0;
	while (i < total)
	{
		j = 1;
		ft_printf("bin: %s\n\n", pars[i]->cmd[0]);
		while (j < pars[i]->amount)
			ft_printf("cmd: %s\n", pars[i]->cmd[j++]);
		ft_printf("\nin: %d\tout: %d\terr: %d\n\n", pars[i]->in, pars[i]->out, pars[i]->err);
		i++;
	}
}
t_pars	**parser(t_list *list)
{
	t_pars	**pars;

	ft_printf("in parser\n");
	pars = setup_struct(list);
	ft_printf("setup struct done\n");
	pars = fill_struct(list, pars);
	ft_lstclear(&list, free);
	display_pars(pars);
	return (pars);
}

char	*str_append(char *first, char *second)
{
	char	*ret;
	if (!second)
		return (first);
	if (!first)
		return (ft_strdup(second));
	ret = ft_strjoin(first, second);
	free(first);
	return (ret);
}

t_pars	**fill_struct(t_list *list, t_pars **pars)
{
	int	line;
	int	fd;
	int	i;

	i = 0;
	line = 0;
	while (list)
	{
		if (list->content && !ft_strncmp(list->content, "|", 2))
		{
			i = 0;
			line++;
		}
		else if (list->content && !ft_strncmp(list->content, ">", 2))
		{
			if (!list->next)
				return (pars);
			redirect_out(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "2>", 3))
		{
			if (!list->next)
				return (pars);
			redirect_err(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "2>&1", 5))
		{
			if (!list->next)
				return (pars);
			pars[line]->err = pars[line]->out;
			list = list->next;
		}
		//implement > file 2>&1
		else if (list->content && !ft_strncmp(list->content, "&>", 3))
		{
			if (!list->next)
				return (pars);
			list = list->next;
			redirect_both(list, pars[line]);
		}
		else if (list->content && !ft_strncmp(list->content, ">>", 3))
		{
			if (!list->next)
				return (pars);
			append_out(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "2>>", 4))
		{
			if (!list->next)
				return (pars);
			append_err(list, pars[line]);
			list = list->next;
		}
		//implement >> file 2>&1
		else if (list->content && !ft_strncmp(list->content, "&>>", 4))
		{
			if (!list->next)
				return (pars);
			append_both(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "&>>", 4))
		{
			if (!list->next)
				return (pars);
			append_both(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "&>>", 4))
		{
			if (!list->next)
				return (pars);
			append_both(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "<", 2))
		{
			if (!list->next)
				return (pars);
			redirect_in(list, pars[line]);
			list = list->next;
			ft_printf("here\n");
		}
		else if (list->content && !ft_strncmp(list->content, "<<", 3))
		{
			if (!list->next)
				return (pars);
			here_doc(list, pars[line]);
			list = list->next;
		}
		else
		{
			if (list->content)
				pars[line]->cmd[pars[line]->amount++] = ft_strdup(list->content);
		}
		list = list->next;
	}
	return (pars);
}

t_pars **setup_struct(t_list *list)
{
	t_pars	**pars;
	int		commands;
	int		i;
	int		len;

	commands = count_commands(list);
	pars = ft_calloc(commands, sizeof(t_pars *));
	i = 0;
	while (i < commands)
	{
		pars[i] = ft_calloc(1, sizeof(t_pars));
		pars[i]->total_cmd = commands;
		pars[i]->err = 2;
		pars[i]->in = 0;
		pars[i]->out = 1;
		pars[i]->index = i;
		pars[i]->amount = 0;
		len = 0;
		while (list && ft_strncmp(list->content, "|", 2))
		{
			list = list->next;
			len++;
		}
		if (list)
			list = list->next;
		pars[i]->cmd = ft_calloc(len + 1, sizeof(char *));
		i++;
	}
	return (pars);
}

int	count_commands(t_list *list)
{
	int	size;

	size = 0;
	while (list)
	{
		if (list->content && !ft_strncmp(list->content, "|", 2))
			size++;
		list = list->next;
	}
	return (size + 1);
}
