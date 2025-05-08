/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:16:47 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:51:02 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	main(int ac, char *av[])
{
	t_data	d;
	ssize_t	ret;

	if (ac > 1)
	{
		ft_check_args(ac, av, &d);
		ret = ft_get_next_cmd(&d);
		while (ret)
			ret = ft_get_next_cmd(&d);
		if (ret == -1)
		{
			ft_printf("%s\n", KO);
			ft_clear_data(&d);
			exit(EXIT_FAILURE);
		}
		if (ft_issorted(&d))
			ft_printf("%s\n", OK);
		else
			ft_printf("%s\n", KO);
		ft_clear_data(&d);
	}
	exit(EXIT_SUCCESS);
}
