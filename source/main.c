/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:34:02 by widraugr          #+#    #+#             */
/*   Updated: 2019/12/06 09:57:43 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

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

int		hook_coordinats(int x, int y, t_frac *frac)
{
	frac->k = get_compl(
			4 * ((double)x / WIDTH - 0.5),
			4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
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
	mlx_hook(frac.window, 6, 6, hook_coordinats, &frac);
	mlx_loop(frac.mlx);
	return (0);
}
