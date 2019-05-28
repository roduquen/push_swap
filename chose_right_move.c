/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_right_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 22:02:18 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/25 01:11:20 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	check_if_other(t_push_list *a, t_push_list *b, int type)
{
	t_push_list	*tmp;
	int			ret;
	int			ret2;

	ret = 0;
	tmp = b;
	ret2 = 0;
	while (tmp)
	{
		if (tmp->number > b->number)
		{
			while (b != tmp && ++ret)
				b = b->next;
			while (b && a->number < b->number && type && ++ret2)
				b = b->next;
			if (b)
				return (ret + ret2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	return_moves_fill_rb(t_result *result, int moves, int type)
{
	result->rb = type;
	return (moves);
}

static int	check_good_path(t_push_list *a, t_push_list *b, t_result *res
	, int lenb)
{
	int			nbr_move;
	t_push_list	*tmp;

	nbr_move = 0;
	tmp = b;
	while (b && a->number < b->number && ++nbr_move)
		b = b->next;
	if (!b)
	{
		nbr_move = check_if_other(a, tmp, 0);
		if (nbr_move == 0)
			return (return_moves_fill_rb(res, nbr_move, 1));
		if (nbr_move < lenb - nbr_move)
			return (return_moves_fill_rb(res, nbr_move, 0));
		return (return_moves_fill_rb(res, lenb - nbr_move, 1));
	}
	nbr_move += check_if_other(a, b, 1);
	if (lenb - nbr_move < nbr_move)
		return (return_moves_fill_rb(res, lenb - nbr_move, 1));
	return (return_moves_fill_rb(res, nbr_move, 0));
}

static void	fill_result(t_push_list *a, t_push_list *b, t_result *res
	, int type)
{
	res->nbr_move_wait = check_good_path(a, b, res, list_size(b));
	res->best_wait = res->actual + type;
	if (res->rb == type)
		res->total_wait = res->best_wait > res->nbr_move_wait
			? res->best_wait : res->nbr_move_wait;
	else
		res->total_wait = res->best_wait + res->nbr_move_wait;
	if (res->total_wait < res->total)
	{
		res->ra = type;
		res->rbb = res->rb;
		res->best = res->best_wait;
		res->nbr_move = res->nbr_move_wait;
		res->total = res->total_wait;
	}
}

void		check_better_num(t_push_list *a, t_push_list *b, t_result *res)
{
	t_push_list	*tmp[2];

	res->total = list_size(b) * 2;
	tmp[0] = a;
	while (tmp[0]->next)
		tmp[0] = tmp[0]->next;
	while (a && res->actual < res->total)
	{
		fill_result(a, b, res, 0);
		fill_result(tmp[0], b, res, 1);
		tmp[1] = a;
		a = a->next;
		while (tmp[1] && tmp[1]->next != tmp[0])
			tmp[1] = tmp[1]->next;
		if (tmp[1])
			tmp[0] = tmp[1];
		res->actual++;
	}
}
