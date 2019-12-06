/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nephroida.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 09:25:20 by widraugr          #+#    #+#             */
/*   Updated: 2019/12/06 10:31:51 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int		nephroida(t_compl *c)
{
	double	a;
	double	teta;
	double	ro;
	double	roc;
	double	p;

	a = 0.38;
	p = (double)2 / 3;
	ro = pow(pow((c->re), 2.0) + pow(c->im, 2.0), 0.5);
	teta = atan2(c->im, c->re);
	if (c->im < 0)
		teta = (-1) * teta;
	roc = pow(pow(a, p) * (pow(cos(teta / 2), p) + pow(sin(teta / 2), p)), 1.5);
	if (ro < roc)
		return (1);
	return (0);
}

int		cardioda(t_compl *compl)
{
	double	ro;
	double	teta;
	double	roc;
	double	r;

	r = pow(compl->re + 1, 2.0) + pow(compl->im, 2.0);
	ro = pow((compl->re - 0.25), 2.0) + pow(compl->im, 2.0);
	teta = atan2(compl->im, compl->re - 0.25);
	roc = 0.5 - 0.5 * cos(teta);
	if (ro < pow(roc, 2.0) || r < 0.0625)
		return (1);
	return (0);
}

int		get_rage(t_frac *frac, int *start, int *end)
{
	int i;
	int	delta;

	i = -1;
	delta = HEIGHT / COUNT_PTH;
	*start = 0;
	*end = delta;
	while (++i < COUNT_PTH)
		if (frac->st_pth[i] == pthread_self())
		{
			*end = (i + 1) * delta;
			*start = i * delta;
		}
	(*start)--;
	return (i);
}

void	create_color(t_frac *frac, int x, int y, int iter)
{
	double	t;
	int		color;

	if (iter == -1)
		iter = 0;
	t = (double)iter / (double)frac->max_iter;
	color = (int)(9 * (frac->color - t) * pow(t, 3) * 255);
	color = color << 8;
	color = color | (int)(15 * pow((frac->color - t), 2) * pow(t, 2) * 255);
	color = color << 8;
	color = color | (int)(8.5 * pow((frac->color - t), 3) * t * 255);
	drow_pixel_to_adr(frac, x, y, color);
}

int		check_fractol(t_flags *flags, t_compl *c)
{
	if (!flags->julia)
	{
		if (flags->z_2)
			if (cardioda(c))
				return (1);
		if (flags->z_3)
			if (nephroida(c))
				return (1);
	}
	return (0);
}
