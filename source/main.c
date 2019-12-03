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
	frac->size_adr_basil = 100;
	frac->max_size_adr = WIDTH * 4 * HEIGHT;
	frac->bits_adr = 4;
	frac->endian = 0;
	frac->max_iter = 10;
	frac->min.re = -2.0;
	frac->min.im = -1;
	frac->max.re = 2.0;
	frac->zoom = 0.1;
	frac->color = 1;
	frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
		* HEIGHT / WIDTH;
	frac->mlx = mlx_init();
	frac->window = mlx_new_window(frac->mlx, WIDTH, HEIGHT, TITLE);

	frac->img_bazil = mlx_new_image(frac->mlx, 100, 100);
	frac->img = mlx_new_image(frac->mlx, WIDTH, HEIGHT);
	frac->data_adr_bazil = mlx_get_data_addr(frac->img_bazil, &frac->bits_adr,
			&frac->size_adr_basil, &frac->endian);
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
	create_theads(frac);
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
	else if (key == K_Q)
	{
		frac->k = get_compl(0.1, 1);
		ft_putendl("hook");
		ft_printf("re = [%f], im = {%f}\n", frac->k.re, frac->k.im);
		//ft_printf("x = [%d], y = {%d}\n", x, y);
		create_theads(frac);
	}
	else if (key == K_W)
	{
		frac->k = get_compl(0.56, 0.11);
		ft_putendl("hook");
		ft_printf("re = [%f], im = {%f}\n", frac->k.re, frac->k.im);
		//ft_printf("x = [%d], y = {%d}\n", x, y);
		create_theads(frac);
	}
	else if (key == K_A)
		frac->color += 0.1;
	else if (key == K_S)
		frac->color -= 0.1;
	else if (key == K_Z)
		frac->max_iter += 10;
	else if (key == K_X)
		frac->max_iter -= 10;
	create_theads(frac);
	//mlx_put_image_to_window(frac->mlx, frac->window, frac->img, 0, 0);
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
	color =color | (int)(15 * pow((frac->color - t), 2) * pow(t, 2) * 255);
	color = color << 8;
	color = color | (int)(8.5 * pow((frac->color - t), 3) * t * 255);
	drow_pixel_to_adr(frac, x, y, color); 
}

void	get_iteration_centroida(t_compl *c, int *max_iter, int *iter)
{
	t_compl comp;

	comp = get_compl(c->re, c->im);
	*iter = -1;
	while(pow(comp.re, 2.0) + pow(comp.im, 2.0) <= 4
			&& ++(*iter) < *max_iter)
	{
		comp = get_compl(
				pow(comp.re, 3.0) - 3 * comp.re * pow(comp.im, 2.0) + c->re,
				3 * pow(comp.re, 2.0) * comp.im - pow(comp.im, 3.0) + c->im);
	}
}

void	get_iteration_cent_julia(t_compl *c, t_compl *k, int *max_iter, int *iter)
{
	t_compl comp;

	comp = get_compl(c->re, c->im);
	*iter = -1;
	while(pow(comp.re, 2.0) + pow(comp.im, 2.0) <= 4
			&& ++(*iter) < *max_iter)
	{
		comp = get_compl(
				pow(comp.re, 3.0) - 3 * comp.re * pow(comp.im, 2.0) + k->re,
				3 * pow(comp.re, 2.0) * comp.im - pow(comp.im, 3.0) + k->im);
	}

}

void	get_iteration(t_compl *c, int *max_iter, int *iter)
{
	t_compl comp;

	comp = get_compl(c->re, c->im);
	*iter = -1;
	if (!cardioda(&comp))
	{
		while(pow(comp.re, 2.0) + pow(comp.im, 2.0) <= 4
				&& ++(*iter) < *max_iter)
		{
			comp = get_compl(
					pow(comp.re, 2.0) - pow(comp.im, 2.0) + c->re,
					2.0 * comp.re * comp.im + c->im);
		}
	}
}

void	get_iteration_julia(t_compl *c, t_compl *k, int *max_iter, int *iter)
{
	t_compl comp;

	comp = get_compl(c->re, c->im);
	*iter = -1;
	while(pow(comp.re, 2.0) + pow(comp.im, 2.0) <= 4
			&& ++(*iter) < *max_iter)
	{
		comp = get_compl(
				pow(comp.re, 2.0) - pow(comp.im, 2.0) + k->re,
				2.0 * comp.re * comp.im + k->im);
	}

}

