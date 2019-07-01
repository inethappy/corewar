/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 02:46:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 14:30:56 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "functions.h"

static int	set_function(t_carriage *carriage)
{
	if (g_game.field[carriage->pos] > 0 && g_game.field[carriage->pos] <= 16)
	{
		ft_memcpy(&carriage->operation, &g_op[g_game.field[carriage->pos] - 1],
			sizeof(t_operation));
		return (0);
	}
	ft_bzero(&carriage->operation, sizeof(t_operation));
	return (1);
}

void		exec_function(t_list *lst)
{
	t_carriage	*carriage;

	carriage = lst->content;
	if (carriage->operation.period > 0)
		carriage->operation.period--;
	else if (carriage->operation.code == 0)
	{
		if (set_function(carriage))
		{
			carriage->pos = (carriage->pos + 1) % MEM_SIZE;
			return ;
		}
		carriage->operation.period--;
	}
	if (carriage->operation.period > 0)
		return ;
	if (get_argtype(carriage))
		carriage->operation.function(carriage);
	carriage->pos = (carriage->pos +
					get_arglen(&carriage->operation) + MEM_SIZE) % MEM_SIZE;
	carriage->operation.code = 0;
}
