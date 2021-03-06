/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:53:16 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/02 13:26:17 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isprint(int c)
{
	if (c < 0 || c > 127)
		return (0);
	if (c >= ' ' && c < 127)
		return (1);
	return (0);
}
