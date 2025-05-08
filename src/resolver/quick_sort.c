/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 04:17:28 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:41:10 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*ft_lst_to_tab(t_list *lst, size_t size)
{
	t_list	*tmp;
	int		*tab;
	size_t	i;

	tmp = lst;
	tab = malloc(sizeof(int) * size);
	if (!tab)
		return (NULL);
	i = 0;
	while (tmp && i < size)
	{
		tab[i] = ((t_sdata *)tmp->data)->val;
		tmp = tmp->next;
		i++;
	}
	return (tab);
}

static void	ft_sort_tab(int *tab, size_t size)
{
	size_t	i;
	size_t	j;
	int		tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static double	ft_get_median(t_data *d, t_list *lst, size_t size)
{
	int		*tab;
	double	median;

	if (size == 1)
		return (((t_sdata *)lst->data)->val);
	tab = ft_lst_to_tab(lst, size);
	if (!tab)
		ft_error(ERROR, d, NULL);
	ft_sort_tab(tab, size);
	if (size % 2 == 0)
		median = (double)(tab[size / 2] + tab[(size / 2) - 1]) / 2.0;
	else
		median = tab[size / 2];
	free(tab);
	return (median);
}

void	ft_quick_sort_a(t_data *d, size_t size)
{
	double	pivot;
	size_t	count;
	size_t	i;

	if (size <= 3)
		return ;
	count = 0;
	i = 0;
	pivot = ft_get_median(d, d->a, size);
	while ((i + count) < size)
	{
		if ((double)((t_sdata *)d->a->data)->val < pivot)
		{
			ft_exec_command(d, PB);
			count++;
		}
		else
		{
			ft_exec_command(d, RA);
			i++;
		}
	}
	ft_quick_sort_a(d, size - count);
}
