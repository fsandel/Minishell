/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:01:38 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 16:02:40 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_child(t_pars *pars, int infd);
static void	execute(t_pars *pars);

t_pars	**executor(t_pars **pars)
{
	char	*path;
	int		fd;
	int		i;
	int		total;

	total = pars[0]->total_cmd;
	i = 0;
	fd = pars[0]->in;
	while (i < total)
	{
		fd = execute_child(pars[i++], fd);
	}
	while (i-- + 1)
		wait(NULL);
	waitpid(0, NULL, 0);
	close(fd);
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
	execve(command, &pars->cmd[0], pars->env);
	ft_putstr_fd(pars->cmd[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free(command);
	exit(127);
}

static int	execute_child(t_pars *pars, int infd)
{
	int			fd[2];
	pid_t		pid;
	char		*command;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, signal_handler_bash);
		dup_input(infd, pars);
		dup_output(fd[1], pars);
		dup_error(pars);
		smart_close(fd[0], fd[1], 0, 0);
		smart_close(pars->in, pars->out, pars->err, infd);
		execute(pars);
	}
	smart_close(pars->in, pars->out, pars->err, infd);
	close(fd[1]);
	return (fd[0]);
}
