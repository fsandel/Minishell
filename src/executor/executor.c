/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:01:38 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/22 16:34:15 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_child(t_pars **pars, int infd, int i);
static void	execute(t_pars **pars, int i);

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

int	execve_error(char *cmd, char *og_cmd)
{
	int			error;
	struct stat	st;
	int			status;

	status = stat(og_cmd, &st);
	error = 0;
	if (!cmd)
	{
		error = 127;
		ft_err_print("minishell: %s: command not found\n", og_cmd, NULL, NULL);
	}
	else if (!status && S_ISDIR(st.st_mode))
	{
		error = 127;
		ft_err_print("minishell: %s: is a directory\n", og_cmd, NULL, NULL);
	}
	else
	{
		ft_err_print("minishell: %s ", og_cmd, NULL, NULL);
		perror("");
		error = 126;
	}
	return (error);
}

static void	execute(t_pars **pars, int i)
{
	char	*command;
	char	**path;

	if (pars && pars[i] && pars[i]->cmd && pars[i]->cmd[0])
	{
		builtin(pars, i);
		path = get_path(pars[i]->env);
		command = check_path(pars[i], path);
		if (path)
			free_array(path);
		if (pars[i]->error == 0)
			execve(command, &pars[i]->cmd[0], pars[i]->env);
		else
			exit(1);
		g_error = execve_error(command, pars[i]->cmd[0]);
		free(command);
	}
	free_array(pars[0]->env);
	free_struct(pars);
	exit(g_error);
}

static int	execute_child(t_pars **pars, int infd, int i)
{
	int			fd[2];

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
