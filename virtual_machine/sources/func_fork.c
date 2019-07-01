/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:27:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 13:40:58 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	func_fork(t_carriage *carriage)
{
	t_operation	*operation;
	t_carriage	*new;

	get_argval(carriage);
	operation = &carriage->operation;
	ft_lstadd(&g_game.carriages, ft_lstnew(carriage, sizeof(t_carriage)));
	new = g_game.carriages->content;
	ft_bzero(&new->operation, sizeof(t_operation));
	new->pos = ((carriage->pos + operation->argv[0] % IDX_MOD) + MEM_SIZE)
																	% MEM_SIZE;
	new->id = ++g_id;
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5i | fork %i (%i)\n",
					carriage->id, operation->argv[0], new->pos);
}

void	func_lfork(t_carriage *carriage)
{
	t_operation	*operation;
	t_carriage	*new;

	get_argval(carriage);
	operation = &carriage->operation;
	ft_lstadd(&g_game.carriages, ft_lstnew(carriage, sizeof(t_carriage)));
	new = g_game.carriages->content;
	ft_bzero(&new->operation, sizeof(t_operation));
	new->pos = (carriage->pos + operation->argv[0] + MEM_SIZE) % MEM_SIZE;
	new->id = ++g_id;
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5i | lfork %i (%i)\n",
				carriage->id, operation->argv[0], new->pos);
}
