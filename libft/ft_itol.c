/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:54:14 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/28 13:36:40 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	ft_len(long long n)
{
	long long	len;

	len = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_translate(char *str, long long n, long long len)
{
	long long	i;

	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		n = n * -1;
	}
	str[len--] = '\0';
	while (n > 9)
	{
		str[len--] = (n % 10) + 48;
		n = n / 10;
	}
	str[len] = (n % 10) + 48;
	return ;
}

char	*ft_itol(long long n)
{
	long long		len;
	char			*result;
	long long		i;

	i = n;
	len = ft_len(n);
	if (n == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	if (n < 0)
	{
		result = (char *)malloc(len * sizeof(char) + 2);
		if (!result)
			return (NULL);
		ft_translate(result, i, len + 1);
	}
	else
	{
		result = (char *)malloc(len * sizeof(char) + 1);
		if (!result)
			return (NULL);
		ft_translate(result, i, len);
	}
	return (result);
}
