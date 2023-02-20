/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:02:39 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/20 16:54:07 by pgorner          ###   ########.fr       */
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
	while (i < total)
	{
		printf("CURRENTLY WORKING ON PARS[%i]\n", i);
		printf("-----------------------------------------------------\n");
		j = 0;
		while (pars[i]->cmd[j])
		{
			printf("CMD#%i:%i:%s:\n", i, j, pars[i]->cmd[j]);
			j++;
		}
		i++;
	}
}

int	rm_bs(t_pars **pars, int set, int num)
{
	int r;
	int b;
	int i;
	int j;
	char *str;

	r = 0;
	b = 0;
	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	while (TRUE)
	{
		if(pars[set]->cmd[num][i] == '\\')
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
			break;
	}
	str[j] = '\0';
	free(pars[set]->cmd[num]);
	pars[set]->cmd[num] = ft_strdup(str);
	free(str);
	return(r);
}


int rm_quot(t_pars **pars, int set, int num)
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
		if (((pars[set]->cmd[num][i] == '\"'
			&& pars[set]->cmd[num][i - 1] != '\\')
			|| (pars[set]->cmd[num][i] == '\''))
			&& pars[set]->cmd[num][i] != '\0')
		{
			last = i++;
			while (TRUE && pars[set]->cmd[num][i] != '\0')
			{
				if (pars[set]->cmd[num][i] == '$' && pars[set]->cmd[num][last] == '\'')
					r = 1;
				if (pars[set]->cmd[num][i] == pars[set]->cmd[num][last])
				{
					if (pars[set]->cmd[num][i] == '\"'
					&& pars[set]->cmd[num][i - 1] == '\\')
						str[j++] = pars[set]->cmd[num][i++];
					else
					{
						if (pars[set]->cmd[num][i + 1] != '\0')
							i++;
						break;
					}
				}
				else
					str[j++] = pars[set]->cmd[num][i++];
			}
		}
		if (pars[set]->cmd[num][i + 1] == '\0')
			break;
		if(check(pars[set]->cmd[num][i], "\"\'") == FALSE
			|| (pars[set]->cmd[num][i] == '\"'
			&& pars[set]->cmd[num][i - 1] == '\\'))
			str[j++] = pars[set]->cmd[num][i++];
	}
	str[j] = '\0';
	free(pars[set]->cmd[num]);
	pars[set]->cmd[num] = ft_strdup(str);
	free(str);
	return (r);
}
//i < ft_strlen(pars[set]->cmd[num]) && 

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
	char	*postpath;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	prepath = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	postpath = ft_calloc(sizeof(char), ft_strlen(pars[set]->cmd[num]));
	while (pars[set]->cmd[num][i] != '$')
		prepath[j++] = pars[set]->cmd[num][i++];
	printf("PREPATH: %s\n", prepath);
	i++;
	if (pars[set]->cmd[num][i] == '?')
		return (errorput(pars, set, num, prepath));
	j = 0;
	while (check(pars[set]->cmd[num][i + 1], "$\n") == FALSE
			&& is_whitespace(pars[set]->cmd[num][i + 1]) == FALSE
			&& pars[set]->cmd[num][i + 1] != '\0')
			str[j++] = pars[set]->cmd[num][i++];
	str[j] = '\0';
	j = 0;
	while (pars[set]->cmd[num][i] != '\0')
		postpath[j++] = pars[set]->cmd[num][i++];
	postpath[j] = '\0';
	printf("PATH: %s\n", str);
	i = 0;
	while(pars[set]->env[i] && ft_strncmp(str, ft_substr(pars[set]->env[i], 0, ft_strlen(str)), ft_strlen(pars[set]->env[i])) != 0)
		i++;
	free(pars[set]->cmd[num]);
	if (pars[set]->env[i] != NULL)
	{
		pars[set]->cmd[num] = ft_strjoin(prepath, ft_substr(pars[set]->env[i], ft_strlen(str) + 1, ft_strlen(pars[set]->env[i]) - ft_strlen(str)));
		pars[set]->cmd[num] = ft_strjoin(pars[set]->cmd[num], postpath);
	}
	else
		pars[set]->cmd[num] = ft_strdup("");
	return(0);
}

void	cmd_expand(t_pars **pars, char **cmds, char **env, int set)
{
	int num;
	int v;
	
	v = 0;
	num = 0;
	while (cmds[num])
	{
		printf("OG:   %s    v: %i\n", pars[set]->cmd[num], v);
		if (ft_strchr(pars[set]->cmd[num], '\'')
			|| ft_strchr(pars[set]->cmd[num], '\"'))
			v = rm_quot(pars, set, num);
		printf("quot: %s    v: %i\n", pars[set]->cmd[num], v);
		if (ft_strchr(pars[set]->cmd[num], '\\'))
			v = rm_bs(pars, set, num);
		printf("bs:   %s    v: %i\n", pars[set]->cmd[num], v);
		if (ft_strchr(pars[set]->cmd[num], '$') && v == 0)
			path(pars, set, num);
		printf("path: %s    v: %i\n", pars[set]->cmd[num], v);
		printf("----------------------expanddone\n");
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
	print_exp(pars);
	return (pars);
}
