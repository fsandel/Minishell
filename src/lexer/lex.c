/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:28:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/30 17:20:20 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token(t_list **lst, char *input, int start, int end)
{
	int		i;
	char	*tok;

	i = 0;
	tok = ft_calloc(sizeof(char), end - start + 2);
	while (start <= end)
	{
		input[start++] = tok[i++];
	}
	tok[i] = '\0';
	ft_lstadd_back(lst, ft_lstnew(tok));
}

int	is_whitespace(char c)
{
	if (c == ' ' | c == '\n' | c == '\t' | c == '\v' | c == '\f' | c == '\r')
		return (FALSE);
	else
		return (TRUE);
}

int	get_token(t_list **tokens, char *input, int i)
{
	int end;

	while(is_whitespace(input[i]) == FALSE)
		i++;
	end = i;
	//token(tokens, input, i, end);
	printf("i is: %i\n", i);
	return(end);
}

void	lexing(char	*input)
{
	t_list	**tokens;
	int		i;

	printf("%s\n", input);
	while (input[i] != '\0')
	{
		if(input[i] != '\0' && is_whitespace(input[i]) == FALSE)
			i = get_token(tokens, input, i);
		else
			i++;
	}
}



