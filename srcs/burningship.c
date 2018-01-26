/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aledru <aledru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:00:02 by aledru            #+#    #+#             */
/*   Updated: 2018/01/26 13:03:50 by aledru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		burningship_calc(t_complex *z, t_complex *c, double *i)
{
	double	tmp;

	tmp = z->r;
	set_complex(z, z->r * z->r - z->i * z->i + c->r,
				2 * fabs(z->i * tmp) + c->i);
	*i = *i + 1.0;
}

void			burningship_draw(t_fractol *fract)
{
	double		i;
	t_params	*params;
	t_point		*p;

	p = create_point(0, 0);
	params = fract->params;
	while (++p->x < WIN_WIDTH)
	{
		p->y = 0;
		while (++p->y < WIN_HEIGHT)
		{
			i = 0;
			set_complex(params->c, (p->x / params->zoom) + params->min->x,
							(p->y / params->zoom) + params->min->y);
			set_complex(params->z, 0, 0);
			burningship_calc(params->z, params->c, &i);
			while (sqrt(params->z->r * params->z->r + params->z->i *
							params->z->i) < 4 && i < fract->max_iteration)
				burningship_calc(params->z, params->c, &i);
			if (i == fract->max_iteration)
				put_pixel(p->x, p->y, fract, 0);
			else
				put_pixel(p->x, p->y, fract, i);
		}
	}
}
