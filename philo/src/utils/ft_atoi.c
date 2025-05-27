/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:27:07 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/26 22:14:46 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isspace(char c)
{
	if (c == '\n' || c == ' ' || c == '	' || c == '\f')
		return (1);
	return (c == '\r' || c == '\t' || c == '\v');
}

int	ft_atoi(const char *nptr)
{
	int					index;
	int					sign;
	unsigned long long	result;

	if (!nptr)
		return (0);
	index = 0;
	result = 0;
	sign = 1;
	while (nptr[index] && ft_isspace(nptr[index]))
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
		return (0);
	while (nptr[index] && nptr[index] >= '0' && nptr[index] <= '9')
	{
		result = result * 10 + (nptr[index] - '0');
		index++;
	}
	if (result > INT_MAX)
		return (0);
	return (result * sign);
}
