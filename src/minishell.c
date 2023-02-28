/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:05:26 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 20:04:39 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nice_exit(char **env, char *input);
char	*get_prompt(void);
char	**command(char *input, char **old_env);

int	minishell(char *old_env[])
{
	char	*input;
	char	*prompt;
	char	**env;

	env = copy_arr(old_env);
	while (1)
	{
		disable_echo();
		signal(SIGINT, signal_handler_interactive);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt();
		input = get_input(prompt);
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
	if (!pars || check_empty(pars))
		return (old_env);
	env = pars[0]->env;
	pars = expander(pars);
	env = executor(pars);
	free_struct(pars);
	return (env);
}
