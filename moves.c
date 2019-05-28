/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:39:01 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/25 15:51:19 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "checker.h"

void		push_write(t_push_list **list, t_push_list **lists, char type)
{
	push_elem(list, lists);
	if (type == 0)
		write(1, "pa\n", 3);
	else if (type == 1)
		write(1, "pb\n", 3);
}

void		swap_write(t_push_list **list, t_push_list **lists, char type)
{
	swap_elem(list);
	if (type == 0)
		write(1, "sa\n", 3);
	else if (type == 1)
		write(1, "sb\n", 3);
	else if (type == 2)
	{
		swap_elem(lists);
		write(1, "ss\n", 3);
	}
}

void		rotate_write(t_push_list **list, t_push_list **lists, char type)
{
	rotate_elem(list);
	if (type == 0)
		write(1, "ra\n", 3);
	else if (type == 1)
		write(1, "rb\n", 3);
	else if (type == 2)
	{
		rotate_elem(lists);
		write(1, "rr\n", 3);
	}
}

void		reverse_rotate_write(t_push_list **list, t_push_list **lists
	, char type)
{
	reverse_rotate_elem(list);
	if (type == 0)
		write(1, "rra\n", 4);
	else if (type == 1)
		write(1, "rrb\n", 4);
	else if (type == 2)
	{
		reverse_rotate_elem(lists);
		write(1, "rrr\n", 4);
	}
}
