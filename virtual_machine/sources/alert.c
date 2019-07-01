/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 04:19:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 14:25:41 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	error(int trigger, char *msg)
{
	if (trigger)
	{
		ft_dprintf(2, "ERROR: %s\n", msg);
		exit(1);
	}
}

void	usage(void)
{
	ft_printf("Usage : ./corewar [-dump N -n N -v N] <champion1.cor> <...>\n");
	ft_printf("\t\t-a\t: Prints output from \"aff\"\n");
	ft_printf("\t\t-dump N\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t\t-n N\t: Define champion number\n");
	ft_printf("\t\t-v N\t: Verbosity levels\n");
	ft_printf("\t\t\t0\t: Show only essentials\n");
	ft_printf("\t\t\t1\t: Show lives\n");
	ft_printf("\t\t\t2\t: Show cycles\n");
	ft_printf("\t\t\t4\t: Show operations (Params are NOT litteral ...)\n");
	ft_printf("\t\t\t8\t: Show deaths\n");
	ft_printf("\t\t\t16\t: Show PC movements (Except for jumps)\n");
	exit(0);
}
