/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:42 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/29 12:20:15 by fsandel          ###   ########.fr       */
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

void	utils(void)
{
	ft_printf("utils loaded\n");
}
