/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:43:49 by vkryvono          #+#    #+#             */
/*   Updated: 2017/11/25 12:45:48 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int num;

	num = (unsigned int)((n < 0) ? -n : n);
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putchar_fd((char)(num % 10 + '0'), fd);
	}
	else
		ft_putchar_fd((char)(num + '0'), fd);
}
