/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:42 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/31 17:06:34 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* ft_free = prozess wenn null freen wenn 1 nicht sodass nicht double free ist
* ggf argument mitgeben von wo gefreet wird sodass man weiß von woher was kommt
* argument dann zu void casten 
*/
void	ft_free(void **arg, char *loc)
{
	//(void)loc;
	if (*arg)
	{
		free(*arg);
		*arg = 0;
	}
	else
		ft_printf("Doublefree at %s\n", loc);
}

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