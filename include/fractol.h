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

# define WIDTH	1000
# define HEIGHT	500
# define TITLE	"Fractol"
# define K_ESC	53

typedef struct	s_frac
{
		void	*mlx;
		void	*window;
		void	*img;
		char	*data_adr;
		size_t	max_size_adr;
		int		size_adr;
		int		bits_adr;
		int		endian;
}				t_frac;

#endif
