/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:15:15 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/02 16:28:47 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_out(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return ;
	fd = open(list->next->content, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return ;
	}
	if (pars->out > 2)
		close(pars->out);
	ft_printf("Apepnding out\n");
	pars->out = fd;
}

void	append_err(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return ;
	fd = open(list->next->content, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return ;
	}
	if (pars->err > 2)
		close(pars->err);
	ft_printf("Apepnding err\n");
	pars->err = fd;
}

void	append_both(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return ;
	fd = open(list->next->content, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return ;
	}
	if (pars->err > 2)
		close(pars->err);
	if (pars->out > 2)
		close(pars->out);
	ft_printf("Apepnding both\n");
	pars->err = fd;
	pars->out = fd;
}