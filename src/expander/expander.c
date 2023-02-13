/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:02:39 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 21:49:56 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int err;

void	print_exp(t_pars **pars)
{
	int i;
	int j;
	int total;
	
	total = pars[0]->total_cmd; 
	i = 0;
	j = 0;
	while (i <total)
	{
		printf("CURRENTLY WORKING ON PARS[%i]\n", i);
		printf("-----------------------------------------------------\n");
		while (pars[i]->cmd[j])
		{
			printf("CMD#%i:%s:\n", i, pars[i]->cmd[i]);
			j++;
		}
		i++;
	}
}

void rm_quot(t_pars **pars, int set, int num)
{
	int		i;
	int		j;
	int		k;
	int		c;
	int		s;
	int		last;
	char	*str;

	if (pars[set]->cmd[num][0] == '\"')
		k = 1;
	i = 0;
	s = 0;
	c = 0;
	j = 0;
	last = -1;
	str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]) - 2);
	while (i < ft_strlen(pars[set]->cmd[num]))
	{
		if (pars[set]->cmd[num][i] == '\"' 
			&& pars[set]->cmd[num][i - 1] != '\\' 
			|| pars[set]->cmd[num][i] == '\'')
		{
			last = i++;
			while (pars[set]->cmd[num][i] != '\0')
			{
				if (pars[set]->cmd[num][i] == '\\'
				&& pars[set]->cmd[num][last] == '\"')
				{
					if (s == 1)
						s = 0;
					else
					{
						i++;
						s++;
					}
				}
				if (pars[set]->cmd[num][i] == pars[set]->cmd[num][last] 
					&& i != last)
				{
					if (pars[set]->cmd[num][i] == '\"'
					&& pars[set]->cmd[num][i - 1] == '\\')
					{
						if (s == 1)
						{
							str[j++] = pars[set]->cmd[num][i++];
							s = 0;
						}
						else
							i++;
					}
					else
						break;
				}
				str[j++] = pars[set]->cmd[num][i++];
			}
		}
		if (pars[set]->cmd[num][i] != '\"'
			&& pars[set]->cmd[num][i] != '\'')
			str[j++] = pars[set]->cmd[num][i++];
		else
			i++;
	}
	str[j] = '\0';
	free(pars[set]->cmd[num]);
	pars[set]->cmd[num] = ft_strdup(str);
	free(str);
}


int	errorput(t_pars **pars, int set, int num, char *prepath)
{
	pars[set]->cmd[num] = ft_strjoin(prepath, ft_itoa(err));
	return(1);	
}

int	path(t_pars **pars, int set, int num)
{
	int i;
	int j;
	char	*str;
	char	*path;
	char	*prepath;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	prepath = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	while (pars[set]->cmd[num][i] != '$')
		prepath[j++] = pars[set]->cmd[num][i++];
	i++;
	if (pars[set]->cmd[num][i] == '?')
		return (errorput(pars, set, num, prepath));
	j = 0;
	while (check(pars[set]->cmd[num][i], "$\n") == FALSE
			&& is_whitespace(pars[set]->cmd[num][i]) == FALSE
			&& pars[set]->cmd[num][i] != '\0')
			str[j++] = pars[set]->cmd[num][i++];
	str[j] = '\0';
	i = 0;
	while(pars[set]->env[i] && ft_strncmp(str, ft_substr(pars[set]->env[i], 0, ft_strlen(str)), ft_strlen(pars[set]->env[i])) != 0)
		i++;
	free(pars[set]->cmd[num]);
	if (pars[set]->env[i] != NULL)
		pars[set]->cmd[num] = ft_strjoin(prepath, ft_substr(pars[set]->env[i], ft_strlen(str) + 1, ft_strlen(pars[set]->env[i]) - ft_strlen(str)));
	else
		pars[set]->cmd[num] = ft_strdup("\n");
	return(0);
}

void	cmd_expand(t_pars **pars, char **cmds, char **env, int set)
{
	int num;
	
	num = 0;
	while (cmds[num])
	{
		if (ft_strchr(pars[set]->cmd[num], '\'')
			|| ft_strchr(pars[set]->cmd[num], '\"'))
			rm_quot(pars, set, num);
		if (ft_strchr(pars[set]->cmd[num], '$'))
			path(pars, set, num);
		num++;
	}
}

t_pars	**expander(t_pars **pars)
{
	int i;
	int total;
	
	i = 0;
	total = pars[0]->total_cmd; 
	while (i < total)
	{
		cmd_expand(pars, pars[i]->cmd, pars[i]->env, i);
		i++;
	}
	return (pars);
}

/* "<>|" fällt wgetasd
asd$US asd
asd asd
pgorner


if $ not found rm until whitespace?
rm "" & ''
if '' no expand
if escape character also no expand??


asdasdasd$USER
 */