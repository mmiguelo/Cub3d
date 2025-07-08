/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:49:26 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/29 10:49:26 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to an integer: ASCII to integer
 * 
 * @param str A pointer to the string to be converted
 * @return Returns the converted integer value
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if ((str[i] == '+') || (str[i] == '-'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/* int	main(void)
{
	printf("empty parameter:");
	printf("\n%d\n", ft_atoi(""));
	printf("zero, positive and negative int:");
	printf("\n%d\n", ft_atoi("0"));
	printf("%d\n", ft_atoi("+1234   "));
	printf("%d\n", ft_atoi("-1234   "));
	printf("several signs in a row:");
	printf("\n%d\n", ft_atoi("--1234   "));
	printf("%d\n", ft_atoi("+-++-+-+-2147483647    "));
	printf("above int max:");
	printf("\n%d\n", ft_atoi("2147483648   "));
	printf("int max and int min:");
	printf("\n%d\n", ft_atoi("2147483647"));
	printf("%d\n", ft_atoi("-2147483648"));
	printf("tabs and newlines:");
	printf("\n%d\n", ft_atoi("    \t\t\t\n\n1234\t\t\n"));
} */