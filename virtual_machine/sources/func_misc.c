/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 19:03:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 14:31:09 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	cmp_number(void const *champion_content, void const *sample_content)
{
	t_champion const *champion;
	t_champion const *sample;

	champion = champion_content;
	sample = sample_content;
	return (champion->number == sample->number);
}

void		func_live(t_carriage *carriage)
{
	t_operation	*operation;
	t_champion	sample;
	t_list		*survivor;

	get_argval(carriage);
	operation = &carriage->operation;
	carriage->live = g_game.cycle_counter;
	g_game.live_counter++;
	survivor = NULL;
	if (-operation->argv[0] > 0 && -operation->argv[0] <= g_game.players_amount)
	{
		sample.number = -operation->argv[0];
		survivor = ft_lstfind(g_game.players, &sample, cmp_number);
		g_game.survivor = (survivor->content)
				? survivor->content : g_game.survivor;
	}
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5i | live %i\n", carriage->id, operation->argv[0]);
	if (survivor == NULL)
		return ;
	if (g_flag & FLAG_VERBOSE_1)
		ft_printf("Player %d (%s) is said to be alive\n",
				-operation->argv[0], g_game.survivor->header->prog_name);
}

void		func_zjmp(t_carriage *carriage)
{
	t_operation	*operation;

	get_argval(carriage);
	operation = &carriage->operation;
	if (carriage->carry)
	{
		carriage->pos = (carriage->pos - get_arglen(operation)
			+ (operation->argv[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
		if (g_flag & FLAG_VERBOSE_4)
			ft_printf("P%5i | zjmp %i OK\n", carriage->id, operation->argv[0]);
		return ;
	}
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5i | zjmp %i FAILED\n", carriage->id, operation->argv[0]);
}

void		func_aff(t_carriage *carriage)
{
	t_operation	*operation;
	int32_t		*argv;

	get_argval(carriage);
	operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[0], operation->argv[0]) != T_REG)
		return ;
	if (g_flag & FLAG_AFF)
		ft_printf("%c\n", (char)(carriage->reg[argv[0] - 1] % 256));
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5d | aff r%d\n", carriage->id, argv[0] - 1);
}
