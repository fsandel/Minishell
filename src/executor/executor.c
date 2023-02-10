/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:01:38 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 15:35:32 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(t_pars *pars, char **path);
int	execute_child(t_pars *pars, int infd);
char	*compact(char **array);
char	**get_path(char **env);

char	**get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

t_pars	**executor(t_pars **pars)
{
	char *path;
	int	fd;
	int	i;
	int	total;

	total = pars[0]->total_cmd;
	i = 0;
	fd = pars[0]->in;
	while (i < total)
	{
		fd = execute_child(pars[i++], fd);
	}
	waitpid(0, NULL, 0);
	close(fd);
	return (pars);
}


char	*check_path(t_pars *pars, char **path)
{
	int		i;
	int		j;
	int		c;
	char	*tmp;

	c = 0;
	while (path && path[c])
	{
		i = 0;
		j = 0;
		tmp = ft_calloc(1, ft_strlen(pars->cmd[0]) + ft_strlen(path[c]) + 2);
		while (path[c][i] != '\0')
		{
			tmp[i] = path[c][i];
			i++;
		}
		tmp[i++] = '/';
		while (pars->cmd[0][j] != '\0')
			tmp[i++] = pars->cmd[0][j++];
		tmp[i] = '\0';
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		c++;
	}
	return (NULL);
}

void	execute(t_pars *pars)
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

int	execute_child(t_pars *pars, int infd)
{
	int			fd[2];
	pid_t		pid;
	char		*command;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
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
