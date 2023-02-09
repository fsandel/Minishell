/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:19:04 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/09 13:00:07 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return ;
	fd = open(list->next->content, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return ;
	}
	if (pars->in > 2)
		close(pars->in);
	ft_printf("Redirecting in\n");
	pars->in = fd;
}

void	here_doc(t_list *list, t_pars *pars)
{
	ft_printf("Dont forget to implement here_doc");
}