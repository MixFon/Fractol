/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:34:02 by widraugr          #+#    #+#             */
/*   Updated: 2019/11/25 15:12:40 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	init(t_frac *frac)
{
	frac->size_adr = WIDTH;
	frac->max_size_adr = WIDTH * 4 * HEIGHT;
	frac->bits_adr = 4;
	frac->endian = 0;
	frac->max_iter = 10;
	frac->min.re = -2.0;
	frac->min.im = -1;
	frac->max.re = 2.0;
	frac->zoom = 0.1;
	frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
		* HEIGHT / WIDTH;
	frac->mlx = mlx_init();
	frac->window = mlx_new_window(frac->mlx, WIDTH, HEIGHT, TITLE);
	frac->img = mlx_new_image(frac->mlx, WIDTH, HEIGHT);
	frac->data_adr = mlx_get_data_addr(frac->img, &frac->bits_adr,
			&frac->size_adr, &frac->endian);
}

int	press_mouse_key(int key, int x, int y, t_frac *frac)
{
	ft_printf("mouse key = [%d]\n", key);
	ft_printf("x = [%d], y = [%d]\n", x, y);
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
	drow_frac(frac);
	mlx_put_image_to_window(frac->mlx, frac->window, frac->img, 0, 0);
	return (0);
}


int	press_key(int key, t_frac *frac)
{
	ft_printf("key = [%d]\n", key);
	if (key == K_ESC)
		sys_err("Normal exit\n");
	else if (key == K_DOWN)
	{
		frac->min.im -= frac->zoom;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
	else if (key == K_UP)
	{
		frac->min.im += frac->zoom;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
	else if (key == K_LEFT)
	{
		frac->min.re -= frac->zoom;
		frac->max.re -= frac->zoom;
	}
	else if (key == K_RIGHT)
	{
		frac->min.re += frac->zoom;
		frac->max.re += frac->zoom;
	}
	else if (key == K_C)
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
	else if (key == K_R)
	{
		frac->min.re = -2.0;
		frac->min.im = -1.0;
		frac->max.re = 2.0;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
	else if (key == K_Z)
		frac->max_iter += 10;
	else if (key == K_X)
		frac->max_iter -= 10;
	drow_frac(frac);
	mlx_put_image_to_window(frac->mlx, frac->window, frac->img, 0, 0);
	return (0);
}

void	put_img(t_frac *frac)
{
	int i;
	
	i = -1;
	mlx_put_image_to_window(frac->mlx, frac->window, frac->img, 0, 0);
}

void	drow_pixel_to_adr(t_frac *frac, int x, int y, int color)
{
	char	*line;
	int		i;

	i = 4 * (WIDTH * y + x);
	if (i < 0 || i > frac->max_size_adr)
		return ;
	line = frac->data_adr;
	line[i] = color & 0xff;
	line[++i] = (color >> 8) & 0xff;
	line[++i] = (color >> 16) & 0xff;
}

void	drow_line(t_frac *frac)
{
	int i;

	i = -100;
	while(++i < 100)
		drow_pixel_to_adr(frac, i + WIDTH / 2, 0 + HEIGHT / 2, 0xff0000);
	i = -100;
	while(++i < 100)
		drow_pixel_to_adr(frac, 0 + WIDTH / 2, i + HEIGHT / 2, 0xff0000);
}

t_compl	get_compl(double re, double im)
{
	t_compl comp;
	
	comp.re = re;
	comp.im = im;
	return (comp);
}

int	cardioda(t_compl *compl)
{
	double	ro;
	double	teta;
	double	roc;
	double r;

	r = pow(compl->re + 1, 2.0) + pow(compl->im, 2.0);
	ro = pow((compl->re - 0.25), 2.0) + pow(compl->im, 2.0);
	teta = atan2(compl->im, compl->re - 0.25);
	roc = 0.5 - 0.5 * cos(teta);
	if (ro < pow(roc, 2.0) || r < 0.0625)
		return (1);
	return (0);
}

void	drow_frac(t_frac *frac)
{
	int		x;
	int		y;
	int		iter;
	int		max_iter;
	int		color;
	t_compl comp;
	t_compl factor;
	t_compl c;
	double	t;

	factor = get_compl(
    (frac->max.re - frac->min.re) / (WIDTH - 1),
    (frac->max.im - frac->min.im) / (HEIGHT - 1));

	y = 0;
	max_iter = frac->max_iter;
	while(++y < HEIGHT)
	{
		c.im = frac->max.im - y * factor.im;
		x = 0;
		while(++x < WIDTH)
		{
			c.re = frac->min.re + x * factor.re;
			comp = get_compl(c.re, c.im);
			iter = -1;
			if (!cardioda(&comp))
			{
				while(pow(comp.re, 2.0) + pow(comp.im, 2.0) <= 4
						&& ++iter < max_iter)
				{
					comp = get_compl(
							pow(comp.re, 2.0) - pow(comp.im, 2.0) + c.re,
							2.0 * comp.re * comp.im + c.im);
				}
			}
			t = (double)iter / (double)max_iter;

			color = (int)(9 * (1 - t) * pow(t, 3) * 255);
			color = color << 8;
			color =color | (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
			color = color << 8;
			color = color | (int)(8.5 * pow((1 - t), 3) * t * 255);
			drow_pixel_to_adr(frac, x, y, color); 
		}
	}
}

int main(int ac, char **av)
{
	t_frac frac;

	init(&frac);
	drow_line(&frac);
	drow_frac(&frac);
	put_img(&frac);
	mlx_key_hook(frac.window, press_key, &frac);
	mlx_mouse_hook(frac.window, press_mouse_key, &frac);
	//mlx_loop_hook(frac.mlx,  loop_hook, 0);
	mlx_loop(frac.mlx);
	return (0);
}
