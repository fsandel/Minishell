/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:01:55 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/20 22:23:00 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_one(t_pars **pars, int set, int num, int i)
{
	if (((pars[set]->cmd[num][i] == '\"'
			&& pars[set]->cmd[num][i - 1] != '\\')
			| (pars[set]->cmd[num][i] == '\''))
			&& pars[set]->cmd[num][i] != '\0')
		return (TRUE);
	else
		return (FALSE);
}

int	check_two(t_pars **pars, int set, int num, int i)
{
	if (pars[set]->cmd[num][i] == '\"'
		&& pars[set]->cmd[num][i - 1] == '\\')
		return (TRUE);
	else
		return (FALSE);
}

int	check_three(t_pars **pars, int set, int num, int i)
{
	if (check(pars[set]->cmd[num][i], "\"\'") == FALSE
			|| (pars[set]->cmd[num][i] == '\"'
			&& pars[set]->cmd[num][i - 1] == '\\'))
		return (TRUE);
	else
		return (FALSE);
}

/* int	rm_quot(t_pars **pars, int set, int num)
{
	int		i;
	int		r;
	int		j;
	int		last;
	char	*str;

	i = 0;
	r = 0;
	j = 0;
	last = 0;
	
	str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	while (i < ft_strlen(pars[set]->cmd[num]))
	{
		if (check_one(pars, set, num, i) == TRUE)
		{
			last = i++;
			while (TRUE && pars[set]->cmd[num][i] != '\0')
			{
				if (pars[set]->cmd[num][i] == '$'
					&& pars[set]->cmd[num][last] == '\'')
					r = 1;
				if (pars[set]->cmd[num][i] == pars[set]->cmd[num][last])
				{
					if (check_two(pars, set, num, i) == TRUE)
						str[j++] = pars[set]->cmd[num][i++];
					else
					{
						if (pars[set]->cmd[num][i + 1] != '\0')
							i++;
						break ;
					}
				}
				else
					str[j++] = pars[set]->cmd[num][i++];
			}
		}
		if (pars[set]->cmd[num][i + 1] == '\0')
			break ;
		if (check_three(pars, set, num, i) == TRUE)
			str[j++] = pars[set]->cmd[num][i++];
	}
	str[j] = '\0';
	free(pars[set]->cmd[num]);
	pars[set]->cmd[num] = ft_strdup(str);
	free(str);
	return (r);
} */