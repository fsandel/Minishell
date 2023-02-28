/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:56:08 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 13:57:46 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;
	char	*temp;
	char	*num;

	path = getcwd(NULL, 0);
	path = str_append(path, ' ');
	path = str_append(path, '(');
	num = ft_itoa(g_error);
	temp = ft_strjoin(path, num);
	free(path);
	free(num);
	path = temp;
	path = str_append(path, ')');
	if (g_error)
	{
		temp = ft_strjoin(path, RED);
		prompt = ft_strjoin(temp, " > ");
		free(temp);
		temp = ft_strjoin(prompt, DEFAULT);
		return (free(prompt), free(path), temp);
	}
	else
		return (prompt = ft_strjoin(path, " >"), free(path), prompt);
}

void	nice_exit(char **env, char *input)
{
	char	*prompt;

	prompt = get_prompt();
	free(prompt);
	free_array(env);
	free(input);
}
