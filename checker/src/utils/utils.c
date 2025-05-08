/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:27:07 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:50:55 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

ssize_t	ft_get_next_cmd(t_data *d)
{
	const char	*str[] = {
		"sa\n", "sb\n", "ss\n", "pa\n", "pb\n",
		"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"
	};
	char		*cmd;
	size_t		i;

	cmd = get_next_line(STDIN_FILENO);
	if (!cmd)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(cmd, (char *)str[i], ft_strlen(cmd) - 1))
		{
			ft_exec_command(d, (t_cmd)i);
			return (free(cmd), 1);
		}
		i++;
	}
	ft_printf("%s\n", KO);
	return (free(cmd), -1);
}
