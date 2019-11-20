/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:34:02 by widraugr          #+#    #+#             */
/*   Updated: 2019/11/20 14:38:41 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	init(t_frac *frac)
{
	frac->mlx = mlx_init();
	frac->window = mlx_new_window(frac->mlx, WIDTH, HIEGHT, TITLE);
}

int	press_key(int key)
{
	ft_printf("key = [%d]\n", key);
	if (key == K_ESC)
		sys_err("Normal exit\n");
	return (0);
}

int main(int ac, char **av)
{
	t_frac frac;

	init(&frac);
	mlx_key_hook(frac.window, press_key, 0);
	mlx_loop(frac.mlx);
	return (0);
}
