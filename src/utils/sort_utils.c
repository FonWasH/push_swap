/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:23:33 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:41:29 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	ft_issorted(t_data *d)
{
	t_list	*tmp;

	if (d->b)
		return (false);
	tmp = d->a;
	while (tmp->next)
	{
		if (((t_sdata *)tmp->data)->val > ((t_sdata *)tmp->next->data)->val)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

t_list	*ft_get_min(t_list *lst)
{
	t_list	*tmp;
	t_list	*min;

	tmp = lst;
	min = tmp;
	while (tmp)
	{
		if (((t_sdata *)tmp->data)->val < ((t_sdata *)min->data)->val)
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

t_list	*ft_get_max(t_list *lst)
{
	t_list	*tmp;
	t_list	*max;

	tmp = lst;
	max = tmp;
	while (tmp)
	{
		if (((t_sdata *)tmp->data)->val > ((t_sdata *)max->data)->val)
			max = tmp;
		tmp = tmp->next;
	}
	return (max);
}

t_list	*ft_get_maxtarget(t_list *lst, int value)
{
	int		val;
	t_list	*tmp;
	t_list	*target;

	target = NULL;
	tmp = lst;
	while (tmp)
	{
		val = ((t_sdata *)tmp->data)->val;
		if (val > value && (!target || val < ((t_sdata *)target->data)->val))
			target = tmp;
		tmp = tmp->next;
	}
	if (!target)
		target = ft_get_min(lst);
	return (target);
}

t_list	*ft_get_mintarget(t_list *lst, int value)
{
	int		val;
	t_list	*tmp;
	t_list	*target;

	target = NULL;
	tmp = lst;
	while (tmp)
	{
		val = ((t_sdata *)tmp->data)->val;
		if (val < value && (!target || val > ((t_sdata *)target->data)->val))
			target = tmp;
		tmp = tmp->next;
	}
	if (!target)
		target = ft_get_max(lst);
	return (target);
}
