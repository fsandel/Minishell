/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:04:02 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 16:03:18 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return ;
	fd = open(list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return ;
	}
	if (pars->out > 2)
		close(pars->out);
	ft_printf("Redirecting out\n");
	pars->out = fd;
}

void	redirect_err(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return ;
	fd = open(list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return ;
	}
	if (pars->err > 2)
		close(pars->err);
	ft_printf("Redirecting err\n");
	pars->err = fd;
}

void	redirect_both(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return ;
	fd = open(list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return ;
	}
	if (pars->err > 2)
		close(pars->err);
	if (pars->out > 2)
		close(pars->out);
	ft_printf("Redirecting both\n");
	pars->err = fd;
	pars->out = fd;
}
