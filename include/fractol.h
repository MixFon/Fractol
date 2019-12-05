/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:40:09 by widraugr          #+#    #+#             */
/*   Updated: 2019/12/05 19:28:34 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_C
# define FRACTOL_C

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <pthread.h>

# define WIDTH	1200
# define HEIGHT	800
# define TITLE	"Fractol"

# define COUNT_PTH	100

# define IMGPATH	"./image/Fractol.xpm"

# define K_ESC		53
# define K_UP		126
# define K_DOWN		125
# define K_LEFT		123
# define K_RIGHT	124
# define K_ENTER	36

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
# define K_M	46
# define K_N	45
# define K_B	11

# define K_H	4
# define K_J	38
# define K_K	40
# define K_L	37

# define K_1	18
# define K_2	19
# define K_3	20
# define K_4	21
# define K_5	23
# define K_6	22
# define K_7	26
# define K_8	28

# define K_N2	84
# define K_N3	85
# define K_N4	86

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

typedef struct	s_flags
{
	int			julia : 1;
	int			mandelbrot : 1;
	int			ship : 1;
	int			z_2 : 1;
	int			z_3 : 1;
	int			z_4 : 1;
	int			greeting : 1;
}				t_flags;

typedef struct	s_frac
{
		void	*mlx;
		void	*window;
		void	*img;
		void	*greeting;
		char	*data_adr;
		size_t	max_size_adr;
		int		size_adr;
		int		bits_adr;
		int		endian;
		int		max_iter;
		double	zoom;
		t_compl	min;
		t_compl	max;
		t_compl	k;
		double	color;
		pthread_t st_pth[COUNT_PTH];
		t_flags	flags;
}				t_frac;

void	*drow_frac(void *arg);//t_frac *frac);
void	create_theads(t_frac *frac);
t_compl	get_compl(double re, double im);
void	drow_pixel_to_adr(t_frac *frac, int x, int y, int color);
void	greeting(t_frac *frac);

#endif
