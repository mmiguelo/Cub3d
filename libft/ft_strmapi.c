/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:47:37 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/10/30 16:30:02 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function f to each character of the string s.
 * 
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return The string created from the successive applications
of ’f’.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int				i;
	char						*str;
	unsigned int				length;

	length = ft_strlen(s);
	if (!s || !f)
		return (NULL);
	str = ft_calloc(length + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < length)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* static char	ft_chardown(unsigned int i, char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
int	main(void)
{
	char	str[] = "TEST IN THIS";
	char	*new_str;
	
	printf("original string: %s\n", str);
	new_str = ft_strmapi(str, ft_chardown);
	printf("Modified string: %s\n", new_str);
	return(0);
} */