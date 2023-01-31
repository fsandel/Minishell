/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:28:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/31 14:57:33 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstprint(t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		printf("list item %i:%s\n", i, list->content);
		list = list->next;
		i++;
	}
}

void	token(t_list *lst, char *input, int start, int end)
{
	int		i;
	char	*tok;

	i = 0;
	tok = ft_calloc(sizeof(char), end - start + 2);
	//printf("size of t: %i\n", end - start + 1);
	while (start <= end)
	{
		if (input[start] == '\\' && input[start + 1] == '\"'
		|| input[start] == '\\' && input[start + 1] == '\\')
			start++;
		else
			tok[i++] = input[start++];
	}
	tok[i] = '\0';
	//printf("tok:%s\n", tok);
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

int	doublequotes(t_list *tokens, char *input, int i, int end)
{
	while (input[end] != '\0')
	{
		//printf("end: %c at %i of %s\n", input[end], end, input);
		if (input[end] == '\"'
			&& input[end - 1] != '\\')
			break ;
		else
			end++;
	}
	token(tokens, input, i, end);
	return(end + 1); //PERHAPS 2 if error?
}

int	singlequotes(t_list *tokens, char *input, int i, int end)
{
	while (input[end] != '\0')
	{
		if (input[end] == '\'')
			break ;
		else
			end++;
	}
	token(tokens, input, i, end);
	return(end + 1);
}

int	quotes(t_list **tokens, char *input, int i)
{
	int end;
	
	end = i + 1;
	if (input[i] == '\"')
		return(doublequotes(*tokens, input, i, end));
	else
		return(singlequotes(*tokens, input, i, end));
}
/* int	quotes(t_list **tokens, char *input, int i)
{
	int end;
	
	end = i + 1;
	while (input[end] != input[i] 
		&& input[end] != '\0' 
		&& input[end - 1] != '\\')
	{
		printf("end: %c isnt: %c\n", input[end], input[i]);
		printf("end: %c isnt: %c\n", input[end], '\0');
		printf("end: %c isnt: %c\n", input[end - 1], '\\');
		printf("----------------------------\n");
		end++;
	}
	token(*tokens, input, i, end + 1);
	if (input[end + 1] == '\"')
		return(end + 2);
	else
		return (end + 1);
} */

int	get_token(t_list **tokens, char *input, int i)
{
	int end;

	end = i;
	if (input[end] == '\'' || input[end] == '\"') //quotes
		return(quotes(tokens, input, end));
	while(is_whitespace(input[end]) != TRUE && input[end] != '\0')
		end++;
	if(input[end] == '-')
		while(is_whitespace(input[end]) == FALSE && input[end] != '\0')
			end++;
	token(*tokens, input, i, end);
	return(end);
}

void	lexing(char	*input)
{
	t_list	*tokens;
	int		i;

	tokens = ft_lstnew(NULL);
	i = 0;
	if (is_whitespace(input[i]) == FALSE)
		i = get_token(&tokens, input, i);
	while (input[i] != '\0')
	{
		if(input[i] != '\0' && is_whitespace(input[i]) == FALSE)
			i = get_token(&tokens, input, i);
		else
			i++;
	}
	ft_lstprint(tokens);
	ft_lstclear(&tokens, free);
}
