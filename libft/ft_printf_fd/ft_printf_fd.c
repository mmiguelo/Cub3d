/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:52:13 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:52:15 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	print_args_fd(va_list args, const char specifier, int fd)
{
	if (specifier == 'c')
		return (ft_putchar_fd_pf(va_arg(args, int), fd));
	if (specifier == 's')
		return (ft_putstr_fd_pf(va_arg(args, char *), fd));
	if (specifier == 'p')
		return (ft_putptr_fd(va_arg(args, void *), fd));
	if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd_pf(va_arg(args, int), fd));
	if (specifier == 'u')
		return (ft_pututoa_fd(va_arg(args, unsigned int), fd));
	if (specifier == 'x' || specifier == 'X')
		return (ft_puthex_fd(va_arg(args, int), specifier, fd));
	if (specifier == '%')
		return (ft_putchar_fd_pf('%', fd));
	return (0);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
			count += print_args_fd(args, str[++i], fd);
		else
			count += ft_putchar_fd_pf(str[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
