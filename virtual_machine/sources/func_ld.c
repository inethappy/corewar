/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:25:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 14:33:14 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	func_ld(t_carriage *carriage)
{
	t_operation	*operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	argv[0] = get_arg(carriage, operation->argt[0], argv[0], IDX_MOD);
	if (check_arg(operation->argt[0], argv[0]) & (T_DIR | T_IND))
	{
		carriage->reg[argv[1] - 1] = argv[0];
		carriage->carry = (carriage->reg[argv[1] - 1]) ? 0 : 1;
		if (g_flag & FLAG_VERBOSE_4)
			ft_printf("P%5d | ld %i r%i\n", carriage->id, argv[0], argv[1]);
	}
}

void	func_lld(t_carriage *carriage)
{
	t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[0], argv[0]) & (T_DIR | T_IND))
	{
		carriage->reg[argv[1] - 1] = get_arg(carriage,
									operation->argt[0], argv[0], MEM_SIZE);
		carriage->carry = (carriage->reg[argv[1] - 1]) ? 0 : 1;
		if (g_flag & FLAG_VERBOSE_4)
			ft_printf("P%5i | lld %i r%i\n", carriage->id, argv[0], argv[1]);
	}
}

void	func_ldi(t_carriage *carriage)
{
	t_operation	*operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (!check_arg(operation->argt[0], argv[0]) ||
		!(check_arg(operation->argt[1], argv[1]) & (T_DIR | T_REG)) ||
		(check_arg(operation->argt[2], argv[2]) != T_REG))
		return ;
	argv[0] = get_arg(carriage, operation->argt[0], argv[0], IDX_MOD);
	argv[1] = get_arg(carriage, operation->argt[1], argv[1], IDX_MOD);
	carriage->reg[argv[2] - 1] = get_value((carriage->pos +
			(argv[0] + argv[1]) % IDX_MOD + MEM_SIZE) % MEM_SIZE, REG_SIZE);
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5i | ldi %i %i r%i\n"
			"      | -> load from %i + %i = %i (with pc and mod %i\n)",
			carriage->id, argv[0], argv[1], argv[2], argv[0], argv[1],
			argv[0] + argv[1], carriage->pos + (argv[0] + argv[1]) % IDX_MOD);
}

void	func_lldi(t_carriage *carriage)
{
	t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (!check_arg(operation->argt[0], argv[0]) ||
		!(check_arg(operation->argt[1], argv[1]) & (T_DIR | T_REG)) ||
		(check_arg(operation->argt[2], argv[2]) != T_REG))
		return ;
	argv[0] = get_arg(carriage, operation->argt[0], argv[0], MEM_SIZE);
	argv[1] = get_arg(carriage, operation->argt[1], argv[1], MEM_SIZE);
	carriage->reg[argv[2] - 1] = get_value((carriage->pos +
						(argv[0] + argv[1]) + MEM_SIZE) % MEM_SIZE, REG_SIZE);
	carriage->carry = (carriage->reg[argv[2] - 1]) ? 0 : 1;
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5i | lldi %i %i r%i\n"
			"       | -> load from %i + %i = %i (with pc %i\n)",
			carriage->id, argv[0], argv[1], argv[2], argv[0], argv[1],
			argv[0] + argv[1], carriage->pos + (argv[0] + argv[1]));
}
