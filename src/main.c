/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/28 16:12:34 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int *test = malloc(150);
	int *p = NULL;

	sleep(10);
	*p = 19;
	exit (0);
}

void	ft_free(void **arg, char *loc) // void loc at end
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

//ft_free = prozess wenn null freen wenn 1 nicht sodass nicht double free ist
// ggf argument mitgeben von wo gefreet wird sodass man weiß von woher was kommt
// argument dann zu void casten 