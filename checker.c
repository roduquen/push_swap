/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 23:59:56 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/26 19:58:09 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "checker.h"

static t_push_list	*create_new_elem(void)
{
	t_push_list	*new;

	if (!(new = (t_push_list*)malloc(sizeof(t_push_list))))
		return (NULL);
	new->number = 0;
	new->next = NULL;
	return (new);
}

static int			check_and_fill_av(char **av, t_push_list **a
	, t_push_list *b, t_visual *visu)
{
	int		i;
	char	*test;

	i = 1;
	if (av[1][0] == '-' && av[1][1] == 'v' && !av[1][2] && ++i)
		visu->enabled = 1;
	if (!(*a = create_new_elem()))
		return (1);
	b = *a;
	while (av[i])
	{
		if (av[i][0] != '-' && (av[i][0] < '0' || av[i][0] > '9'
				|| (av[i][0] == '0' && av[i][1])))
			return (1);
		b->number = ft_strtol(av[i], &test, 0);
		if (test == NULL || test[0] != 0 || test[0] == av[i++][0])
			return (1);
		if (av[i])
		{
			if (!(b->next = create_new_elem()))
				return (1);
			b = b->next;
		}
	}
	return (0);
}

static int			check_double(t_push_list *a)
{
	t_push_list	*b;

	while (a)
	{
		b = a->next;
		while (b)
		{
			if (a->number == b->number)
				return (1);
			b = b->next;
		}
		a = a->next;
	}
	return (0);
}

static void			free_list(t_push_list **a, t_push_list **b)
{
	t_push_list	*tmp;

	while (*a)
	{
		tmp = (*a)->next;
		free(*a);
		*a = tmp;
	}
	while (*b)
	{
		tmp = (*b)->next;
		free(*b);
		*b = tmp;
	}
}

int					main(int ac, char **av)
{
	t_push_list		*a;
	t_push_list		*b;
	t_visual		visu;

	ft_memset(&visu, 0, sizeof(t_visual));
	a = NULL;
	b = NULL;
	if (ac == 1 || check_and_fill_av(av, &a, b, &visu) || check_double(a)
		|| parse_stdin(&a, &b, &visu))
	{
		free_list(&a, &b);
		write(2, "Error\n", 6);
		return (EXIT_FAILURE);
	}
	if (verify_list(a, b))
		write(1, "KO\n", 3);
	else
		write(1, "OK\n", 3);
	if (visu.enabled || visu.ret)
		check_do_and_leave_the_visual(&visu, &a, &b);
	free_list(&a, &b);
	return (EXIT_SUCCESS);
}
