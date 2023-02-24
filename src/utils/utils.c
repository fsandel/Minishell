/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:42 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/22 18:50:56 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_append(char *s1, char c)
{
	int		i;
	char	*ret;

	if (!c)
		return (s1);
	if (!s1)
		return (ret = ft_calloc(2, sizeof(char)), ret[0] = c, ret);
	i = 0;
	ret = ft_calloc(ft_strlen(s1) + 1 + 1, sizeof(char));
	ft_memcpy(ret, s1, ft_strlen(s1));
	ret[ft_strlen(s1)] = c;
	free(s1);
	return (ret);
}

int	is_whitespace(char c)
{
	if (c == ' ' | c == '\n' | c == '\t' | c == '\v' | c == '\f' | c == '\r')
		return (TRUE);
	else
		return (FALSE);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_err_print(char *str, char *s1, char *s2, char *s3)
{
	int			i;
	int			j;
	char const	*s[3] = {s1, s2, s3};

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '%' && !str[i + 1])
			return ;
		if (str[i] == '%' && str[i + 1] == 's' && s[j])
		{
			ft_putstr_fd((char *)s[j++], 2);
			i++;
		}
		else
			ft_putchar_fd(str[i], 2);
		i++;
	}
}

void	token(t_lx *lex, char *input, t_list *tokens)
{
	int		i;
	char	*token;

	i = 0;
	lex->te = lex->i;
	token = ft_calloc(sizeof(char), lex->te - lex->ts + 2);
	if (lex->ts == lex->i)
		token[i] = input[lex->i];
	else
		while (lex->ts <= lex->te)
			token[i++] = input[lex->ts++];
	token[i + 1] = '\0';
	lex->ts = lex->te + 1;
	if (tokens->content == NULL)
		tokens->content = token;
	else
		ft_lstadd_back(&tokens, ft_lstnew(token));
	tokens = tokens->next;
}
