/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/16 15:01:55 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**command(char *input, char **old_env);
char	**arr_del_line(char **arr, char *ln);
char	**array_add_line(char **arr, char *nl);
int		g_error;

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;

	path = getcwd(NULL, 0);
	prompt = ft_strjoin(path, ": ");
	free(path);
	return (prompt);
}

void	empty_input_handler(char *input)
{
	free(input);
	g_error = 1;
}

void	bad_quote_handler(char *input)
{
	ft_putendl_fd("minishell: input: bad quotes", 2);
	free(input);
	g_error = 1;
}


int	minishell(int argc, char *argv[], char *old_env[])
{
	char	*input;
	char	*prompt;
	char	**env;

	env = copy_arr(old_env);
	while (1)
	{
		signal(SIGINT, signal_handler_interactive);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		if (!input)
			return (free_array(env), free(input), g_error);
		else if (!ft_strncmp(input, "", 1))
			empty_input_handler(input);
		else if (check_input(input))
			bad_quote_handler(input);
		else
			env = command(input, env);
	}
	return (g_error);
}

int	main(int argc, char *argv[], char *old_env[])
{
	g_error = 0;
	minishell(argc, argv, old_env);
	return (g_error);
}

char	**command(char *input, char **old_env)
{
	t_list	*tokens;
	t_pars	**pars;
	char	**env;
	int		exec;

	add_history(input);
	tokens = lexer(input);
	free(input);
	if (ft_lstsize(tokens) == 0)
		return (g_error = 0, free(tokens), old_env);
	if (!tokens->content)
		return (g_error = 0, ft_lstclear(&tokens, free), old_env);
	pars = parser(tokens, old_env);
	ft_lstclear(&tokens, free);
	if (!pars)
		return (old_env);
	env = pars[0]->env;
	pars = expander(pars);
		env = executor(pars);
	free_struct(pars);
	return (env);
}
