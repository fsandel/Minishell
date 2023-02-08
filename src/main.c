/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/08 14:40:20 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(char *input);

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;

	path = getcwd(NULL, 0);
	prompt = ft_strjoin(path, ": ");
	free(path);
	return (prompt);
}

int	main(void)
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
		add_history(input);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		if (check_input(input))
			ft_putendl_fd("bad quotes", 2);
		else
			command(input);
	}
	system("leaks minishell");
	return (0);
}

void	command(char *input)
{
	t_list	*tokens;
	t_pars	**pars;

	ft_putendl_fd("NOW LEXER", 2);
	tokens = lexer(input);
	free(input);
	ft_putendl_fd("NOW PARSER", 2);
	pars = parser(tokens);
	ft_lstclear(&tokens, free);
	ft_putendl_fd("NOW EXECUTOR", 2);
	executor(pars);
	free_struct(pars);
}
