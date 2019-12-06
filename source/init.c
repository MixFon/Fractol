/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 09:20:21 by widraugr          #+#    #+#             */
/*   Updated: 2019/12/06 09:51:57 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	init(t_frac *frac)
{
	int	w;
	int	h;

	frac->size_adr = WIDTH;
	frac->max_size_adr = WIDTH * 4 * HEIGHT;
	frac->bits_adr = 4;
	frac->endian = 0;
	frac->max_iter = 30;
	frac->min.re = -2.15;
	frac->min.im = -1.45;
	frac->max.re = 2.15;
	frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
		* HEIGHT / WIDTH;
	frac->zoom = 0.05;
	frac->color = 1;
	frac->mlx = mlx_init();
	frac->window = mlx_new_window(frac->mlx, WIDTH, HEIGHT, TITLE);
	frac->img = mlx_new_image(frac->mlx, WIDTH, HEIGHT);
	frac->data_adr = mlx_get_data_addr(frac->img, &frac->bits_adr,
			&frac->size_adr, &frac->endian);
	if (!(frac->greeting = mlx_xpm_file_to_image(frac->mlx, IMGPATH, &w, &h)))
		if (!(frac->greeting = mlx_xpm_file_to_image(frac->mlx,
						"./image/Fractol.xpm", &w, &h)))
			sys_err("Error file greeting.\n");
}

int		press_mouse_key(int key, int x, int y, t_frac *frac)
{
	x = y;
	if (key == W_UP)
	{
		frac->min.re -= frac->zoom;
		frac->max.re += frac->zoom;
		frac->min.im -= frac->zoom / 2;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
	else if (key == W_DOWN)
	{
		frac->min.re += frac->zoom;
		frac->max.re -= frac->zoom;
		frac->min.im += frac->zoom / 2;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
	create_theads(frac);
	return (0);
}

void	navigation(int key, t_frac *frac)
{
	if (key == K_H)
	{
		frac->min.re += 0.05;
		frac->max.re += 0.05;
	}
	else if (key == K_L)
	{
		frac->min.re -= 0.05;
		frac->max.re -= 0.05;
	}
	else if (key == K_J)
	{
		frac->min.im += 0.05;
		frac->max.im += 0.05;
	}
	else if (key == K_K)
	{
		frac->min.im -= 0.05;
		frac->max.im -= 0.05;
	}
	else if (key == K_ENTER)
		frac->flags.greeting = !frac->flags.greeting;
}

void	formuls(int key, t_frac *frac)
{
	if (key == K_N2)
	{
		frac->flags.z_2 = 1;
		frac->flags.z_3 = 0;
		frac->flags.z_4 = 0;
	}
	else if (key == K_N3)
	{
		frac->flags.z_2 = 0;
		frac->flags.z_3 = 1;
		frac->flags.z_4 = 0;
	}
	else if (key == K_N4)
	{
		frac->flags.z_2 = 0;
		frac->flags.z_3 = 0;
		frac->flags.z_4 = 1;
	}
}

void	change_fractals(int key, t_frac *frac)
{
	if (key == K_N)
		frac->flags.julia = !frac->flags.julia;
	else if (key == K_M)
	{
		frac->flags.ship = 0;
		frac->flags.julia = 0;
		frac->flags.mandelbrot = 1;
	}
	else if (key == K_B)
	{
		frac->flags.ship = 1;
		frac->flags.julia = 0;
		frac->flags.mandelbrot = 0;
	}
	else if (key == K_R)
	{
		frac->min.re = -2.15;
		frac->min.im = -1.45;
		frac->max.re = 2.15;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
}
