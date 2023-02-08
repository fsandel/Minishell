/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:01:38 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/08 15:10:26 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char *cpath);
int	execute_child(t_pars *pars, int infd);
char	*compact(char **array);

t_pars	**executor(t_pars **pars)
{
	char *path;
	int	fd;
	int	i;
	int	total;
	ft_printf("in executor\n");
	total = pars[0]->total_cmd;
	i = 0;
	fd = execute_child(pars[i++], STDIN);
	while (i < total)
	{
		ft_printf("index: %d   total: %d\n", pars[i]->index, pars[i]->total_cmd);
		fd = execute_child(pars[i++], fd);
	}
	waitpid(0, NULL, 0);
	return (pars);
}


char	*check_path(char *cpath)
{
	int		i;
	int		j;
	int		c;
	char	*tmp;
	char	**env;

	env = ft_split(getenv("PATH"), ':');
	c = 0;
	while (env[c])
	{
		i = 0;
		j = 0;
		tmp = ft_calloc(1, ft_strlen(cpath) + ft_strlen(env[c]) + 2);
		while (env[c][i] != '\0')
		{
			tmp[i] = env[c][i];
			i++;
		}
		tmp[i++] = '/';
		while (cpath[j] != '\0')
			tmp[i++] = cpath[j++];
		tmp[i] = '\0';
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		c++;
	}
	return (NULL);
}

char	*compact(char **array)
{
	char *str;
	int	len;
	int	i;
	int	j;

	if (!array)
		return (NULL);
	if (!array[0])
		return (NULL);
	len = 0;
	i = 0;
	while (array[i])
		len += ft_strlen(array[i++]);
	str = ft_calloc(len + i + 1, 1);
	j = 0;
	len = 0;
	while (j < i)
	{
		ft_memmove(&str[len], array[j], ft_strlen(array[j]));
		len += ft_strlen(array[j++]);
		str[len++] = ' ';
	}
	str[len] = 0;
	return (str);
}
int	execute()
{
	return (0);
}

int	execute_child(t_pars *pars, int infd)
{
	int			fd[2];
	pid_t		pid;
	char		*command;

	if (pars->out != STDOUT)
		pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup_input(infd, pars);
		dup_output(fd[0], pars);
		dup_error(pars);
		//smart_close(pars->in, pars->out, pars->err, infd);
		command = check_path(pars->cmd[0]);
		if (!command)
		{
			ft_putstr_fd(pars->cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		execve(command, &pars->cmd[0], NULL);
		ft_putendl_fd("execve failed", 2);
		exit(-1);
	}
	close(fd[1]);
	return (fd[0]);
}
