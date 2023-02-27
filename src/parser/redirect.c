/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:12:40 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/25 18:29:36 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token(char *str)
{
	int			i;
	char const	*list[] = {"|", "<", "<<", ">", ">>", NULL};

	i = 0;
	while (list[i])
	{
		if (!ft_strncmp(str, list[i], ft_strlen(list[i])))
			return (1);
		i++;
	}
	return (0);
}

char	*expand_string(char **env, char *str)
{
	t_pars	**expand;
	char	*exp;

	expand = ft_calloc(1, sizeof(t_pars *));
	expand[0] = setup_single_pars(env, NULL);
	expand[0]->cmd = ft_calloc(2, sizeof(char *));
	expand[0]->cmd[0] = ft_strdup(str);
	expand[0]->cmd[1] = NULL;
	expand[0]->amount = 1;
	expand[0]->index = 0;
	expand[0]->total_cmd = 1;
	expand = expander(expand);
	exp = ft_strdup(expand[0]->cmd[0]);
	free_struct(expand);
	return (exp);
}

t_list	*append_out(t_list *list, t_pars *pars)
{
	int		fd;
	char	*exp;

	if (!list->next)
		return (ft_putendl_fd("minishell: syntax error near unexpected token \
'newline'", 2), g_error = 258, pars->error = 1, NULL);
	if (!list->next->content)
		return (ft_putendl_fd("minishell: syntax error near unexpected token \
'newline'", 2), g_error = 258, pars->error = 1, NULL);
	if (unexpected_token(list->next->content))
		return (ft_putstr_fd("minishell: syntax error near unexpected token ",
				2), ft_putendl_fd(list->next->content, 2), g_error = 258,
			pars->error = 1, NULL);
	exp = expand_string(pars->env, list->next->content);
	if (!ft_strncmp(exp, "", 2))
		return (ft_err_print("minishell: %s: ambigious redirect",
				list->next->content, NULL, NULL), g_error = 1, pars->error = 1,
			free(exp), list->next);
	fd = open(exp, O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (free(exp), perror(exp), g_error = 1, pars->error = 1,
			list->next);
	if (pars->out > 2)
		close(pars->out);
	pars->out = fd;
	return (free(exp), list->next);
}

t_list	*redirect_in(t_list *list, t_pars *pars)
{
	int		fd;
	char	*exp;

	if (!list->next)
		return (ft_putendl_fd("minishell: syntax error near unexpected token \
'newline'", 2), g_error = 258, pars->error = 1, NULL);
	if (!list->next->content)
		return (ft_putendl_fd("minishell: syntax error near unexpected token \
'newline'", 2), g_error = 258, pars->error = 1, NULL);
	if (unexpected_token(list->next->content))
		return (ft_putstr_fd("minishell: syntax error near unexpected token ",
				2), ft_putendl_fd(list->next->content, 2), g_error = 258,
			pars->error = 1, NULL);
	exp = expand_string(pars->env, list->next->content);
	if (!ft_strncmp(exp, "", 2))
		return (ft_err_print("minishell: %s: ambigious redirect",
				list->next->content, NULL, NULL), g_error = 1, pars->error = 1,
			free(exp), list->next);
	fd = open(exp, O_RDONLY, 0644);
	if (fd < 0)
		return (free(exp), perror(exp), g_error = 1,
			pars->error = 1, list->next);
	if (pars->in > 2)
		close(pars->in);
	pars->in = fd;
	return (free(exp), list->next);
}

t_list	*redirect_out(t_list *list, t_pars *pars)
{
	int		fd;
	char	*exp;

	if (!list->next)
		return (ft_putendl_fd("minishell: syntax error near unexpected token \
'newline'", 2), g_error = 258, pars->error = 1, NULL);
	if (!list->next->content)
		return (ft_putendl_fd("minishell: syntax error near unexpected token \
'newline'", 2), g_error = 258, pars->error = 1, NULL);
	if (unexpected_token(list->next->content))
		return (ft_putstr_fd("minishell: syntax error near unexpected token ",
				2), ft_putendl_fd(list->next->content, 2), g_error = 258,
			pars->error = 1, NULL);
	exp = expand_string(pars->env, list->next->content);
	if (!ft_strncmp(exp, "", 2))
		return (ft_err_print("minishell: %s: ambigious redirect",
				list->next->content, NULL, NULL), g_error = 1, pars->error = 1,
			free(exp), list->next);
	fd = open(exp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(exp), perror(exp), g_error = 1, pars->error = 1,
			list->next);
	if (pars->out > 2)
		close(pars->out);
	pars->out = fd;
	return (free(exp), list->next);
}
