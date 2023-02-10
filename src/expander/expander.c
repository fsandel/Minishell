/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:02:39 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 18:15:18 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_str(char *str, char **env);

t_pars	**expander(t_pars **pars)
{
	int	i;
	int	j;

	j = 0;
	while (pars[j])
	{
		i = 0;
		while (pars[j]->cmd[i])
		{
			pars[j]->cmd[i] = expand_str(pars[j]->cmd[i], pars[i]->env);
			i++;
		}
		j++;
	}
	return (pars);
}

char	*expand_str(char *str, char **env)
{
	t_c	c;
	int	i;

	c = (t_c){.esc = 0, .sgl = 0, .dbl = 0};
	i = 0;
	
	c = (t_c){.esc = c.esc, .sgl = c.sgl, .dbl = c.dbl + 1};
	printf("=== %d ===\n", c.dbl);
	// while (str[i])
	// {
	// 	if (str[i] == '\\' && c.esc = 0 && c.sgl = 0)
	// 		c.esc = 1;
		

	// }
	return (str);
}
