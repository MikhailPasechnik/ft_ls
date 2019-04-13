/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char d0[5] = "....";
	ft_memcpy(d0, "____", 5);
	FT_TAP_ISMEM(d0, "____", 5);
	char d1[1] = "";
	ft_memcpy(d0, "____", 1);
	FT_TAP_ISMEM(d1, "", 1);
	return (0);
}
