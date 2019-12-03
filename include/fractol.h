/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:40:09 by widraugr          #+#    #+#             */
/*   Updated: 2019/11/25 12:25:50 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_C
# define FRACTOL_C

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <pthread.h>

# define WIDTH	1000
# define HEIGHT	600
# define TITLE	"Fractol"

# define COUNT_PTH	10

# define K_ESC		53
# define K_UP		126
# define K_DOWN		125
# define K_LEFT		123
# define K_RIGHT	124

# define W_UP	4
# define W_DOWN	5

# define K_Q	12
# define K_W	13
# define K_A	0
# define K_S	1
# define K_Z	6
# define K_X	7
# define K_C	8
# define K_V	9
# define K_R	15

typedef struct	s_compl
{
	double		re;
	double		im;
}				t_compl;

typedef struct	s_parm
{
	int			x;
	int			y;
	int			y_end;
	int			iter;
}				t_parm;
typedef struct	s_frac
{
		void	*mlx;
		void	*window;
		void	*img;
		char	*data_adr;
		char	*data_adr_bazil;
		size_t	max_size_adr;
		int		size_adr;
		int		bits_adr;
		int		endian;
		int		max_iter;
		double	zoom;
		t_compl	min;
		t_compl	max;
		t_compl	k;
		int		julia;
		int		mandelbrot;
		double	color;;
		pthread_t st_pth[COUNT_PTH];

		void	*img_bazil;
		int		size_adr_basil;
}				t_frac;

void	*drow_frac(void *arg);//t_frac *frac);
void	create_theads(t_frac *frac);
t_compl	get_compl(double re, double im);

#endif
