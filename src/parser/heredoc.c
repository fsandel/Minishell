/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:42:28 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/07 09:46:48 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_quit(int status, t_pars *pars);
void	finish_heredoc(int fd[], t_pars *pars);

void	finish_heredoc_child(char **env, t_pars **pars, int *fd, char *limiter)
{
	free(limiter);
	smart_close(fd[0], fd[1], 0, 0);
	ft_lstclear(&pars[0]->list, free);
	free_array(env);
	free_struct(pars);
}

void	here_doc_child(char *limiter_uncut, int fd[2],
	char **env, t_pars **pars_full)
{
	char	*temp;
	char	*limiter;

	limiter = rm_quote(limiter_uncut);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		if (isatty(STDIN))
			temp = readline("> ");
		else
			temp = get_next_line(STDIN);
		if (temp == NULL)
			break ;
		if (!ft_strncmp(temp, limiter, ft_strlen(limiter) + 1))
			break ;
		if (ft_strchr(limiter_uncut, '\"') || ft_strchr(limiter_uncut, '\''))
			ft_putendl_fd(temp, fd[1]);
		else
			expand(temp, env, fd[1]);
		free(temp);
	}
	free(temp);
	finish_heredoc_child(env, pars_full, fd, limiter);
	ft_exit(0);
}

t_list	*here_doc(t_list *list, t_pars *pars, t_pars **pars_full)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!list->next)
		return (ft_putendl_fd("minishell: syntax error near unexpected token \
'newline'", STDERR), g_error = 258, pars->error = 1, NULL);
	if (!list->next->content)
		return (ft_putendl_fd("minishell: syntax error near unexpected token \
'newline'", STDERR), g_error = 258, pars->error = 1, NULL);
	if (unexpected_token(list->next->content))
		return (ft_putstr_fd("minishell: syntax error near unexpected token ",
				STDERR), ft_putendl_fd(list->next->content, STDERR),
			g_error = 258,
			pars->error = 1, NULL);
	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		here_doc_child(list->next->content, fd, pars->env, pars_full);
	waitpid(pid, &status, 0);
	handle_heredoc_quit(status, pars);
	finish_heredoc(fd, pars);
	return (list->next);
}

void	handle_heredoc_quit(int status, t_pars *pars)
{
	if (WIFSIGNALED(status))
	{
		write(STDOUT, "\n", 1);
		g_error = 1;
		pars->heredoc = 1;
	}
}

void	finish_heredoc(int fd[], t_pars *pars)
{
	signal(SIGINT, signal_handler_interactive);
	close(fd[1]);
	pars->in = fd[0];
}
