/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 05:59:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/26 23:54:17 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <unistd.h>

static void	check_and_rev_if_better_rev(t_push_list **b)
{
	t_push_list	*tmp;
	int			ret;
	int			len;

	tmp = *b;
	ret = 0;
	len = list_size(*b);
	while (tmp->next && tmp->number > tmp->next->number)
	{
		ret++;
		tmp = tmp->next;
	}
	if (ret > len / 2)
	{
		ret = len - ret;
		while (ret-- > 1)
			reverse_rotate_write(b, NULL, 1);
	}
	else
	{
		while (ret-- >= 0)
			rotate_write(b, NULL, 1);
	}
}

static void	find_better_and_push(t_push_list **a, t_push_list **b
	, t_push_list *list, int tmp[4])
{
	while (list)
	{
		if (list->number < tmp[0])
		{
			tmp[1] = tmp[0];
			tmp[0] = list->number;
			tmp[2] = tmp[3];
		}
		else if (list->number < tmp[1])
			tmp[1] = list->number;
		list = list->next;
		tmp[3]++;
	}
	if (tmp[2] <= 2)
		while (tmp[2]--)
			rotate_write(a, NULL, 0);
	else
		while (tmp[2]++ < tmp[3])
			reverse_rotate_write(a, NULL, 0);
	push_write(a, b, 1);
	list = *a;
	tmp[2] = 0;
	while (list->number != tmp[1] && ++(tmp[2]))
		list = list->next;
}

static int	sort_five_elem(t_push_list **a, t_push_list **b, int len)
{
	int		tmp[4];

	if (len != 5)
		return (sort_four_elem(a, b, len));
	tmp[0] = 2147483647;
	tmp[1] = 2147483647;
	tmp[2] = 0;
	tmp[3] = 0;
	find_better_and_push(a, b, *a, tmp);
	if (tmp[2] < 2)
		while (tmp[2]--)
			rotate_write(a, NULL, 0);
	else
		while (tmp[2]++ < tmp[3] - 1)
			reverse_rotate_write(a, NULL, 0);
	push_write(a, b, 1);
	sort_three_elem(a, 3);
	push_write(b, a, 0);
	push_write(b, a, 0);
	return (0);
}

static void	fill_tmp(int *ret, t_push_list **a, int tmp[5])
{
	*ret = list_size(*a) - 1;
	tmp[0] = (*a)->number;
	tmp[1] = (*a)->next->number;
	if (*ret >= 2)
		tmp[2] = (*a)->next->next->number;
	if (*ret >= 3)
		tmp[3] = (*a)->next->next->next->number;
	if (*ret == 4)
		tmp[4] = (*a)->next->next->next->next->number;
	if (*ret == 5)
		tmp[5] = (*a)->next->next->next->next->next->number;
}

void		sort_list(t_push_list **a, t_push_list **b)
{
	int		tmp[5];
	int		ret;

	if (!verify_list(*a, *b))
		return ;
	while (list_size(*a) > 5)
		chose_right_option(a, b);
	sort_five_elem(a, b, list_size(*a));
	if (*b)
	{
		fill_tmp(&ret, a, tmp);
		check_and_rev_if_better_rev(b);
		while (*b)
		{
			if (ret >= 0 && (*b)->number < tmp[ret])
			{
				reverse_rotate_write(a, NULL, 0);
				ret--;
			}
			else
				push_write(b, a, 0);
		}
		while (verify_list(*a, NULL))
			reverse_rotate_write(a, NULL, 0);
	}
}
