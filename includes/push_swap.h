/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:01:45 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 05:54:09 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

/* Error Strings */
# define ERROR "Error\n"

/* Debug Strings */
# define DEBUG 0
# define ARG "\n[   DEBUGGER   ]\n\n--- Argument ---\n"
# define S_A "\n--- Stack  A ---\n"
# define S_B "\n--- Stack  B ---\n"
# define EMPTY "Empty"
# define CMD "\n--- Commands ---\n"
# define CMD_COUNT "\nCount:"
# define SORT "\n---  Sorted  ---\n"
# define OK "OK"
# define KO "KO"

/* Commands Enum */
typedef enum e_cmd
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	SKIP,
}	t_cmd;

/* Commands List Data */
typedef struct s_cdata
{
	t_cmd	cmd;
}			t_cdata;

/* Stack List Data */
typedef struct s_sdata
{
	int		val;
	size_t	index;
	size_t	cost;
	size_t	top;
	bool	rev;
	t_list	*target;
}			t_sdata;

/* Push Swap Data Structure */
typedef struct s_data
{
	t_list	*a;
	t_list	*b;
	t_list	*c;
}			t_data;

/* Args Structure */
typedef struct s_args
{
	char	**args;
	bool	free;
	int		*tab;
	size_t	size;
}			t_args;

/* Utils */
void		ft_clear_data(t_data *d);
void		ft_check_args(int ac, char **av, t_data *d);
bool		ft_isss(t_list *current, t_list *next);
bool		ft_isrr(t_list *current, t_list *next);
bool		ft_isrrr(t_list *current, t_list *next);
bool		ft_isskip(t_list *current, t_list *next);
bool		ft_issorted(t_data *d);
t_list		*ft_get_min(t_list *lst);
t_list		*ft_get_max(t_list *lst);
t_list		*ft_get_maxtarget(t_list *lst, int value);
t_list		*ft_get_mintarget(t_list *lst, int value);

/* Error */
void		ft_error(char *msg, t_data *d, t_args *a);

/* Debug */
void		ft_print_stacks(t_data *d);
void		ft_print_issorted(t_data *d);

/* Helper */
void		ft_print_commands(t_list **lst);
void		ft_add_command(t_data *d, t_cmd c);
void		ft_move_node_a(t_data *d, t_list *node, bool push);
void		ft_move_node_b(t_data *d, t_list *node, bool push);
void		ft_refresh_stack(t_list *lst);
void		ft_calcost_stack(t_list *lst,
				t_list *(*ft_find_target)(t_list *, int), t_list *target_lst);
t_list		*ft_get_cheapest_cost(t_list *lst);

/* Commands */
void		ft_exec_command(t_data *d, t_cmd c);

/* Sort */
void		ft_sort(t_data *d);
void		ft_quick_sort_a(t_data *d, size_t size);

#endif
