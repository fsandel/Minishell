/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:46 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/01 15:54:29 by pgorner          ###   ########.fr       */
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
void	ft_free(void **arg, char *loc);
void	ft_puttarr_fd(char **arr, int fd);
void	ft_putcube_fd(char ***cube, int fd);
//==============================================================================
//----------------------------FT_SPLIT_SPECIAL.c--------------------------------
//==============================================================================
char	**ft_split_special(char const *s, char c);
//==============================================================================
//-------------------------------SP_UTILS.c-------------------------------------
//==============================================================================
size_t	counter(char *content, char c);

#endif