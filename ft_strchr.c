/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:52:45 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 17:15:58 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	v;

	v = c;
	while (*s)
	{
		if (*s == v)
			return ((char *)s);
		s++;
	}
	return (v == '\0' ? (char *)s : NULL);
}
