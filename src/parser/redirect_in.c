/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:19:04 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 20:39:40 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	replace(char *line, char **env, int fd);
void	expand(char *line, char **env, int fd);

void	redirect_in(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return ;
	fd = open(list->next->content, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return ;
	}
	if (pars->in > 2)
		close(pars->in);
	ft_printf("Redirecting in\n");
	pars->in = fd;
}

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
	char *ret;
	int	i;
	int	esc;

	esc = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			i++;
			esc = (esc + 1) % 2;
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			i += 2;
			ft_putstr_fd("PID", fd);
			esc = 0;
		}
		else if (line[i] == '$' && !esc && line[i + 1] && line[i + 1] != '$' && line[i + 1] != '\n')
		{
			i += replace(&line[i + 1], env, fd);
			esc = 0;
		}
		else
		{
			esc = 0;
			ft_putchar_fd(line[i++], fd);
		}
	}
}

char	*rm_quote(char *str)
{
	char	*ret;
	int	i;

	i = 0;
	ret = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			ret[i] = str[i];
		i++;
	}
	return (ret);
}
void	here_doc(t_list *list, t_pars *pars)
{
	int		fd[2];
	char	*temp;
	char	*limiter;
	char	*limiter_no_quote;
	
	if (!(list->next || list->next->content))
	{
		ft_putendl_fd("here throw error and exit", 2);
		exit(258);
	}
	if (pipe(fd) < 0)
		exit(0);
	limiter = ft_strjoin(list->next->content, "\n");
	limiter_no_quote = rm_quote(limiter);
	while (1)
	{
		temp = get_next_line(STDIN);
		if (temp == NULL)
			break ;
		if (!ft_strncmp(temp, limiter_no_quote, ft_strlen(limiter_no_quote)))
			break ;
		if (ft_strchr(limiter, '\"') || ft_strchr(limiter, '\''))
			ft_putstr_fd(temp, fd[1]);
		else
			expand(temp, pars->env, fd[1]);
		free(temp);
	}
	free(limiter);
	free(temp);
	close(fd[1]);
	pars->in = fd[0];
}
