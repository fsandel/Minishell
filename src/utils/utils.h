/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:46 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 20:35:10 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//				██╗  ██╗███████╗ █████╗ ██████╗ ███████╗██████╗
//				██║  ██║██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
//				███████║█████╗  ███████║██║  ██║█████╗  ██████╔╝
//				██╔══██║██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
//				██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
//				╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝

#ifndef UTILS_H
# define UTILS_H

//==============================================================================
//---------------------------------UTILS.c--------------------------------------
//==============================================================================
void    do_exit(int error);
int     is_whitespace(char c);
void	ft_free(void **arg, char *loc);

//==============================================================================
//----------------------------FT_SPLIT_SPECIAL.c--------------------------------
//==============================================================================
char	**ft_split_special(char const *s, char c);

//==============================================================================
//-------------------------------SP_UTILS.c-------------------------------------
//==============================================================================
size_t	counter(char *content, char c);

//==============================================================================
//--------------------------ARRAY_HANDLING>C------------------------------------
//==============================================================================
void	free_array(char **arr);
char	**copy_arr(char **arr);
int		array_size(char **arr);
char	**array_add_line(char **arr, char *nl);
char	**arr_del_line(char **arr, char *ln);

//==============================================================================
//----------------------------PRINT_UTILS.c-------------------------------------
//==============================================================================
void	ft_puttarr_fd(char **arr, int fd);
void	ft_putcube_fd(char ***cube, int fd);

#endif
