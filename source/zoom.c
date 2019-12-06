/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 09:22:39 by widraugr          #+#    #+#             */
/*   Updated: 2019/12/06 09:52:56 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	zoom(int key, t_frac *frac)
{
	if (key == K_C)
	{
		frac->min.re -= frac->zoom;
		frac->max.re += frac->zoom;
		frac->min.im -= frac->zoom / 2;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
	else if (key == K_V)
	{
		frac->min.re += frac->zoom;
		frac->max.re -= frac->zoom;
		frac->min.im += frac->zoom / 2;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
	else if (key == K_Q)
	{
		if (frac->zoom - 0.01 <= 0)
			frac->zoom -= 0.001;
		else
			frac->zoom -= 0.01;
	}
	else if (key == K_W)
		frac->zoom += 0.01;
}

void	change_mandelbrot_frac(int key, t_frac *frac)
{
	if (key == K_1)
		frac->k = get_compl(0, 0);
	else if (key == K_2)
		frac->k = get_compl(-0.2, 0);
	else if (key == K_3)
		frac->k = get_compl(-0.5, 0);
	else if (key == K_4)
		frac->k = get_compl(-0.75, 0);
	else if (key == K_5)
		frac->k = get_compl(-1, 0);
	else if (key == K_6)
		frac->k = get_compl(-0.12, 0.74);
	else if (key == K_7)
		frac->k = get_compl(-1.77, 0);
	else if (key == K_8)
		frac->k = get_compl(0, 1);
}

int		press_key(int key, t_frac *frac)
{
	if (key == K_ESC)
		sys_err("Normal exit\n");
	else if (key == K_DOWN)
		frac->k.im -= 0.01;
	else if (key == K_UP)
		frac->k.im += 0.01;
	else if (key == K_LEFT)
		frac->k.re += 0.01;
	else if (key == K_RIGHT)
		frac->k.re -= 0.01;
	else if (key == K_A)
		frac->color += 0.1;
	else if (key == K_S)
		frac->color -= 0.1;
	else if (key == K_Z)
		frac->max_iter += 10;
	else if (key == K_X)
		frac->max_iter -= 10;
	zoom(key, frac);
	change_mandelbrot_frac(key, frac);
	change_fractals(key, frac);
	formuls(key, frac);
	navigation(key, frac);
	create_theads(frac);
	return (0);
}

void	drow_pixel_to_adr(t_frac *frac, int x, int y, int color)
{
	char	*line;
	int		i;

	i = 4 * (WIDTH * y + x);
	if (i < 0 || i > (int)frac->max_size_adr)
		return ;
	line = frac->data_adr;
	line[i] = color & 0xff;
	line[++i] = (color >> 8) & 0xff;
	line[++i] = (color >> 16) & 0xff;
}

t_compl	get_compl(double re, double im)
{
	t_compl comp;

	comp.re = re;
	comp.im = im;
	return (comp);
}
