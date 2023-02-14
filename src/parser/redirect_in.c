/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:19:04 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/14 14:56:59 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	replace(char *line, char **env, int fd);
void	expand(char *line, char **env, int fd);

t_list	*redirect_in(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
		if (!list->next->content)
			return(list);
	fd = open(list->next->content, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror(list->next->content);
		return(list->next);
	}
	if (pars->in > 2)
		close(pars->in);
	pars->in = fd;
	return(list->next);
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
	ft_putchar_fd('\n', fd);
}

char	*rm_quote(char *str)
{
	char	*ret;
	int	i;
	int	j;
	int	quote[3];
	//quote[0] == sgl quote
	//quote[1] == dbl quote
	//quote[2] == esc
	ft_bzero(quote, sizeof(int) * 3);
	
	j = 0;
	i = 0;
	ret = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		if (str[i] == '\\' && quote[0] == 0 && quote[2] == 0)
		{
			quote[2] = (quote[2] + 1) % 2;
			i++;
		}
		else if (str[i] == '\'' && quote[1] == 0)
		{
			quote[0] = (quote[0] + 1) % 2;
			quote[2] = 0;
			i++;
		}
		else if (str[i] == '\"' && quote[0] == 0 && quote[2] == 0)
		{
			quote[1] = (quote[1] + 1) % 2;
			i++;
		}
		else
		{
			ret[j++] = str[i++];
			quote[2] = 0;
		}
	}
	return (ret);
}
t_list	*here_doc(t_list *list, t_pars *pars)
{
	int		fd[2];
	char	*temp;
	char	*limiter;
	char	*limiter_no_quote;
	pid_t	pid;

	if (!(list->next || list->next->content))
	{
		ft_putendl_fd("here throw error and exit", 2);
		exit(258);
	}
	if (pipe(fd) < 0)
		exit(0);
	limiter_no_quote = rm_quote(list->next->content);
	while (1)
	{
		temp = readline("> ");
		if (temp == NULL)
			break ;
		if (!ft_strncmp(temp, limiter_no_quote, ft_strlen(limiter_no_quote) + 1))
			break ;
		if (ft_strchr(limiter, '\"') || ft_strchr(limiter, '\''))
			ft_putendl_fd(temp, fd[1]);
		else
			expand(temp, pars->env, fd[1]);
		free(temp);
	}
	free(limiter_no_quote);
	free(temp);
	close(fd[1]);
	pars->in = fd[0];
	//signal(SIGINT, signal_handler_interactive);
	return(list->next);
}
