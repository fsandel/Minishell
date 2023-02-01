/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:28:07 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/01 15:41:53 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	counter(char *content, char c)
{
	size_t i;
	size_t j;
	j = 0;
	i = 0;
	while(content[i] != '\0')
	{
		if (content[i] == '<')
			j++;
		i++;
	}
	return(j);
}
