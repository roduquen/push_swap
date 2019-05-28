/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_renderer_rect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 00:48:27 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/27 01:56:10 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "checker.h"

static void	clamp_color(int color[3])
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (color[i] > 255)
			color[i] = 255;
		else if (color[i] < 0)
			color[i] = 0;
		i++;
	}
}

static void	fill_color(int gradient, int number, int len, int color[3])
{
	int		i;

	i = 0;
	while (i < number && i < len)
	{
		color[0] -= gradient;
		color[1] -= gradient;
		i++;
	}
	clamp_color(color);
	while (i < number && i < 2 * len)
	{
		color[2] -= gradient;
		color[1] += gradient;
		i++;
	}
	clamp_color(color);
	while (i < number && i < 3 * len)
	{
		color[1] -= gradient;
		color[0] += gradient;
		i++;
	}
	clamp_color(color);
}

static void	fill_color_and_add_rect_to_renderer(t_visual *visu, SDL_Rect rect
	, int len, int number)
{
	double		gradient;
	int			color[3];

	gradient = 1000.0 / len;
	len /= 3;
	color[0] = 255;
	color[1] = 255;
	color[2] = 255;
	fill_color((int)gradient, number, len, color);
	SDL_SetRenderDrawColor(visu->renderer, color[0], color[1], color[2], 255);
	SDL_RenderFillRect(visu->renderer, &rect);
}

void		create_renderer(t_visual *visu, t_push_list *a
	, t_push_list *b)
{
	SDL_Rect	rect;

	rect.y = 0;
	rect.h = visu->win_height / visu->len;
	while (a)
	{
		rect.w = a->number * 500 / visu->len;
		rect.x = (500 - rect.w) / 2;
		fill_color_and_add_rect_to_renderer(visu, rect, visu->len, a->number);
		rect.y += rect.h;
		a = a->next;
	}
	rect.y = 0;
	while (b)
	{
		rect.w = b->number * 500 / visu->len;
		rect.x = (500 - rect.w) / 2 + 500;
		fill_color_and_add_rect_to_renderer(visu, rect, visu->len, b->number);
		rect.y += rect.h;
		b = b->next;
	}
}