void	*mandelbrot(void *arg)
{
	t_parm	par;
	t_frac	*frac;
	t_compl factor;
	t_compl c;

	frac = (t_frac *)arg;
	factor = get_compl(
    (frac->max.re - frac->min.re) / (WIDTH - 1),
    (frac->max.im - frac->min.im) / (HEIGHT - 1));
	//ft_printf("thid = [%d]\n", (int)(pthread_self()));
	get_rage(frac, &par.y, &par.y_end);
	//ft_printf("start = [%d] end = {%d}\n", par.y, par.y_end);
	while(++par.y < par.y_end)
	{
		c.im = frac->max.im - par.y * factor.im;
		par.x = 0;
		while(++par.x < WIDTH)
		{
			c.re = frac->min.re + par.x * factor.re;
			get_iteration_centroida(&c, &frac->max_iter, &par.iter);
			create_color(frac, par.x, par.y, par.iter); 
		}
	}
	return (NULL);
}

void	*julia(void *arg)
{
	t_parm	par;
	t_frac	*frac;
	t_compl factor;
	t_compl c;

	frac = (t_frac *)arg;
	factor = get_compl(
    (frac->max.re - frac->min.re) / (WIDTH - 1),
    (frac->max.im - frac->min.im) / (HEIGHT - 1));
	//ft_printf("thid = [%d]\n", (int)(pthread_self()));
	get_rage(frac, &par.y, &par.y_end);
	//ft_printf("start = [%d] end = {%d}\n", par.y, par.y_end);
	while(++par.y < par.y_end)
	{
		c.im = frac->max.im - par.y * factor.im;
		par.x = 0;
		while(++par.x < WIDTH)
		{
			c.re = frac->min.re + par.x * factor.re;
			get_iteration_cent_julia(&c, &frac->k, &frac->max_iter, &par.iter);
			create_color(frac, par.x, par.y, par.iter); 
		}
	}
	return (NULL);
}

void	create_theads(t_frac *frac)
{
	int i;

	i = -1;
	while (++i < COUNT_PTH)
	{
		if ((pthread_create(&(frac->st_pth[i]), NULL, julia, frac)))
			sys_err("Error create thread\n");
	}
	i = -1;
	while (++i < COUNT_PTH)
		if (pthread_join(frac->st_pth[i], NULL))
			sys_err("Error join thread\n");
	mlx_put_image_to_window(frac->mlx, frac->window, frac->img, 0, 0);
	mlx_put_image_to_window(frac->mlx, frac->window, frac->img_bazil, 0, 0);
}

int		expose_hook(int x, int y, t_frac *frac)
{
	ft_putendl("Hook");
	ft_printf("!x = [%d], y = {%d}\n", x, y);
	return (0);
}

int		loop_hook(int x, int y, t_frac *frac)
{
	mlx_put_image_to_window(frac->mlx, frac->window, frac->img, 0, 0);
	ft_printf("!x = [%d], y = {%d}\n", x, y);
	return (0);
}

int		hook_coordinats(int x, int y, t_frac *frac)
{
	frac->k = get_compl(
			4 * ((double)x / WIDTH - 0.5),
			4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
	ft_putendl("hook");
	ft_printf("re = [%f], im = {%f}\n", frac->k.re, frac->k.im);
	ft_printf("x = [%d], y = {%d}\n", x, y);
	create_theads(frac);
	return (0);
}

void	print_error_arg(void)
{
	char *err;

	err = "Wrong fractal name.\n\n\
	Use:\n\
	./fractol Julia\n\
	./fractol Mandelbrot\n";
	sys_err(err);
}

void	name_fractal(t_frac *frac, char **av)
{
	frac->julia = 0;
	frac->mandelbrot = 0;
	if (!(ft_strcmp(av[1], "Julia")))
		frac->julia = 1;
	else if (!(ft_strcmp(av[1], "Mandelbrot")))
		frac->julia = 1;
	ft_printf("J = {%d} M = [%d]\n", frac->julia, frac->mandelbrot);
}

int		main(int ac, char **av)
{
	t_frac frac;

	if (ac != 2)
		print_error_arg();
	name_fractal(&frac, av);
	init(&frac);
	create_theads(&frac);
	mlx_key_hook(frac.window, press_key, &frac);
	mlx_mouse_hook(frac.window, press_mouse_key, &frac);
	//mlx_expose_hook(frac.window, expose_hook, &frac);
	mlx_hook(frac.window, 6, 6, hook_coordinats, &frac);
	//mlx_loop_hook(frac.mlx, loop_hook, &frac);
	mlx_loop(frac.mlx);
	return (0);
}
