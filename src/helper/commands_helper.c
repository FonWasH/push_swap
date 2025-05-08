/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:40:00 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:40:59 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_check_command(t_list **lst, t_list *c, t_list *n)
{
	if (ft_isss(c, n))
	{
		((t_cdata *)c->data)->cmd = SS;
		ft_lstdelnode(lst, n);
	}
	else if (ft_isrr(c, n))
	{
		((t_cdata *)c->data)->cmd = RR;
		ft_lstdelnode(lst, n);
	}
	else if (ft_isrrr(c, n))
	{
		((t_cdata *)c->data)->cmd = RRR;
		ft_lstdelnode(lst, n);
	}
}

static void	ft_clean_removable(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && ft_isskip(tmp, tmp->next))
		{
			ft_lstdelnode(lst, tmp->next);
			tmp = ft_lstdelnode(lst, tmp);
		}
		else
			tmp = tmp->next;
	}
}

static void	ft_clean_commands(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	ft_clean_removable(lst);
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		while (next
			&& (((t_cdata *)tmp->data)->cmd == ((t_cdata *)next->data)->cmd))
			next = next->next;
		if (next)
			ft_check_command(lst, tmp, next);
		tmp = tmp->next;
	}
	ft_clean_removable(lst);
}

void	ft_print_commands(t_list **lst)
{
	const char	*str[] = {
		"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"
	};
	t_list		*tmp;
	size_t		count;

	if (DEBUG)
		ft_printf(CMD);
	ft_clean_commands(lst);
	tmp = *lst;
	count = 0;
	while (tmp)
	{
		if (DEBUG)
		{
			ft_printf("%-4s", (char *)str[((t_cdata *)tmp->data)->cmd]);
			count++;
		}
		else
			ft_printf("%s\n", (char *)str[((t_cdata *)tmp->data)->cmd]);
		tmp = tmp->next;
	}
	if (DEBUG)
		ft_printf("%s %zu\n\n", CMD_COUNT, count);
}

void	ft_add_command(t_data *d, t_cmd c)
{
	t_list	*new;
	t_cdata	*data;

	data = (t_cdata *)malloc(sizeof(t_cdata));
	if (!data)
		ft_error(ERROR, d, NULL);
	data->cmd = c;
	new = ft_lstnew(data);
	if (!new)
		ft_error(ERROR, d, NULL);
	ft_lstadd_back(&d->c, new);
}
