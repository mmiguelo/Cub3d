/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:07:05 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/11/27 11:15:10 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_args(va_list args, const char specifier)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (specifier == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (specifier == 'u')
		return (ft_pututoa(va_arg(args, unsigned int)));
	if (specifier == 'x' || specifier == 'X')
		return (ft_puthex(va_arg(args, int), specifier));
	if (specifier == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
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
			count += print_args(args, str[++i]);
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}

/* int main()
{
    char c = 'k'; // %c
    char *str = NULL; // %s
    
    int nbr = -5;// %d // %i
	char *var; var = str;// %p
    unsigned int nbrr = 20;// %u
    int b= 0xffffffff;// %x // %X
    // %%
    int i;
	ft_printf("He%clo\n%s!\n%x\n%%", 'l', "World", -42);
    printf("\n\nPrintf replica:\n");
    i = ft_printf("| TEST TEXT |\n| Single Char: %c |\n| String: %s |\
	\n| Pointer Adress: %p |\n| Decimal: %d |\n| Integer %i |\
	\n| Unsign deci: %u |\n| HexLower: %x |\n| HexUpper: %X |\
	\n| Percentage sign: %% |\n", c, str, var, nbr, nbr, nbrr, b, b);
    printf("\nReturn Value: %d", i);
    ///////////////////////////////
    printf("\nPrintf original:\n");
    i = printf("| TEST TEXT |\n| Single Char: %c |\n| String: %s |\
	\n| Pointer Adress: %p |\n| Decimal: %d |\n| Integer %i |\
	\n| Unsign deci: %u |\n| HexLower: %x |\n| HexUpper: %X |\
	\n| Percentage sign: %% |\n", c, str, var, nbr, nbr, nbrr, b, b);
    printf("\nReturn Value: %d\n", i);
    return (0);
} */