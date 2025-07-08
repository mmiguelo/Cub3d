/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:47:05 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/29 12:02:55 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert_to_char(char *s, unsigned int number, long int len)
{
	while (number > 0)
	{
		s[len] = 48 + (number % 10);
		number = number / 10;
		len--;
	}
	return (s);
}

/**
 * @brief Gets the size of an int.
 * 
 * @param n integer to count.
 */
static long int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

/**
 * @brief Converts an int to ascii
 * 
 * @param n The integer to convert.
 * @return Converted 'n' to string.
 */
char	*ft_itoa(int n)
{
	char			*str;
	long int		length;
	unsigned int	number;

	length = ft_intlen(n);
	str = ft_calloc(length + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[length--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		number = n * -1;
	}
	else
		number = n;
	str = ft_convert_to_char(str, number, length);
	return (str);
}

/* int	main(void)
{
	printf("zero, positive and negative int:");
	printf("\n%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(+1234   ));
	printf("%s\n", ft_itoa(-1234   ));
	printf("several signs in a row:");
	printf("\n%s\n", ft_itoa(-+-1234   ));
	printf("%s\n", ft_itoa(+-+-+-+-+-2147483647    ));
	printf("int max and int min:");
	printf("\n%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));
} */