/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:34:02 by widraugr          #+#    #+#             */
/*   Updated: 2019/11/18 18:08:13 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	init(t_frac *frac)
{
	frac->mlx = mlx_init();
	frac->window = mlx_new_window(frac->mlx, WIDTH, HIEGHT, TITLE);

}

int main(int ac, char **av)
{
	t_frac frac;

	init(&frac);
	mlx_loop(frac.mlx);
	return (0);
}
