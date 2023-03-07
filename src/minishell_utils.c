/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:56:08 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/07 09:51:39 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_error_number(char *path)
{
	char	*num;
	char	*temp;

	path = str_append(path, ' ');
	path = str_append(path, '(');
	num = ft_itoa(g_error);
	temp = ft_strjoin(path, num);
	free(path);
	free(num);
	path = temp;
	path = str_append(path, ')');
	return (path);
}

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;
	char	*temp;

	path = getcwd(NULL, 0);
	if (DEBUG)
		path = append_error_number(path);
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

void	ft_exit(int ec)
{
	rl_clear_history();
	exit(ec);
}
