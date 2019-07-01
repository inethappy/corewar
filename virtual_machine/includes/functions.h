/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:42:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 01:42:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <vm.h>

void	func_live(t_carriage *carriage);
void	func_zjmp(t_carriage *carriage);
void	func_aff(t_carriage *carriage);

void	func_ld(t_carriage *carriage);
void	func_lld(t_carriage *carriage);
void	func_ldi(t_carriage *carriage);
void	func_lldi(t_carriage *carriage);

void	func_st(t_carriage *carriage);
void	func_sti(t_carriage *carriage);

void	func_add(t_carriage *carriage);
void	func_sub(t_carriage *carriage);
void	func_and(t_carriage *carriage);
void	func_or(t_carriage *carriage);
void	func_xor(t_carriage *carriage);

void	func_fork(t_carriage *carriage);
void	func_lfork(t_carriage *carriage);

static const t_operation	g_op[16] =
{
	{
		.name = "live",
		.code = 0x01,
		.argc = 1,
		.argv = {0, 0, 0},
		.argt = {T_DIR, 0, 0},
		.function = func_live,
		.period = 10,
		.codage = 0,
		.dir_size = DIR_SIZE
	},
	{
		.name = "ld",
		.code = 0x02,
		.argc = 2,
		.argv = {0, 0, 0},
		.argt = {T_DIR | T_IND, T_REG, 0},
		.function = func_ld,
		.period = 5,
		.codage = 1,
		.dir_size = DIR_SIZE
	},
	{
		.name = "st",
		.code = 0x03,
		.argc = 2,
		.argv = {0, 0, 0},
		.argt = {T_REG, T_REG | T_IND, 0},
		.function = func_st,
		.period = 5,
		.codage = 1,
		.dir_size = DIR_SIZE
	},
	{
		.name = "add",
		.code = 0x04,
		.argc = 3,
		.argv = {0, 0, 0},
		.argt = {T_REG, T_REG, T_REG},
		.function = func_add,
		.period = 10,
		.codage = 1,
		.dir_size = DIR_SIZE
	},
	{
		.name = "sub",
		.code = 0x05,
		.argc = 3,
		.argv = {0, 0, 0},
		.argt = {T_REG, T_REG, T_REG},
		.function = func_sub,
		.period = 10,
		.codage = 1,
		.dir_size = DIR_SIZE
	},
	{
		.name = "and",
		.code = 0x06,
		.argc = 3,
		.argv = {0, 0, 0},
		.argt = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_and,
		.period = 6,
		.codage = 1,
		.dir_size = DIR_SIZE
	},
	{
		.name = "or",
		.code = 0x07,
		.argc = 3,
		.argv = {0, 0, 0},
		.argt = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_or,
		.period = 6,
		.codage = 1,
		.dir_size = DIR_SIZE
	},
	{
		.name = "xor",
		.code = 0x08,
		.argc = 3,
		.argv = {0, 0, 0},
		.argt = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_xor,
		.period = 6,
		.codage = 1,
		.dir_size = DIR_SIZE
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.argc = 1,
		.argv = {0, 0, 0},
		.argt = {T_DIR, 0, 0},
		.function = func_zjmp,
		.period = 20,
		.codage = 0,
		.dir_size = IND_SIZE
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.argc = 3,
		.argv = {0, 0, 0},
		.argt = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.function = func_ldi,
		.period = 25,
		.codage = 1,
		.dir_size = IND_SIZE
	},
	{
		.name = "sti",
		.code = 0x0B,
		.argc = 3,
		.argv = {0, 0, 0},
		.argt = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.function = func_sti,
		.period = 25,
		.codage = 1,
		.dir_size = IND_SIZE
	},
	{
		.name = "fork",
		.code = 0x0C,
		.argc = 1,
		.argv = {0, 0, 0},
		.argt = {T_DIR, 0, 0},
		.function = func_fork,
		.period = 800,
		.codage = 0,
		.dir_size = IND_SIZE
	},
	{
		.name = "lld",
		.code = 0x0D,
		.argc = 2,
		.argv = {0, 0, 0},
		.argt = {T_DIR | T_IND, T_REG, 0},
		.function = func_lld,
		.period = 10,
		.codage = 1,
		.dir_size = DIR_SIZE
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.argc = 3,
		.argv = {0, 0, 0},
		.argt = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.function = func_lldi,
		.period = 50,
		.codage = 1,
		.dir_size = IND_SIZE
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.argc = 1,
		.argv = {0, 0, 0},
		.argt = {T_DIR, 0, 0},
		.function = func_lfork,
		.period = 1000,
		.codage = 0,
		.dir_size = IND_SIZE
	},
	{
		.name = "aff",
		.code = 0x10,
		.argc = 1,
		.argv = {0, 0, 0},
		.argt = {T_REG, 0, 0},
		.function = func_aff,
		.period = 2,
		.codage = 1,
		.dir_size = DIR_SIZE
	}
};

#endif
