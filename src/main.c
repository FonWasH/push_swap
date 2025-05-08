/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:16:47 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:41:45 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char *av[])
{
	t_data	d;

	if (ac > 1)
	{
		ft_check_args(ac, av, &d);
		if (!ft_issorted(&d))
			ft_sort(&d);
		if (DEBUG)
		{
			ft_print_stacks(&d);
			ft_print_issorted(&d);
		}
		ft_print_commands(&d.c);
		ft_clear_data(&d);
	}
	exit(EXIT_SUCCESS);
}
