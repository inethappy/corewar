/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:40:58 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 13:40:36 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "functions.h"

uint8_t		check_arg(uint32_t type, uint32_t arg)
{
	if (type == T_REG)
		return (arg > 0 || arg < REG_NUMBER) ? T_REG : 0;
	if (type == T_IND || type == T_DIR)
		return (type);
	return (0);
}

int32_t		get_arg(t_carriage *carriage, uint32_t type,
					uint32_t arg, int32_t divider)
{
	if (type == T_REG)
		return (carriage->reg[arg - 1]);
	if (type == T_IND)
	{
		return (get_value(
			(carriage->pos + (arg) % divider + MEM_SIZE) % MEM_SIZE, REG_SIZE));
	}
	if (type == T_DIR)
		return (arg);
	return (0);
}

int			get_argtype(t_carriage *carriage)
{
	t_argtype	argt;
	t_operation	*operation;
	uint16_t	i;

	operation = &carriage->operation;
	if (operation->codage == 0)
	{
		operation->argt[0] = T_DIR;
		return (1);
	}
	argt.cell = g_game.field[(carriage->pos + 1) % MEM_SIZE];
	operation->argt[0] = (argt.arg.a1 & 3U) ? 1U << (argt.arg.a1 - 1U) : 0;
	operation->argt[1] = (argt.arg.a2 & 3U) ? 1U << (argt.arg.a2 - 1U) : 0;
	operation->argt[2] = (argt.arg.a3 & 3U) ? 1U << (argt.arg.a3 - 1U) : 0;
	i = -1;
	while (++i < operation->argc)
	{
		if (!(operation->argt[i] & g_op[operation->code - 1].argt[i]))
			return (0);
	}
	return (1);
}

size_t		get_arglen(t_operation *operation)
{
	size_t	size;
	int		i;

	if (operation->codage == 0)
		return (operation->dir_size + 1);
	size = operation->codage + 1;
	i = -1;
	while (++i < operation->argc)
	{
		size += (operation->argt[i] == T_DIR) ? operation->dir_size : 0;
		size += (operation->argt[i] == T_REG) ? 1 : 0;
		size += (operation->argt[i] == T_IND) ? IND_SIZE : 0;
	}
	return (size);
}

void		get_argval(t_carriage *carriage)
{
	t_operation *operation;
	size_t		size;
	int			i;

	operation = &carriage->operation;
	size = operation->codage + 1;
	i = -1;
	while (++i < operation->argc)
	{
		operation->argv[i] = (operation->argt[i] == T_DIR)
			? get_value((carriage->pos + size) % MEM_SIZE, operation->dir_size)
			: 0;
		operation->argv[i] = (operation->argt[i] == T_REG)
			? get_value((carriage->pos + size) % MEM_SIZE, 1)
			: operation->argv[i];
		operation->argv[i] = (operation->argt[i] == T_IND)
			? get_value((carriage->pos + size) % MEM_SIZE, IND_SIZE)
			: operation->argv[i];
		size += (operation->argt[i] == T_DIR) ? operation->dir_size : 0;
		size += (operation->argt[i] == T_REG) ? 1 : 0;
		size += (operation->argt[i] == T_IND) ? IND_SIZE : 0;
	}
}
