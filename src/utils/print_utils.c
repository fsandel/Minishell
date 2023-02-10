/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:12:53 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 16:16:47 by fsandel          ###   ########.fr       */
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
