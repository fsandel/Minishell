/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:33:04 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/29 12:44:24 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define DEBUG_NUM(num)\
{\
	ft_putstr_fd(#num, 2);\
	ft_putstr_fd(": ", 2);\
	ft_putnbr_fd(num, 2);\
	ft_putchar_fd('\n', 2);\
}

# define DEBUG_STR(str)\
{\
	ft_putstr_fd(#str, 2);\
	ft_putstr_fd(": ", 2);\
	ft_putstr_fd(str, 2);\
	ft_putchar_fd('\n', 2);\
}
#endif