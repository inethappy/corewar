/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 04:21:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 13:42:36 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			is_number(char *str)
{
	while (ft_iswhspace(*str))
		str++;
	while (ft_isdigit(*str))
		str++;
	while (ft_iswhspace(*str))
		str++;
	return (*str == '\0');
}

static int	find_num(t_list *lst, int num)
{
	t_champion	*champion;
	int			amount;

	amount = 0;
	while (lst)
	{
		champion = lst->content;
		if (champion->number == num)
			amount++;
		lst = lst->next;
	}
	return (amount);
}

void		choose_num(t_list *lst)
{
	static int	num = 1;
	t_champion	*champion;

	champion = lst->content;
	if (champion->number != 0)
	{
		error(find_num(g_game.players, champion->number) > 1, ERR_NBR_DUBL);
		return ;
	}
	while (find_num(g_game.players, num) && num <= MAX_PLAYERS)
		num++;
	if (num > MAX_PLAYERS)
		usage();
	champion->number = num;
}

void		set_value(int32_t addr, uint32_t value, size_t size)
{
	size_t	i;
	t_value	val;

	val.word = value;
	i = 0;
	while (i < size)
	{
		g_game.field[(addr + size - i - 1 + MEM_SIZE) % MEM_SIZE] = val.byte[i];
		i++;
	}
}

uint32_t	get_value(uint32_t addr, size_t size)
{
	size_t	i;
	t_value	value;

	value.word = 0;
	i = 0;
	while (i < size)
	{
		value.byte[i] =
				g_game.field[((addr + size - i - 1) + MEM_SIZE) % MEM_SIZE];
		i++;
	}
	if (size == 1)
		return ((int8_t)value.word);
	if (size == 2)
		return ((int16_t)value.word);
	return ((int32_t)value.word);
}
