/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_verify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 03:42:49 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/27 00:20:43 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "checker.h"
#include <unistd.h>

int			check_if_stdin_formated(char *buffer)
{
	if (ft_strequ(buffer, "sa\n"))
		return (1);
	else if (ft_strequ(buffer, "sb\n"))
		return (2);
	else if (ft_strequ(buffer, "ss\n"))
		return (3);
	else if (ft_strequ(buffer, "pb\n"))
		return (4);
	else if (ft_strequ(buffer, "pa\n"))
		return (5);
	else if (ft_strequ(buffer, "ra\n"))
		return (6);
	else if (ft_strequ(buffer, "rb\n"))
		return (7);
	else if (ft_strequ(buffer, "rr\n"))
		return (8);
	else if (ft_strequ(buffer, "rra\n"))
		return (9);
	else if (ft_strequ(buffer, "rrb\n"))
		return (10);
	else if (ft_strequ(buffer, "rrr\n"))
		return (11);
	return (0);
}

void		do_the_reverse_instruction(int inst, t_push_list **a
	, t_push_list **b)
{
	if (inst == 1 || inst == 3)
		swap_elem(a);
	if (inst == 2 || inst == 3)
		swap_elem(b);
	if (inst == 4)
		push_elem(b, a);
	if (inst == 5)
		push_elem(a, b);
	if (inst == 6 || inst == 8)
		reverse_rotate_elem(a);
	if (inst == 7 || inst == 8)
		reverse_rotate_elem(b);
	if (inst == 9 || inst == 11)
		rotate_elem(a);
	if (inst == 10 || inst == 11)
		rotate_elem(b);
}

void		do_the_instruction(int inst, t_push_list **a, t_push_list **b
	, t_visual *visu)
{
	if (inst == 1 || inst == 3)
		swap_elem(a);
	if (inst == 2 || inst == 3)
		swap_elem(b);
	if (inst == 4)
		push_elem(a, b);
	if (inst == 5)
		push_elem(b, a);
	if (inst == 6 || inst == 8)
		rotate_elem(a);
	if (inst == 7 || inst == 8)
		rotate_elem(b);
	if (inst == 9 || inst == 11)
		reverse_rotate_elem(a);
	if (inst == 10 || inst == 11)
		reverse_rotate_elem(b);
	if (visu->enabled)
	{
		visu->ret = fill_the_visual_instruction(visu, visu->list, inst);
		if (visu->ret)
			visu->enabled = 0;
	}
}

int			parse_stdin(t_push_list **a, t_push_list **b, t_visual *visu)
{
	char	buffer[5];
	int		ret[2];

	ret[0] = 0;
	while ((ret[1] = read(0, buffer + ret[0], 1)) > 0)
	{
		if (buffer[ret[0]] == '\n')
		{
			buffer[ret[0] + 1] = 0;
			if (!(ret[1] = check_if_stdin_formated(buffer)))
				return (1);
			else
				do_the_instruction(ret[1], a, b, visu);
			ft_memset(buffer, 0, 5);
			ret[0] = 0;
		}
		else if (ret[0] < 3)
			ret[0]++;
		else
			return (1);
	}
	if (ret[1] == -1 || (buffer[0] && ret[0]))
		return (1);
	return (0);
}
