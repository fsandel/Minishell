/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/14 16:53:16 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**command(char *input, char **old_env);
char	**arr_del_line(char **arr, char *ln);
char	**array_add_line(char **arr, char *nl);
int		err;

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;

	path = getcwd(NULL, 0);
	prompt = ft_strjoin(path, ": ");
	free(path);
	return (prompt);
}

int	main(int argc, char *argv[], char *old_env[])
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
		{
			free_array(env);
			free(input);
			break ;
		}
		if (!ft_strncmp(input, "", 1))
		{
			free(input);
			err = 1;
			continue;
		}
		if (!ft_strncmp(input, "exit", 5))
		{
			free_array(env);
			free(input);
			break ;
		}
		add_history(input);
		if (check_input(input))
		{
			ft_putendl_fd("bad quotes", 2);
			free(input);
			err = 2;
			continue;
		}
		else
			env = command(input, env);
	}
	//system("leaks minishell");
	return (0);
}


char	**command(char *input, char **old_env)
{
	t_list	*tokens;
	t_pars	**pars;
	char	**env;

	//signal_bash();
	ft_putendl_fd("NOW LEXER", 2);
	tokens = lexer(input);
	ft_lstprint(tokens);
	free(input);
	if (ft_lstsize(tokens) == 0)
		return (NULL);
	ft_putendl_fd("NOW PARSER", 2);
	pars = parser(tokens, old_env);
	env = pars[0]->env;
	ft_lstclear(&tokens, free);
	ft_putendl_fd("NOW EXPANDER", 2);
	pars = expander(pars);
	ft_putendl_fd("NOW EXECUTOR", 2);
	if (pars && pars[0] && pars[0]->total_cmd == 1 && !ft_strncmp(pars[0]->cmd[0], "cd", 3))
		b_cd(pars[0]);
	else if (pars && pars[0] && pars[0]->total_cmd == 1 && !ft_strncmp(pars[0]->cmd[0], "unset", 6))
		env = b_unset(pars[0]);
	else if (pars && pars[0] && pars[0]->total_cmd == 1 && !ft_strncmp(pars[0]->cmd[0], "export", 7))
		env = b_export(pars[0]);
	else
		pars = executor(pars);
	waitpid(0, NULL, 0);
	free_struct(pars);
	return (env);
}
