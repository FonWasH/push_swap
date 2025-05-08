/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:57:22 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:40:52 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error(char *msg, t_data *d, t_args *a)
{
	if (a && a->tab)
		free(a->tab);
	if (a && a->free && a->args)
		ft_mfree((void **)a->args, a->size);
	if (d && d->a)
		ft_lstclear(&d->a, free);
	if (d && d->b)
		ft_lstclear(&d->b, free);
	if (d && d->c)
		ft_lstclear(&d->c, free);
	ft_putstr(msg, 2);
	exit(EXIT_FAILURE);
}
