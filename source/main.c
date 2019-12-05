/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:34:02 by widraugr          #+#    #+#             */
/*   Updated: 2019/12/05 19:28:33 by widraugr         ###   ########.fr       */
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
	frac->zoom = 0.05;
	frac->color = 1;
	frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
		* HEIGHT / WIDTH;
	frac->mlx = mlx_init();
	frac->window = mlx_new_window(frac->mlx, WIDTH, HEIGHT, TITLE);
	frac->img = mlx_new_image(frac->mlx, WIDTH, HEIGHT);
	frac->data_adr = mlx_get_data_addr(frac->img, &frac->bits_adr,
			&frac->size_adr, &frac->endian);
	if (!(frac->greeting = mlx_xpm_file_to_image(frac->mlx, IMGPATH, &w, &h)))
		sys_err("Error file greeting.\n");
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
	ft_printf("re = [%0f], im = [%0f], minim = [%0f]\n",
			frac->min.re, frac->max.re, frac->min.im);
	create_theads(frac);
	return (0);
}

int	press_key(int key, t_frac *frac)
{
	ft_printf("key = [%d]\n", key);
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
	else if (key == K_N)
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
		frac->min.re = -2.0;
		frac->min.im = -1.0;
		frac->max.re = 2.0;
		frac->max.im = frac->min.im + (frac->max.re - frac->min.re)
			* HEIGHT / WIDTH;
	}
	else if (key == K_1)
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
	else if (key == K_Q)
	{
		if (frac->zoom - 0.01 <= 0)
			frac->zoom -= 0.001;
		else
			frac->zoom -= 0.01;
	}
	else if (key == K_W)
		frac->zoom += 0.01;
	else if (key == K_A)
		frac->color += 0.1;
	else if (key == K_S)
		frac->color -= 0.1;
	else if (key == K_Z)
		frac->max_iter += 10;
	else if (key == K_X)
		frac->max_iter -= 10;
	else if (key == K_H)
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
	else if (key == K_X)
		frac->max_iter -= 10;
	else if (key == K_X)
		frac->max_iter -= 10;
	else if (key == K_N2)
	{
		frac->flags.z_2 = 1;
		frac->flags.z_3 = 0;
		frac->flags.z_4 = 0;
	}
	else if (key == K_ENTER)
		frac->flags.greeting = !frac->flags.greeting;
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
	create_theads(frac);
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

int nephroida(t_compl *c)
{
	double	a;
	double	teta;
	double	ro;
	double	roc;
	double	p;
	
	a = 0.38;
	p = (double)2/3;
	ro = pow(pow((c->re), 2.0) + pow(c->im, 2.0), 0.5);
	teta = atan2(c->im, c->re);
	if (c->im < 0)
		teta = (-1) * teta;
	roc = pow(pow(a, p) * (pow(cos(teta / 2), p) + pow(sin(teta / 2), p)), 1.5);
	if (ro < roc)
		return (1);
	return (0);
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
				fabs(pow(comp.re, 3.0)) - 3 * fabsl(comp.re) * pow(comp.im, 2.0) + c->re,
				3.0 * pow(comp.re, 2.0) * fabsl(comp.im) - fabs(pow(comp.im, 3.0)) + c->im);
		else if (frac->flags.z_4)
			comp = get_compl(
					pow(comp.re, 4.0) - 6 * pow(comp.re * comp.im, 2.0) + pow(comp.im, 4.0)
					+ c->re,
			4 * fabs(pow(comp.re, 3.0) * comp.im) - 4 * fabs(comp.re * pow(comp.im, 3.0))
			+ c->im);
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
	while(++par.y < par.y_end)
	{
		c.im = frac->max.im - par.y * factor.im;
		par.x = 0;
		while(++par.x < WIDTH)
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

void	create_theads(t_frac *frac)
{
	int i;

	i = -1;
	if (frac->flags.greeting)
	{
		mlx_put_image_to_window(frac->mlx, frac->window, frac->greeting, 0, 0);
		return ;
	}
	while (++i < COUNT_PTH)
	{
		if ((pthread_create(&(frac->st_pth[i]), NULL, working_frac, frac)))
			sys_err("Error create thread\n");
	}
	i = -1;
	while (++i < COUNT_PTH)
		if (pthread_join(frac->st_pth[i], NULL))
			sys_err("Error join thread\n");
	mlx_put_image_to_window(frac->mlx, frac->window, frac->img, 0, 0);
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
	./fractol Mandelbrot\n\
	./fractol Ship\n";
	sys_err(err);
}

void	name_fractal(t_frac *frac, char **av)
{
	frac->flags.julia = 0;
	frac->flags.mandelbrot = 0;
	frac->flags.ship = 0;
	frac->flags.z_2 = 1;
	frac->flags.z_3 = 0;
	frac->flags.z_4 = 0;
	frac->flags.greeting = 1;
	if (!(ft_strcmp(av[1], "Julia")))
		frac->flags.julia = 1;
	else if (!(ft_strcmp(av[1], "Mandelbrot")))
		frac->flags.mandelbrot = 1;
	else if (!(ft_strcmp(av[1], "Ship")))
		frac->flags.ship = 1;
	else
		print_error_arg();
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
