/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 00:42:37 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/27 00:25:05 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			list_size(t_push_list *list)
{
	int		i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int			verify_list(t_push_list *a, t_push_list *b)
{
	if (b)
		return (1);
	while (a->next)
	{
		if (a->number > a->next->number)
			return (1);
		a = a->next;
	}
	return (0);
}
