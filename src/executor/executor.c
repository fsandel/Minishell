/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:01:38 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/18 11:43:48 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_child(t_pars **pars, int infd, int i);
static void	execute(t_pars **pars, int i);

int	check_builtin(t_pars **pars)
{
	if (pars && pars[0] && pars[0]->cmd[0] && pars[0]->total_cmd == 1)
	{
		if (!ft_strncmp(pars[0]->cmd[0], "cd", 3)
			|| !ft_strncmp(pars[0]->cmd[0], "unset", 6)
			|| !ft_strncmp(pars[0]->cmd[0], "export", 7)
			|| !ft_strncmp(pars[0]->cmd[0], "exit", 5))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

char	**do_builtin(t_pars **pars, char **env)
{
	if (!ft_strncmp(pars[0]->cmd[0], "cd", 3))
		env = b_cd(pars[0], env);
	else if (!ft_strncmp(pars[0]->cmd[0], "unset", 6))
		env = b_unset(pars[0]);
	else if (!ft_strncmp(pars[0]->cmd[0], "export", 7))
		env = b_export(pars[0]);
	else if (!ft_strncmp(pars[0]->cmd[0], "exit", 5))
		env = b_exit(pars, env);
	return (env);
}

char	**executor(t_pars **pars)
{
	int		fd;
	int		i;
	int		total;
	int		status;
	char	**env;

	env = pars[0]->env;
	if (check_builtin(pars))
		env = do_builtin(pars, env);
	else
	{
		total = pars[0]->total_cmd;
		i = 0;
		fd = pars[0]->in;
		while (i < total)
			fd = execute_child(pars, fd, i++);
		while (total--)
			waitpid(0, &status, 0);
		close(fd);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
		else
			g_error = 130;
	}
	return (env);
}

static void	execute(t_pars **pars, int i)
{
	char	*command;
	char	**path;

	path = get_path(pars[i]->env);
	builtin(pars, i);
	command = check_path(pars[i], path);
	free(path);
	if (pars[i]->error == 0)
		execve(command, &pars[i]->cmd[0], pars[i]->env);
	else
		exit(1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pars[i]->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(command);
	exit(127);
}

static int	execute_child(t_pars **pars, int infd, int i)
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
		dup_input(infd, pars[i]);
		dup_output(fd[1], pars[i]);
		smart_close(fd[0], fd[1], 0, 0);
		smart_close(pars[i]->in, pars[i]->out, pars[i]->err, infd);
		execute(pars, i);
	}
	smart_close(pars[i]->in, pars[i]->out, pars[i]->err, infd);
	close(fd[1]);
	return (fd[0]);
}
