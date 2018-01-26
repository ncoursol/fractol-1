/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledru <aledru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:27:32 by aledru            #+#    #+#             */
/*   Updated: 2018/01/26 22:19:19 by aledru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img	*create_img(void *img)
{
	t_img *s_img;

	if (!(s_img = (t_img*)ft_memalloc(sizeof(t_img))))
		malloc_error();
	s_img->img_ptr = img;
	s_img->data = (int *)mlx_get_data_addr(s_img->img_ptr, &s_img->bpp,
			&s_img->size_line, &s_img->endian);
	return (s_img);
}

void	put_pixel(int x, int y, t_fract_thread *f_t, double i)
{
	t_color		*color;
	t_params	*p;

	p = f_t->thread->params;
	if (i != 0)
	{
		i = i - log(log(sqrt(p->z->r * p->z->r + p->z->i * p->z->i))) / log(2);
		i = (767 * i) / f_t->fract->max_iteration;
		if (ft_strcmp(f_t->fract->name, "mandelbrot") == 0)
			color = create_color_rgb(i, i, i);
		if (ft_strcmp(f_t->fract->name, "julia") == 0)
			color = create_color_rgb(0, i, 0);
		if (ft_strcmp(f_t->fract->name, "burningship") == 0)
			color = create_color_rgb(0, i, i);
	}
	else
		color = create_color(0);
	if (y * WIN_WIDTH + x <= WIN_WIDTH * WIN_HEIGHT && y * WIN_WIDTH + x >= 0)
		f_t->fract->img->data[y * WIN_WIDTH + x] = color->decimal;
	ft_memdel((void*)&color);
}

void	display_image(t_fractol *fract)
{
	char	*iteration;

	iteration = ft_itoa(fract->max_iteration);
	mlx_put_image_to_window(fract->mlx, fract->win, fract->img->img_ptr, 0, 0);
	mlx_string_put(fract->mlx, fract->win, 10, 10, 0xFFFFFF,
			"Zoom: Mouse Wheel");
	mlx_string_put(fract->mlx, fract->win, 10, 40, 0xFFFFFF, "Move: < ^ > v");
	mlx_string_put(fract->mlx, fract->win, 10, 70, 0xFFFFFF, "Reset: R");
	mlx_string_put(fract->mlx, fract->win, 10, 100, 0xFFFFFF, "Exit: ESC");
	mlx_string_put(fract->mlx, fract->win, WIN_WIDTH - 135, WIN_HEIGHT - 30,
			0xFFFFFF, "Iteration: ");
	mlx_string_put(fract->mlx, fract->win, WIN_WIDTH - 30, WIN_HEIGHT - 30,
			0xFFFFFF, iteration);
	if (ft_strcmp(fract->name, "julia") == 0)
	{
		if (fract->mouse_disabled == 1)
			mlx_string_put(fract->mlx, fract->win, 10, WIN_HEIGHT - 30,
					0xFFFFFF, "Mouse move: OFF (M)");
		if (fract->mouse_disabled == 0)
			mlx_string_put(fract->mlx, fract->win, 10, WIN_HEIGHT - 30,
					0xFFFFFF, "Mouse move: ON (M)");
	}
	ft_memdel((void*)&iteration);
}
