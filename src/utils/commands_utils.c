/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:26:18 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:41:22 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	ft_isss(t_list *current, t_list *next)
{
	t_cmd	c;
	t_cmd	n;

	c = ((t_cdata *)current->data)->cmd;
	n = ((t_cdata *)next->data)->cmd;
	return ((c == SA && n == SB) || (c == SB && n == SA));
}

bool	ft_isrr(t_list *current, t_list *next)
{
	t_cmd	c;
	t_cmd	n;

	c = ((t_cdata *)current->data)->cmd;
	n = ((t_cdata *)next->data)->cmd;
	return ((c == RB && n == RA) || (c == RA && n == RB));
}

bool	ft_isrrr(t_list *current, t_list *next)
{
	t_cmd	c;
	t_cmd	n;

	c = ((t_cdata *)current->data)->cmd;
	n = ((t_cdata *)next->data)->cmd;
	return ((c == RRB && n == RRA) || (c == RRA && n == RRB));
}

bool	ft_isskip(t_list *current, t_list *next)
{
	t_cmd	c;
	t_cmd	n;

	c = ((t_cdata *)current->data)->cmd;
	n = ((t_cdata *)next->data)->cmd;
	return ((c == SA && n == SA) || (c == SB && n == SB)
		|| (c == PA && n == PB) || (c == PB && n == PA)
		|| (c == RA && n == RRA) || (c == RRA && n == RA)
		|| (c == RB && n == RRB) || (c == RRB && n == RB)
		|| (c == RR && n == RRR) || (c == RRR && n == RR)
		|| (c == SS && n == SS));
}
