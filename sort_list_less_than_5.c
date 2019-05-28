/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_less_than_5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 23:52:01 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/26 23:55:03 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			sort_three_elem(t_push_list **a, int len)
{
	if (len == 3)
	{
		while (verify_list(*a, NULL))
		{
			if ((*a)->number > (*a)->next->number
					&& (*a)->number > (*a)->next->next->number)
				rotate_write(a, NULL, 0);
			else if ((*a)->number > (*a)->next->number
					&& (*a)->number < (*a)->next->next->number)
				swap_write(a, NULL, 0);
			else if ((*a)->number < (*a)->next->number
					&& (*a)->number > (*a)->next->next->number)
				reverse_rotate_write(a, NULL, 0);
			else if ((*a)->next->number > (*a)->next->next->number)
				rotate_write(a, NULL, 0);
		}
	}
	else
	{
		if (!verify_list(*a, NULL))
			return (0);
		else
			swap_write(a, NULL, 0);
	}
	return (0);
}

int			sort_four_elem(t_push_list **a, t_push_list **b, int len)
{
	if (len != 4)
		return (sort_three_elem(a, len));
	push_write(a, b, 1);
	sort_three_elem(a, 3);
	if ((*b)->number < (*a)->number)
		push_write(b, a, 0);
	else if ((*b)->number < (*a)->next->number)
	{
		rotate_write(a, NULL, 0);
		push_write(b, a, 0);
		reverse_rotate_write(a, NULL, 0);
	}
	else if ((*b)->number < (*a)->next->next->number)
	{
		reverse_rotate_write(a, NULL, 0);
		push_write(b, a, 0);
		rotate_write(a, NULL, 0);
		rotate_write(a, NULL, 0);
	}
	else
	{
		push_write(b, a, 0);
		rotate_write(a, NULL, 0);
	}
	return (0);
}
