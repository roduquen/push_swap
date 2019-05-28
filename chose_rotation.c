/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 00:39:21 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/25 00:46:07 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"

static void	do_the_rotation(t_push_list **a, t_push_list **b, t_result *result)
{
	if (result->ra == 0)
	{
		while (result->best-- > 0)
		{
			if (result->ra == result->rbb && result->nbr_move-- > 0)
				rotate_write(a, b, 2);
			else
				rotate_write(a, NULL, 0);
		}
	}
	else
	{
		while (result->best-- > 0)
		{
			if (result->ra == result->rbb && result->nbr_move-- > 0)
				reverse_rotate_write(a, b, 2);
			else
				reverse_rotate_write(a, NULL, 0);
		}
	}
}

void		chose_right_option(t_push_list **a, t_push_list **b)
{
	t_result	result;

	ft_memset(&result, 0, sizeof(t_result));
	if (!*b)
		push_write(a, b, 1);
	else
	{
		check_better_num(*a, *b, &result);
		do_the_rotation(a, b, &result);
		while (result.nbr_move-- > 0)
		{
			if (result.rbb == 0)
				rotate_write(b, NULL, 1);
			else
				reverse_rotate_write(b, NULL, 1);
		}
		push_write(a, b, 1);
	}
}
