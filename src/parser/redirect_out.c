/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:04:02 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/14 14:56:07 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*redirect_out(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return(list);
	fd = open(list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

t_list	*redirect_err(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return(list);
	fd = open(list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

t_list	*redirect_both(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return(list);
	fd = open(list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
