/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:47:40 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:40:46 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_print_stack(t_list *lst)
{
	t_list	*tmp;
	t_sdata	*data;

	if (!lst)
		ft_printf(EMPTY);
	tmp = lst;
	while (tmp)
	{
		data = (t_sdata *)tmp->data;
		ft_printf("% -12d", data->val);
		tmp = tmp->next;
	}
}

void	ft_print_stacks(t_data *d)
{
	ft_printf(S_A);
	ft_print_stack(d->a);
	ft_printf(S_B);
	ft_print_stack(d->b);
}

void	ft_print_issorted(t_data *d)
{
	ft_printf(SORT);
	if (ft_issorted(d))
		ft_printf(OK);
	else
		ft_printf(KO);
}
