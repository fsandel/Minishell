/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:01:38 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/20 16:46:45 by fsandel          ###   ########.fr       */
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
		i = 0;
		while (i < total)
			waitpid(pars[i++]->pid, &status, 0);
		close(fd);
		set_g_error(status);
	}
	return (env);
}

static void	execute(t_pars **pars, int i)
{
	char	*command;
	char	**path;

	builtin(pars, i);
	path = get_path(pars[i]->env);
	command = check_path(pars[i], path);
	free_array(path);
	if (pars[i]->error == 0)
		execve(command, &pars[i]->cmd[0], pars[i]->env);
	else
		exit(1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pars[i]->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(command);
	free_array(pars[0]->env);
	free_struct(pars);
	exit(127);
}

static int	execute_child(t_pars **pars, int infd, int i)
{
	int			fd[2];
	pid_t		pid;

	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pars[i]->pid = fork();
	if (pars[i]->pid == 0)
	{
		enable_echo();
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
