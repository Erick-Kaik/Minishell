/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_other.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:39:38 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/06/06 14:40:45 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_other(const char *str, char c)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (str == NULL)
		return (0);
	while (str[x] != '\0')
	{
		if (str[x] != c)
			y++;
		x++;
	}
	return (y);
}
