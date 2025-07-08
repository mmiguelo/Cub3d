/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_pf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:53:27 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:53:30 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_putnbr_fd_pf(int n, int fd)
{
	int		length;
	char	*num;

	length = 0;
	num = ft_itoa(n);
	length = ft_putstr_fd_pf(num, fd);
	free(num);
	return (length);
}
