/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:12:53 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 13:52:06 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puttarr_fd(char **arr, int fd)
{
	int	j;

	j = 0;
	while (arr[j])
		ft_putendl_fd(arr[j++], fd);
}

void	ft_putcube_fd(char ***cube, int fd)
{
	int	k;

	k = 0;
	while (cube[k])
	{
		ft_puttarr_fd(cube[k++], fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_lstprint(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		ft_printf("LIST ITEM:%i:%s:\n", i, list->content);
		list = list->next;
		i++;
	}
}

void	print_exp(t_pars **pars)
{
	int	i;
	int	j;
	int	total;

	total = pars[0]->total_cmd;
	i = 0;
	while (i < total)
	{
		j = 0;
		while (pars[i]->cmd[j])
			j++;
		i++;
	}
}
