/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:52:24 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:52:27 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <stdarg.h> // variadic
# include <unistd.h> // write
# include <stdio.h> // test printf
# include <stdlib.h> //free malloc
# include "../libft.h"

int	ft_printf_fd(int fd, const char *str, ...);
int	print_args_fd(va_list args, const char specifier, int fd);
int	ft_puthex_fd(unsigned int n, char c, int fd);
int	ft_putptr_fd(void *n, int fd);
int	ft_pututoa_fd(unsigned int n, int fd);
int	ft_putstr_fd_pf(char *str, int fd);
int	ft_putnbr_fd_pf(int n, int fd);
int	ft_putchar_fd_pf(char c, int fd);

#endif