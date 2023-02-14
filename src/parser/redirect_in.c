/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:19:04 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 20:39:40 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*redirect_in(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return (list);
	fd = open(list->next->content, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return (list->next);
	}
	if (pars->in > 2)
		close(pars->in);
	pars->in = fd;
	return (list->next);
}
