/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/09 16:51:51 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(char *input, char *env[]);

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;

	path = getcwd(NULL, 0);
	prompt = ft_strjoin(path, ": ");
	free(path);
	return (prompt);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		if (!ft_strncmp(input, "", 1))
		{
			free(input);
			continue;
		}
		if (!ft_strncmp(input, "exit", 5))
		{
			free(input);
			exit(0);
		}
		add_history(input);
		if (check_input(input))
			ft_putendl_fd("bad quotes", 2);
		else
			command(input, env);
	}
	//system("leaks minishell");
	return (0);
}

void	command(char *input, char *env[])
{
	t_list	*tokens;
	t_pars	**pars;

	ft_putendl_fd("NOW LEXER", 2);
	tokens = lexer(input);
	free(input);
	ft_putendl_fd("NOW PARSER", 2);
	pars = parser(tokens);
	ft_lstclear(&tokens, free);
	ft_putendl_fd("NOW EXPANDER", 2);
	pars = expander(pars);
	ft_putendl_fd("NOW EXECUTOR", 2);
	if (pars && pars[0] && pars[0]->total_cmd == 1 && !ft_strncmp(pars[0]->cmd[0], "cd", 3))
		b_cd(pars[0]);
	else
		pars = executor(pars, env);
	free_struct(pars);
	waitpid(0, NULL, 0);
}
