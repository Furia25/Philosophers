/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:53 by val               #+#    #+#             */
/*   Updated: 2025/05/24 16:45:22 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	system_message(char *message, char *message2, char *message3);

void	warning_message(char *message, char *message2, char *message3)
{
	ft_putstr_fd("\033[33m", 2);
	ft_putstr_fd("Warning: ", 2);
	ft_putstr_fd("\033[0m", 2);
	system_message(message, message2, message3);
}

void	error_message(char *error, char *message, char *message2)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd("\033[0m", 2);
	system_message(error, message, message2);
}

static void	system_message(char *message, char *message2, char *message3)
{
	if (message)
		ft_putstr_fd(message, 2);
	if (message2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message2, 2);
	}
	if (message3)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message3, 2);
	}
	ft_putstr_fd("\n", 2);
}
