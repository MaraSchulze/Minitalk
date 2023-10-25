/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:25:07 by marschul          #+#    #+#             */
/*   Updated: 2023/10/25 20:31:53 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_strdup(const char *s)
{
	size_t	length;
	size_t	i;
	char	*str_dup;

	length = ft_strlen(s) + 1;
	str_dup = (char *) malloc(length);
	if (str_dup == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		str_dup[i] = s[i];
		i++;
	}
	return (str_dup);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*pointer;

	pointer = (unsigned char *) s;
	while (n > 0)
	{
		*pointer = (unsigned char) c;
		pointer++;
		n--;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

static int	dimension(long int n)
{
	int	dim;

	dim = 1;
	while (n >= 10)
	{
		n = n / 10;
		dim = dim * 10;
	}
	return (dim);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	char		str[13];
	char		*result;
	int			i;
	int			dim;

	nbr = (long int) n;
	ft_bzero(str, 13);
	i = 0;
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr = -nbr;
	}
	dim = dimension(nbr);
	while (dim != 0)
	{
		str[i++] = '0' + ((nbr / dim) % 10);
		dim = dim / 10;
	}
	str[i] = '\n';
	result = ft_strdup(str);
	return (result);
}
