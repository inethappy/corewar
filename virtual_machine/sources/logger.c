/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:42:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 01:42:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	log_champion(t_list *lst)
{
	t_champion	*champion;

	champion = lst->content;
	if (champion)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
					champion->number, champion->header->prog_size,
					champion->header->prog_name, champion->header->comment);
}

void	log_winner(t_champion *champion)
{
	if (!champion)
		return ;
	ft_printf("Contestant %d, \"%s\", has won !\n",
		champion->number, champion->header->prog_name);
}

void	log_field(void)
{
	int	pos;
	int	width;

	if (g_flag & (FLAG_DUMP32 | FLAG_DUMP64))
	{
		width = (g_flag & FLAG_DUMP32) ? 32 : 64;
		pos = 0;
		while (pos < MEM_SIZE)
		{
			if (pos % width == 0)
				ft_printf("%.4p : ", pos);
			ft_printf("%.2x ", g_game.field[pos]);
			if (++pos % width == 0)
				ft_printf("\n");
		}
		exit(0);
	}
}
