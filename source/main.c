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
	frac->comp.re = 0;
	frac->comp.im = 0;
	frac->mlx = mlx_init();
	frac->window = mlx_new_window(frac->mlx, WIDTH, HEIGHT, TITLE);
	frac->img = mlx_new_image(frac->mlx, WIDTH, HEIGHT);
	frac->data_adr = mlx_get_data_addr(frac->img, &frac->bits_adr,
			&frac->size_adr, &frac->endian);
}

int	press_mouse_key(int key, int x, int y)
{
	ft_printf("mouse key = [%d]\n", key);
	ft_printf("x = [%d], y = [%d]\n", x, y);
	return (0);
}


int	press_key(int key)
{
	ft_printf("key = [%d]\n", key);
	if (key == K_ESC)
		sys_err("Normal exit\n");
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

void	drow_frac(t_frac *frac)
{
	int		x;
	int		y;
	int		iter;
	int		max_iter;
	int		color;
	t_compl comp;
	t_compl min;
	t_compl max;
	t_compl factor;
	t_compl c;
	double	t;

	min = get_compl(-2.0, -2.0);
	max.re = 2.0;
	max.im = min.im + (max.re - min.re) * HEIGHT / WIDTH;

	factor = get_compl(
    (max.re - min.re) / (WIDTH - 1),
    (max.im - min.im) / (HEIGHT - 1));

	y = -1;
	max_iter = 10;
	while(++y < HEIGHT)
	{
		c.im = max.im - y * factor.im;
		x = -1;
		while(++x < WIDTH)
		{
			c.re = min.re + x * factor.re;
			comp = get_compl(c.re, c.im);
			iter = -1;
			while(pow(comp.re, 2.0) + pow(comp.im, 2.0) <= 4
					&& ++iter < max_iter)
			{
				comp = get_compl(
						pow(comp.re, 2.0) - pow(comp.im, 2.0) + c.re,
						2.0 * comp.re * comp.im + c.im);
			}
			ft_printf("%d ", iter);
			if (iter == -1)
				mlx_pixel_put(frac->mlx,frac->window, x, y, 0xff); 
			if (iter == 0)
				mlx_pixel_put(frac->mlx,frac->window, x, y, 0xff00); 
			if (iter == 50)
				mlx_pixel_put(frac->mlx,frac->window, x, y, 0xffff); 
		}
	}
}

int main(int ac, char **av)
{
	t_frac frac;

	init(&frac);
	drow_line(&frac);
	drow_frac(&frac);
	//put_img(&frac);
	mlx_key_hook(frac.window, press_key, 0);
	mlx_mouse_hook(frac.window, press_mouse_key, 0);
	//mlx_loop_hook(frac.mlx,  loop_hook, 0);
	mlx_loop(frac.mlx);
	return (0);
}
