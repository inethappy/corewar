/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:40:58 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 13:44:19 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "functions.h"

uint8_t		get_flag(char *str)
{
	if (ft_strequ(str, "-v") || ft_strequ(str, "-verbose"))
		return (VERBOSE);
	if (ft_strequ(str, "-dump"))
		return (DUMP32);
	if (ft_strequ(str, "-d"))
		return (DUMP64);
	if (ft_strequ(str, "-a"))
		return (AFF);
	if (ft_strequ(str, "-n"))
		return (CHAMPION_NUMBER);
	return (UNKNOWN);
}

int			handle_flag(int flag, char *av)
{
	int	champion_number;

	champion_number = 0;
	if (flag == UNKNOWN)
		usage();
	if (flag == AFF)
		g_flag |= FLAG_AFF;
	if (flag == VERBOSE)
	{
		error(!is_number(av), ERR_VERBOSE_ARG);
		g_flag |= FLAG_VERBOSE & (uint8_t)ft_atoi(av);
	}
	if (flag == DUMP32 || flag == DUMP64)
	{
		error(!is_number(av), ERR_DUMP_ARG);
		error((g_game.dump_period = ft_atoi(av)) < 0, ERR_DUMP_ARG);
		g_flag |= (flag == DUMP32) ? FLAG_DUMP32 : FLAG_DUMP64;
	}
	if (flag == CHAMPION_NUMBER)
	{
		error(!is_number(av), ERR_NBR_ARG);
		champion_number = ft_atoi(av);
		error(champion_number < 1 || champion_number > 4, ERR_NBR_PLAYER);
	}
	return (champion_number);
}

void		read_params(int ac, char **av)
{
	t_champion	champion;
	int			i;

	i = 0;
	ft_bzero(&champion, sizeof(t_champion));
	while (++i < ac)
	{
		if (*av[i] == '-')
		{
			champion.number = handle_flag(get_flag(av[i]), av[i + 1]);
			i++;
		}
		else
		{
			error(new_champion(av[i], &champion), ERR_INIT_PLAYER);
			ft_lstappend(&g_game.players,
					ft_lstnew(&champion, sizeof(t_champion)));
			ft_bzero(&champion, sizeof(t_champion));
		}
	}
	g_game.players_amount = ft_lstlen(g_game.players);
	g_id = g_game.players_amount;
	error(g_game.players_amount < 1 || g_game.players_amount > MAX_PLAYERS,
			ERR_PLAYERS_AMOUNT);
}

void		fill_field(t_list *player_lst)
{
	static uint16_t	id = 1;
	t_carriage		carriage;
	t_champion		*champion;

	champion = player_lst->content;
	ft_bzero(&carriage, sizeof(t_carriage));
	carriage.id = id++;
	carriage.reg[0] = -champion->number;
	carriage.pos = ((carriage.id - 1) *
			(MEM_SIZE / ft_lstlen(g_game.players))) % MEM_SIZE;
	ft_memcpy(g_game.field + carriage.pos,
			champion->code, champion->header->prog_size);
	ft_lstadd(&g_game.carriages, ft_lstnew(&carriage, sizeof(t_carriage)));
}

int			main(int ac, char **av)
{
	t_champion	*winer;

	if (ac < 2)
		usage();
	ft_bzero(&g_game, sizeof(t_game));
	g_game.check_period = CYCLE_TO_DIE;
	read_params(ac, av);
	ft_lstiter(g_game.players, choose_num);
	sort_champions();
	ft_printf("Introducing contestants...\n");
	ft_lstiter(g_game.players, log_champion);
	ft_bzero(g_game.field, MEM_SIZE);
	ft_lstiter(g_game.players, fill_field);
	winer = game_loop();
	log_winner(winer);
	return (0);
}
