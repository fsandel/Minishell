/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:29:21 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 16:16:07 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_alpha_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	string_is_digit(char *str)
{
	int		i;
	size_t	sign;

	sign = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '+' || str[i] == '-')
				sign++;
		}
		else
			return (0);
		i++;
	}
	if (ft_strlen(str) == sign)
		return (0);
	return (1);
}
