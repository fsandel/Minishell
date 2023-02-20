/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:07:20 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/20 14:36:43 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_pars **pars)
{
	int	total;
	int	i;
	int	j;

	if (!pars)
		return ;
	total = pars[0]->total_cmd;
	i = 0;
	while (i < total)
	{
		j = 0;
		smart_close(pars[i]->in, pars[i]->out, pars[i]->err, 0);
		while (pars[i]->cmd[j])
			free(pars[i]->cmd[j++]);
		free(pars[i]->cmd);
		free(pars[i]);
		i++;
	}
	free(pars);
}

void	display_pars(t_pars **pars)
{
	int	i;
	int	total;
	int	j;

	total = pars[0]->total_cmd;
	i = 0;
	ft_printf("-----------------------------------------------------\n");
	while (i < total)
	{
		j = 1;
		ft_printf("index: %d   total:%d\n", pars[i]->index, pars[i]->total_cmd);
		ft_printf("bin: %s\n\n", pars[i]->cmd[0]);
		while (j < pars[i]->amount)
			ft_printf("cmd: %s\n", pars[i]->cmd[j++]);
		ft_printf("\nin: %d\tout: %d\terr: %d\n", pars[i]->in, pars[i]->out,
			pars[i]->err);
		ft_printf("-----------------------------------------------------\n");
		i++;
	}
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
