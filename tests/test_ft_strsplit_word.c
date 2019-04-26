/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strsplit_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:33:40 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	**r;

	r = ft_strsplit_word("<1>ab<1>cde<1>c", "<1>");
	FT_IS(r[0], "ab");
	FT_IS(r[1], "cde");
	FT_IS(r[2], "c");
	FT_OK(r[3] == NULL);
	free(r[0]);
	free(r[1]);
	free(r[2]);
	free(r);
	return (0);
}
