/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:42 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 13:21:38 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* ft_free = prozess wenn null freen wenn 1 nicht sodass nicht double free ist
* ggf argument mitgeben von wo gefreet wird sodass man weiß von woher was kommt
* argument dann zu void casten 
*/
void	ft_free(void **arg, char *loc)
{
	//(void)loc;
	if (*arg)
	{
		free(*arg);
		*arg = 0;
	}
	else
		ft_printf("Doublefree at %s\n", loc);
}

void	ft_puttarr_fd(char **arr, int fd)
{
	int	j;
	
	j = 0;
	while (arr[j])
		ft_putendl_fd(arr[j++], fd);
}

void	ft_putcube_fd(char ***cube, int fd)
{
	int	k;

	k = 0;
	while (cube[k])
	{
		ft_puttarr_fd(cube[k++], fd);
		ft_putchar_fd('\n', fd);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**copy_arr(char **arr)
{
	char	**ret;
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	ret = ft_calloc(array_size(arr) + 1, sizeof(char *));
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	array_size(char **arr)
{
	int	size;

	size = 0;
	while (arr && arr[size])
		size++;
	return (size);
}

char	**array_add_line(char **arr, char *nl)
{
	char	**ret;
	int		line;

	line = 0;
	ret = ft_calloc(array_size(arr) + 2, sizeof(char *));
	while (arr[line])
	{
		ret[line] = ft_strdup(arr[line]);
		line++;
	}
	ret[line++] = ft_strdup(nl);
	ret[line] = NULL;
	free_array(arr);
	return (ret);
}

char	**arr_del_line(char **arr, char *ln)
{
	int	line;
	char	**ret;
	int	ret_line;

	if (!ln)
		return (arr);
	ret_line = 0;
	line = 0;
	ret = ft_calloc(array_size(arr) + 1, sizeof(char *));
	while (arr[line])
	{
		if (!ft_strncmp(arr[line], ln, ft_strlen(ln)) && arr[line][ft_strlen(ln)] == '=')
			line++;
		else
			ret[ret_line++] = ft_strdup(arr[line++]);
	}
	ret[ret_line] = NULL;
	free_array(arr);
	return (ret);
}