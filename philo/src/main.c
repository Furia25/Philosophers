/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:04:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/09 17:30:22 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5)
		return (EXIT_FAILURE);
	parse_argv(argv, &table);
	return (EXIT_SUCCESS);
}

