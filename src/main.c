/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 21:29:21 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell(char *old_env[]);
char	**command(char *input, char **old_env);
int		g_error;

int	main(int argc, char *argv[], char *old_env[])
{
	(void)argc;
	(void)argv;
	g_error = 0;
	ft_putendl_fd("\nThe default interactive shell is now minishell.", 2);
	ft_putendl_fd("If you dont want to, feels bad, you are trapped here.", 2);
	ft_putendl_fd("forever", 2);
	minishell(old_env);
	return (g_error);
}

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;

	path = getcwd(NULL, 0);
	prompt = ft_strjoin(path, ": ");
	free(path);
	return (prompt);
}

void	nice_exit(char **env, char *input)
{
	char	*prompt;

	prompt = get_prompt();
	ft_printf("%s%sexit\n", "\033[A", prompt);
	free(prompt);
	free_array(env);
	free(input);
}

int	minishell(char *old_env[])
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
			return (nice_exit(env, input), g_error);
		else if (!ft_strncmp(input, "", 1))
			empty_input_handler(input);
		else if (check_input(input))
			bad_quote_handler(input);
		else
			env = command(input, env);
	}
	return (g_error);
}

char	**command(char *input, char **old_env)
{
	t_list	*tokens;
	t_pars	**pars;
	char	**env;

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
