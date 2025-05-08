/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:27:49 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:40:40 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_swap(t_data *d, t_cmd c)
{
	int		tmp;

	if ((c == SA || c == SS) && d->a && ft_lstsize(d->a) >= 2)
	{
		tmp = ((t_sdata *)d->a->data)->val;
		((t_sdata *)d->a->data)->val = ((t_sdata *)d->a->next->data)->val;
		((t_sdata *)d->a->next->data)->val = tmp;
		ft_add_command(d, SA);
	}
	if ((c == SB || c == SS) && d->b && ft_lstsize(d->b) >= 2)
	{
		tmp = ((t_sdata *)d->b->data)->val;
		((t_sdata *)d->b->data)->val = ((t_sdata *)d->b->next->data)->val;
		((t_sdata *)d->b->next->data)->val = tmp;
		ft_add_command(d, SB);
	}
}

static void	ft_push(t_data *d, t_cmd c)
{
	t_list	*tmp;

	if (c == PA && d->b)
	{
		tmp = d->b;
		d->b = d->b->next;
		if (d->b)
			d->b->prev = NULL;
		ft_lstadd_front(&d->a, tmp);
		ft_add_command(d, PA);
	}
	if (c == PB && d->a)
	{
		tmp = d->a;
		d->a = d->a->next;
		if (d->a)
			d->a->prev = NULL;
		ft_lstadd_front(&d->b, tmp);
		ft_add_command(d, PB);
	}
}

static void	ft_rotate(t_data *d, t_cmd c)
{
	t_list	*tmp;

	if ((c == RA || c == RR) && d->a && ft_lstsize(d->a) >= 2)
	{
		tmp = d->a;
		d->a = d->a->next;
		d->a->prev = NULL;
		ft_lstadd_back(&d->a, tmp);
		ft_add_command(d, RA);
	}
	if ((c == RB || c == RR) && d->b && ft_lstsize(d->b) >= 2)
	{
		tmp = d->b;
		d->b = d->b->next;
		d->b->prev = NULL;
		ft_lstadd_back(&d->b, tmp);
		ft_add_command(d, RB);
	}
}

static void	ft_reverse_rotate(t_data *d, t_cmd c)
{
	t_list	*tmp;

	if ((c == RRA || c == RRR) && d->a && ft_lstsize(d->a) >= 2)
	{
		tmp = ft_lstlast(d->a);
		tmp->prev->next = NULL;
		ft_lstadd_front(&d->a, tmp);
		ft_add_command(d, RRA);
	}
	if ((c == RRB || c == RRR) && d->b && ft_lstsize(d->b) >= 2)
	{
		tmp = ft_lstlast(d->b);
		tmp->prev->next = NULL;
		ft_lstadd_front(&d->b, tmp);
		ft_add_command(d, RRB);
	}
}

void	ft_exec_command(t_data *d, t_cmd c)
{
	if (c == SA || c == SB || c == SS)
		ft_swap(d, c);
	if (c == PA || c == PB)
		ft_push(d, c);
	if (c == RA || c == RB || c == RR)
		ft_rotate(d, c);
	if (c == RRA || c == RRB || c == RRR)
		ft_reverse_rotate(d, c);
}
