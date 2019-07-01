/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:13:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 13:41:28 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	func_add(t_carriage *carriage)
{
	t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[0], argv[0]) != T_REG ||
		check_arg(operation->argt[1], argv[1]) != T_REG ||
		check_arg(operation->argt[2], argv[2]) != T_REG)
		return ;
	carriage->reg[argv[2] - 1] =
			carriage->reg[argv[0] - 1] + carriage->reg[argv[1] - 1];
	carriage->carry = (carriage->reg[argv[2] - 1]) ? 0 : 1;
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5d | add r%i r%i r%i\n",
				carriage->id, argv[0], argv[1], argv[2]);
}

void	func_sub(t_carriage *carriage)
{
	t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[0], argv[0]) != T_REG ||
		check_arg(operation->argt[1], argv[1]) != T_REG ||
		check_arg(operation->argt[2], argv[2]) != T_REG)
		return ;
	carriage->reg[argv[2] - 1] =
			carriage->reg[argv[0] - 1] - carriage->reg[argv[1] - 1];
	carriage->carry = (carriage->reg[argv[2] - 1]) ? 0 : 1;
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5d | add r%i r%i r%i\n",
			carriage->id, argv[0], argv[1], argv[2]);
}

void	func_and(t_carriage *carriage)
{
	t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[2], argv[2]) != T_REG
		|| !check_arg(operation->argt[0], argv[0])
		|| !check_arg(operation->argt[1], argv[1]))
		return ;
	argv[0] = get_arg(carriage, operation->argt[0], argv[0], IDX_MOD);
	argv[1] = get_arg(carriage, operation->argt[1], argv[1], IDX_MOD);
	carriage->reg[argv[2] - 1] = (uint32_t)argv[0] & (uint32_t)argv[1];
	carriage->carry = (carriage->reg[argv[2] - 1]) ? 0 : 1;
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5d | and %i %i r%i\n",
			carriage->id, argv[0], argv[1], argv[2]);
}

void	func_or(t_carriage *carriage)
{
	t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[2], argv[2]) != T_REG
		|| !check_arg(operation->argt[0], argv[0])
		|| !check_arg(operation->argt[1], argv[1]))
		return ;
	argv[0] = get_arg(carriage, operation->argt[0], argv[0], IDX_MOD);
	argv[1] = get_arg(carriage, operation->argt[1], argv[1], IDX_MOD);
	carriage->reg[argv[2] - 1] = (uint32_t)argv[0] | (uint32_t)argv[1];
	carriage->carry = (carriage->reg[argv[2] - 1]) ? 0 : 1;
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5d | or %i %i r%i\n",
				carriage->id, argv[0], argv[1], argv[2]);
}

void	func_xor(t_carriage *carriage)
{
	t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[2], argv[2]) != T_REG
		|| !check_arg(operation->argt[0], argv[0])
		|| !check_arg(operation->argt[1], argv[1]))
		return ;
	argv[0] = get_arg(carriage, operation->argt[0], argv[0], IDX_MOD);
	argv[1] = get_arg(carriage, operation->argt[1], argv[1], IDX_MOD);
	carriage->reg[argv[2] - 1] = (uint32_t)argv[0] ^ (uint32_t)argv[1];
	carriage->carry = (carriage->reg[argv[2] - 1]) ? 0 : 1;
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5d | xor %i %i r%i\n",
				carriage->id, argv[0], argv[1], argv[2]);
}
