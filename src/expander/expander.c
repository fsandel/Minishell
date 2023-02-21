/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:02:39 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 12:08:51 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

int	rm_bs(t_pars **pars, int set, int num)
{
	int		r;
	int		b;
	int		i;
	int		j;
	char	*str;

	r = 0;
	b = 0;
	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	while (TRUE)
	{
		if (pars[set]->cmd[num][i] == '\\')
		{
			if (b == TRUE)
			{
				if (pars[set]->cmd[num][i] == '$')
					r = 1;
				str[j++] = pars[set]->cmd[num][i++];
				b = FALSE;
			}
			if (b == FALSE)
			{
				i++;
				b = TRUE;
			}
		}
		else if (pars[set]->cmd[num][i] == '\0')
			str[j++] = pars[set]->cmd[num][i++];
		else
			break ;
	}
	str[j] = '\0';
	free(pars[set]->cmd[num]);
	pars[set]->cmd[num] = ft_strdup(str);
	free(str);
	return (r);
}

void	cmd_expand(t_pars **pars, char **cmds, char **env, int set)
{
	int	num;
	int	v;

	v = 0;
	num = 0;
	printf("-------------------\n");
	while (cmds[num])
	{
		if (ft_strchr(pars[set]->cmd[num], '\'')
			|| ft_strchr(pars[set]->cmd[num], '\"'))
			v = rm_quot(pars, set, num);
		printf("/:%s:/\n", pars[set]->cmd[num]);
		if (ft_strchr(pars[set]->cmd[num], '\\'))
			v = rm_bs(pars, set, num);
		printf("/:%s:/\n", pars[set]->cmd[num]);
		if (ft_strchr(pars[set]->cmd[num], '$') && v == 0)
			path(pars, set, num);
		printf("/:%s:/\n", pars[set]->cmd[num]);
		num++;
	}
}

t_pars	**expander(t_pars **pars)
{
	int	i;
	int	total;

	i = 0;
	total = pars[0]->total_cmd;
	while (i < total)
	{
		cmd_expand(pars, pars[i]->cmd, pars[i]->env, i);
		i++;
	}
	print_exp(pars);
	return (pars);
}