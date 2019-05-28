/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:47:29 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/27 00:45:02 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "checker.h"

static int	leave_sdl(t_visual *visu, int type)
{
	if (visu->renderer)
		SDL_DestroyRenderer(visu->renderer);
	if (visu->window)
		SDL_DestroyWindow(visu->window);
	SDL_Quit();
	return (type);
}

static int	chose_winsize(t_visual *visu)
{
	if (visu->len < 250)
		return (visu->win_height = 1000);
	if (visu->len < 400)
		return (visu->win_height = visu->len * 4);
	return (visu->win_height = 1600);
}

static int	init_visual(t_visual *visu)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s"
			, SDL_GetError());
		return (1);
	}
	if (SDL_CreateWindowAndRenderer(1000, chose_winsize(visu), SDL_WINDOW_SHOWN
			, &visu->window, &visu->renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
			, "Couldn't create window and renderer: %s", SDL_GetError());
		return (leave_sdl(visu, 1));
	}
	return (0);
}

static void	do_the_visual_while_not_paused(t_visual *visu, t_push_list **a
	, t_push_list **b)
{
	visu->start = 1;
	do_the_instruction(visu->list->type, a, b, visu);
	if (visu->list->next)
		visu->list = visu->list->next;
	else
	{
		visu->pause = 0;
		visu->end = 1;
	}
}

int			check_do_and_leave_the_visual(t_visual *visu, t_push_list **a
	, t_push_list **b)
{
	visu->enabled = 0;
	if (visu->ret || list_size(*a) > 1000 || !visu->list || init_visual(visu))
		return (free_visual_list(visu));
	visu->len = list_size(*a);
	re_init_and_translate_lists(visu->list, a, b);
	create_renderer(visu, *a, *b);
	SDL_RenderPresent(visu->renderer);
	while (!visu->exit)
	{
		while (SDL_PollEvent(&visu->event))
			commands(visu, a, b);
		SDL_SetRenderDrawColor(visu->renderer, 0, 0, 0, 255);
		SDL_RenderClear(visu->renderer);
		if (visu->pause)
			do_the_visual_while_not_paused(visu, a, b);
		create_renderer(visu, *a, *b);
		SDL_RenderPresent(visu->renderer);
	}
	free_visual_list(visu);
	return (leave_sdl(visu, 0));
}
