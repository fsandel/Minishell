/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:28:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/30 18:32:02 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstprint(t_list *list)
{
	while (list)
	{
		printf("list:%s\n", list->content);
		list = list->next;
	}
}

void	token(t_list *lst, char *input, int start, int end)
{
	int		i;
	char	*tok;

	i = 0;
	tok = ft_calloc(sizeof(char), end - start + 2);
	printf("size of t: %i\n", end - start + 1);
	while (start <= end)
		tok[i++] = input[start++];
	tok[i] = '\0';
	printf("tok:%s\n", tok);
	if (lst->content == NULL)
		lst->content = tok;
	else
		ft_lstadd_back(&lst, ft_lstnew(tok));
}

int	is_whitespace(char c)
{
	if (c == ' ' | c == '\n' | c == '\t' | c == '\v' | c == '\f' | c == '\r')
		return (TRUE);
	else
		return (FALSE);
}

int	quotes(t_list **tokens, char *input, int i)
{
	int end;
	
	end = i + 1;
	while (input[end] != input[i] && input[end] != '\0')
		end++;
	token(*tokens, input, i, end);
	return(end +1);
}

int	get_token(t_list **tokens, char *input, int i)
{
	int end;

	end = i;
	if (input[end] == '\'' || input[end] == '\"')
		return(quotes(tokens, input, end));
	while(is_whitespace(input[end]) != TRUE && input[end] != '\0')
		end++;
	printf("currently at %c\n", input[end]);
	if(input[end] == '-')
		while(is_whitespace(input[end]) == FALSE && input[end] != '\0')
			end++;
	//printf("2i is: %i, end is %i\n", i, end);
	token(*tokens, input, i, end);
	return(end);
}

void	lexing(char	*input)
{
	t_list	*tokens;
	int		i;

	tokens = ft_lstnew(NULL);
	i = 0;
	printf("%s\n", input);
	i = get_token(&tokens, input, i);
	while (input[i] != '\0')
	{
		if(input[i] != '\0' && is_whitespace(input[i]) == FALSE)
			i = get_token(&tokens, input, i);
		else
			i++;
	}
	ft_lstprint(tokens);
}



