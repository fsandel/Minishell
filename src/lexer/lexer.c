/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:28:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/06 15:47:48 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstprint(t_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		printf("LIST ITEM:%i:%s:\n", i, list->content);
		list = list->next;
		i++;
	}
}

void	token(t_list *lst, char *input, int start, int end)
{
	int		i;
	char	*tok;

	i = 0;
	tok = ft_calloc(sizeof(char), end - start + 1);
	while (start < end)
	{
		if (input[start] == '\\' && input[start + 1] == '\"'
		|| input[start] == '\\' && input[start + 1] == '\\')
			start++;
		else
			tok[i++] = input[start++];
	}
	tok[i] = '\0';
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
			{
			end++;
			break ;
			}
		else
			end++;
	}
	token(tokens, input, i, end);
	return(end); //PERHAPS 2 if error?
}

int	singlequotes(t_list *tokens, char *input, int i, int end)
{
	while (input[end] != '\'')
	{
		end++;
	}
	end++;
	token(tokens, input, i, end);
	return(end);
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

int	get_token(t_list **tokens, char *input, int i)
{
	int end;
	int c;

	c = i;
	end = i;
	if (input[end] == '\'' || input[end] == '\"') //quotes
		return(quotes(tokens, input, end));
	while(is_whitespace(input[end]) != TRUE && input[end] != '\0')
		end++;
/* 	printf("GET TOKEN:\n");
	while (c < end)
	{
		printf("%c", input[c]);
		c++;
	}
	printf("|\n"); */
	token(*tokens, input, i, end);
	return(end);
}

void	lexer(char	*input)
{
	t_list	*tokens;
	int		i;

	if (ft_strlen(input) != 0)
	{
		printf("----------------------------INPUT ------------------------\n");
		printf("%s\n", input);
		tokens = ft_lstnew(NULL);
		i = 0;
/* 		if (is_whitespace(input[i]) == FALSE)
			i = get_token(&tokens, input, i); */
		while (input[i] != '\0')
		{
			if(is_whitespace(input[i]) == FALSE)
				i = get_token(&tokens, input, i);
			else
				i++;
		}
		printf("---------------------INPUT NACH TOKENSPLIT----------------\n");
		ft_lstprint(tokens);
		tokens = lstspecial(tokens);
		printf("------------------------ \"< | >\" DONE  -------------------\n");
		ft_lstprint(tokens);
		ft_lstclear(&tokens, free);
	}
<<<<<<< Updated upstream
=======
	printf("---------------------INPUT NACH TOKENSPLIT----------------\n");
	ft_lstprint(tokens);
	tokens = lstspecial(tokens);
	printf("------------------------ \"< | >\" DONE  -------------------\n");
	ft_lstprint(tokens);
	//ft_lstclear(&tokens, free);
>>>>>>> Stashed changes
}
