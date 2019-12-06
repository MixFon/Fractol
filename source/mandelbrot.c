/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 09:30:13 by widraugr          #+#    #+#             */
/*   Updated: 2019/12/06 09:57:29 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	mandelbrot(t_frac *frac, t_compl *c, int *iter)
{
	t_compl comp;

	*iter = -1;
	if (check_fractol(&frac->flags, c))
		return ;
	comp = get_compl(c->re, c->im);
	if (frac->flags.julia)
		c = &frac->k;
	while (pow(comp.re, 2.0) + pow(comp.im, 2.0) <= 4
			&& ++(*iter) < frac->max_iter)
	{
		if (frac->flags.z_2)
			comp = get_compl(pow(comp.re, 2.0) - pow(comp.im, 2.0) + c->re,
					2.0 * comp.re * comp.im + c->im);
		else if (frac->flags.z_3)
			comp = get_compl(pow(comp.re, 3.0) - 3 * comp.re * pow(comp.im, 2.0)
		+ c->re, 3 * pow(comp.re, 2.0) * comp.im - pow(comp.im, 3.0) + c->im);
		else if (frac->flags.z_4)
			comp = get_compl(pow(comp.re, 4.0) - 6 * pow(comp.re, 2.0) *
					pow(comp.im, 2.0) + pow(comp.im, 4.0) + c->re,
					4 * pow(comp.re, 3.0) * comp.im - 4 * comp.re *
					pow(comp.im, 3.0) + c->im);
	}
}

void	ship(t_frac *frac, t_compl *c, int *iter)
{
	t_compl comp;

	*iter = -1;
	comp = get_compl(c->re, c->im);
	if (frac->flags.julia)
		c = &frac->k;
	while (pow(comp.re, 2.0) + pow(comp.im, 2.0) <= 4
			&& ++(*iter) < frac->max_iter)
	{
		if (frac->flags.z_2)
			comp = get_compl(
				pow(comp.re, 2.0) - pow(comp.im, 2.0) + c->re,
				2.0 * fabsl(comp.re * comp.im) + c->im);
		else if (frac->flags.z_3)
			comp = get_compl(
				fabs(pow(comp.re, 3.0)) - 3 * fabsl(comp.re) *
				pow(comp.im, 2.0) + c->re,
				3.0 * pow(comp.re, 2.0) * fabsl(comp.im) -
				fabs(pow(comp.im, 3.0)) + c->im);
		else if (frac->flags.z_4)
			comp = get_compl(pow(comp.re, 4.0) - 6 *
				pow(comp.re * comp.im, 2.0) + pow(comp.im, 4.0) + c->re,
				4 * fabs(pow(comp.re, 3.0) * comp.im) - 4
				* fabs(comp.re * pow(comp.im, 3.0)) + c->im);
	}
}

void	*working_frac(void *arg)
{
	t_parm	par;
	t_frac	*frac;
	t_compl factor;
	t_compl c;

	frac = (t_frac *)arg;
	factor = get_compl(
		(frac->max.re - frac->min.re) / (WIDTH - 1),
		(frac->max.im - frac->min.im) / (HEIGHT - 1));
	get_rage(frac, &par.y, &par.y_end);
	while (++par.y < par.y_end)
	{
		c.im = frac->max.im - par.y * factor.im;
		par.x = 0;
		while (++par.x < WIDTH)
		{
			c.re = frac->min.re + par.x * factor.re;
			if (frac->flags.mandelbrot)
				mandelbrot(frac, &c, &par.iter);
			else if (frac->flags.ship)
				ship(frac, &c, &par.iter);
			create_color(frac, par.x, par.y, par.iter);
		}
	}
	return (NULL);
}
