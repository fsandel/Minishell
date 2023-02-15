/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:01:38 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/15 10:09:10 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_child(t_pars *pars, int infd);
static void	execute(t_pars *pars);

t_pars	**executor(t_pars **pars)
{

	int		fd;
	int		i;
	int		total;
	int		status;

	total = pars[0]->total_cmd;
	i = 0;
	fd = pars[0]->in;
	while (i < total)
		fd = execute_child(pars[i++], fd);
	i = 0;
	while (i++ < total)
		waitpid(0, &status, 0);
	close(fd);
	if (WIFEXITED(status))
		g_error = WEXITSTATUS(status);
	else
		g_error = 130;
	return (pars);
}

static void	execute(t_pars *pars)
{
	char	*command;
	char	**path;

	path = get_path(pars->env);
	builtin(pars);
	command = check_path(pars, path);
	free(path);
	if (pars->error == 0)
		execve(command, &pars->cmd[0], pars->env);
	else
		exit(1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pars->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(command);
	exit(127);
}

static int	execute_child(t_pars *pars, int infd)
{
	int			fd[2];
	pid_t		pid;
	char		*command;

	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		dup_input(infd, pars);
		dup_output(fd[1], pars);
		smart_close(fd[0], fd[1], 0, 0);
		smart_close(pars->in, pars->out, pars->err, infd);
		execute(pars);
	}
	smart_close(pars->in, pars->out, pars->err, infd);
	close(fd[1]);
	return (fd[0]);
}
