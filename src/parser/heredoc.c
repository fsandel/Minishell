/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:38:56 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/14 16:39:25 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace(char *line, char **env, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && ft_isalpha(line[i]) || ft_isdigit(line[i]))
		i++;
	j = 0;
	while (env[j])
	{
		if (!ft_strncmp(line, env[j], i) && env[j][i] == '=')
		{
			ft_putstr_fd(&env[j][i + 1], fd);
			return (i + 1);
		}
		j++;
	}
	return (i + 1);
}

void	expand(char *line, char **env, int fd)
{
	char	*ret;
	t_q		q;

	q = (t_q){0, 0, 0, 0};
	while (line[q.i])
	{
		if (line[q.i] == '\\')
			q = (t_q){q.i + 1, 0, 0, (q.esc + 1) % 2};
		else if (line[q.i] == '$' && line[q.i + 1] == '$')
		{
			q = (t_q){q.i + 2, 0, 0, 0};
			ft_putstr_fd("PID", fd);
		}
		else if (line[q.i] == '$' && !q.esc && line[q.i + 1])
			q = (t_q){q.i + replace(&line[q.i + 1], env, fd), 0, 0, 0};
		else
		{
			ft_putchar_fd(line[q.i], fd);
			q = (t_q){q.i + 1, 0, 0, 0};
		}
	}
	ft_putchar_fd('\n', fd);
}

char	*rm_quote(char *str)
{
	char	*ret;
	int		j;
	t_q		q;

	q = (t_q){0, 0, 0, 0};
	j = 0;
	ret = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[q.i])
	{
		if (str[q.i] == '\\' && q.sgl == 0 && q.esc == 0)
			q = (t_q){q.i + 1, q.sgl, q.dbl, (q.esc + 1) % 2};
		else if (str[q.i] == '\'' && q.dbl == 0)
			q = (t_q){q.i + 1, (q.sgl + 1) % 2, q.dbl, q.esc = 0};
		else if (str[q.i] == '\"' && q.sgl == 0 && q.esc == 0)
			q = (t_q){q.i + 1, q.sgl, (q.dbl + 1) % 2, q.esc = 0};
		else
		{
			ret[j++] = str[q.i];
			q = (t_q){q.i + 1, q.sgl, q.dbl, q.esc = 0};
		}
	}
	return (ret);
}

void	here_doc_loop(char *limiter, int fd, char **env)
{
	char	*temp;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		temp = readline("> ");
		if (temp == NULL)
			break ;
		if (!ft_strncmp(temp, limiter, ft_strlen(limiter) + 1))
			break ;
		if (ft_strchr(limiter, '\"') || ft_strchr(limiter, '\''))
			ft_putendl_fd(temp, fd);
		else
			expand(temp, env, fd);
		free(temp);
	}
	free(temp);
	free(limiter);
}

t_list	*here_doc(t_list *list, t_pars *pars)
{
	int		fd[2];
	char	*limiter_no_quote;
	pid_t	pid;

	if (!(list->next || list->next->content))
	{
		ft_putendl_fd("here throw error and exit", 2);
		exit(258);
	}
	if (pipe(fd) < 0)
		exit(0);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		limiter_no_quote = rm_quote(list->next->content);
		here_doc_loop(limiter_no_quote, fd[1], pars->env);
		smart_close(fd[0], fd[1], 0, 0);
		exit(0);
	}
	close(fd[1]);
	waitpid(0, NULL, 0);
	pars->in = fd[0];
	signal(SIGINT, signal_handler_interactive);
	return (list->next);
}
