/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:15:15 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/14 14:56:45 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*append_out(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return(list);
	fd = open(list->next->content, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return(list->next);
	}
	if (pars->out > 2)
		close(pars->out);
	pars->out = fd;
	return(list->next);
}

t_list	*append_err(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return(list);
	fd = open(list->next->content, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return(list->next);
	}
	if (pars->err > 2)
		close(pars->err);
	pars->err = fd;
	return(list->next);
}

t_list	*append_both(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return(list);
	fd = open(list->next->content, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return(list->next);
	}
	if (pars->err > 2)
		close(pars->err);
	if (pars->out > 2)
		close(pars->out);
	pars->err = fd;
	pars->out = fd;
	return(list->next);
}
