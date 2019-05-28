/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:48:53 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/27 00:24:40 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "checker.h"

static void	command_to_reverse(t_visual *visu, t_push_list **a, t_push_list **b)
{
	if (!visu->list->prev && visu->start)
	{
		visu->start = 0;
		do_the_reverse_instruction(visu->list->type, a, b);
	}
	else if (visu->start)
	{
		if (!visu->end)
			visu->list = visu->list->prev;
		do_the_reverse_instruction(visu->list->type, a, b);
	}
	visu->end = 0;
}

void		commands(t_visual *visu, t_push_list **a, t_push_list **b)
{
	if (visu->event.key.type == SDL_KEYUP)
	{
		if (visu->event.key.keysym.sym == SDLK_SPACE)
			visu->pause = visu->pause == 1 ? 0 : 1;
		if (visu->event.key.keysym.sym == SDLK_ESCAPE)
			visu->exit = 1;
	}
	if (visu->event.key.type == SDL_KEYDOWN)
	{
		if (!visu->pause && visu->event.key.keysym.sym == SDLK_RIGHT)
		{
			if (!visu->end)
			{
				do_the_instruction(visu->list->type, a, b, visu);
				if (!visu->list->next)
					visu->end = 1;
				else
					visu->list = visu->list->next;
			}
			visu->start = 1;
		}
		if (!visu->pause && visu->event.key.keysym.sym == SDLK_LEFT)
			command_to_reverse(visu, a, b);
	}
}
