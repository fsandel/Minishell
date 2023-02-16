/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:12:40 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/16 17:00:57 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token(char *str)
{
	int	i;
	char const	*list[] = {"|", "<", "<<", ">", ">>", NULL};
	i = 0;
	while (list[i])
	{
		if (ft_strncmp(str, list[i], ft_strlen(list[i])))
			return (1);
		i++;
	}
	return (0);
}

t_list	*append_out(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
		return (g_error = 258, pars->error = 1, NULL);
	}
	if (!list->next->content)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
		return (g_error = 258, pars->error = 1, NULL);
	}
	if (unexpected_token(list->next->content))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putendl_fd(list->next->content, 2);
		return (g_error = 258, pars->error = 1, NULL);
	}
	fd = open(list->next->content, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return(perror(list->next->content), g_error = 1, pars->error = 1, list->next);
	if (pars->out > 2)
		close(pars->out);
	pars->out = fd;
	return(list->next);
}

t_list	*redirect_in(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
		return (g_error = 258, pars->error = 1, NULL);
	}
	if (!list->next->content)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
		return (g_error = 258, pars->error = 1, NULL);
	}
	if (unexpected_token(list->next->content))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putendl_fd(list->next->content, 2);
		return (g_error = 258, pars->error = 1, NULL);
	}
	fd = open(list->next->content, O_RDONLY, 0644);
	if (fd < 0)
		return(perror(list->next->content), g_error = 1, pars->error = 1, list->next);
	if (pars->in > 2)
		close(pars->in);
	pars->in = fd;
	return (list->next);
}

t_list	*redirect_out(t_list *list, t_pars *pars)
{
	int	fd;

	if (!list->next)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
		pars->error = 1;
		g_error = 258;
		return (NULL);
	}
	if (!list->next->content)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'newline'", 2);
		pars->error = 1;
		g_error = 258;
		return (NULL);
	}
	if (unexpected_token(list->next->content))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putendl_fd(list->next->content, 2);
		return (g_error = 258, pars->error = 1, NULL);
	}
	fd = open(list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return(perror(list->next->content), g_error = 1, pars->error = 1, list->next);
	if (pars->out > 2)
		close(pars->out);
	pars->out = fd;
	return(list->next);
}
