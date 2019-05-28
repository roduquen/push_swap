/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 03:03:14 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/05 04:45:02 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "checker.h"

void	push_elem(t_push_list **a, t_push_list **b)
{
	t_push_list *tmp;

	tmp = NULL;
	if (*a)
	{
		tmp = (*a)->next;
		if (!*b)
		{
			*b = *a;
			(*b)->next = NULL;
		}
		else
		{
			(*a)->next = *b;
			*b = *a;
		}
		*a = tmp;
	}
}

void	swap_elem(t_push_list **a)
{
	int		tmp;

	if (*a && (*a)->next)
	{
		tmp = (*a)->number;
		(*a)->number = (*a)->next->number;
		(*a)->next->number = tmp;
	}
}

void	rotate_elem(t_push_list **a)
{
	t_push_list	*tmp;

	if (*a && (*a)->next)
	{
		tmp = *a;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *a;
		tmp = (*a)->next;
		(*a)->next = NULL;
		*a = tmp;
	}
}

void	reverse_rotate_elem(t_push_list **a)
{
	t_push_list	*tmp;
	t_push_list	*to_put_on_the_top_of_the_list;

	if (*a && (*a)->next)
	{
		tmp = *a;
		while (tmp->next->next)
			tmp = tmp->next;
		to_put_on_the_top_of_the_list = tmp->next;
		tmp->next = NULL;
		to_put_on_the_top_of_the_list->next = *a;
		*a = to_put_on_the_top_of_the_list;
	}
}
