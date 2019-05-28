/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 12:44:05 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/26 16:23:43 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "checker.h"
#include "libft.h"

int			free_visual_list(t_visual *visu)
{
	t_check_list	*tmp;

	while (visu->begin)
	{
		tmp = visu->begin->next;
		free(visu->begin);
		visu->begin = tmp;
	}
	return (0);
}

int			fill_the_visual_instruction(t_visual *visu, t_check_list *list
	, int inst)
{
	t_check_list	*new;

	if (!(new = (t_check_list*)malloc(sizeof(t_check_list))))
		return (1);
	ft_memset(new, 0, sizeof(t_check_list));
	new->type = inst;
	if (!list)
	{
		visu->begin = new;
		visu->list = new;
	}
	else
	{
		while (list->next)
			list = list->next;
		new->prev = list;
		list->next = new;
	}
	return (0);
}

static void	fill_tab_and_translate_list(int *tab, t_push_list *a)
{
	t_push_list	*tmp;
	int			i;

	tmp = a;
	i = 0;
	while (tmp)
	{
		tab[i++] = tmp->number;
		tmp = tmp->next;
	}
	quick_sort_int(tab, i);
	while (a)
	{
		i = 0;
		while (a->number != tab[i])
			i++;
		a->number = i + 1;
		a = a->next;
	}
}

int			re_init_and_translate_lists(t_check_list *list, t_push_list **a
	, t_push_list **b)
{
	int			*tab;
	int			len;

	len = list_size(*a);
	if (!(tab = (int*)malloc(sizeof(int) * len)))
		return (1);
	fill_tab_and_translate_list(tab, *a);
	free(tab);
	while (list->next)
		list = list->next;
	while (list)
	{
		do_the_reverse_instruction(list->type, a, b);
		list = list->prev;
	}
	return (0);
}
