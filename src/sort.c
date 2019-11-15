/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:02:18 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/15 15:36:47 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		swap(t_file *p, t_file **a, t_file **b)
{
	t_file	*tmp;

	if (a == NULL || b == NULL)
		return ;
	(*a)->next = (*b)->next;
	(*b)->next = *a;
	if (p)
		p->next = *b;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void		reverse_list(t_file **list)
{
	t_file	*third;
	t_file	*second;
	t_file	*first;

	if (!list || !(first = *list) || !(first->next))
		return ;
	second = first->next;
	third = second->next;
	first->next = 0;
	second->next = first;
	while (third)
	{
		first = second;
		second = third;
		third = third->next;
		second->next = first;
	}
	*list = second;
}

void			print_list(t_file *list)
{
	while (list)
	{
		ft_printf("%s -> ", list->name);
		list = list->next;
	}
	ft_printf("\n");
}

static void		bubble_sort(t_file **list, int (*cmp)(t_file *, t_file *))
{
	int		i;
	int		end;
	t_file	*a;
	t_file	*b;
	t_file	*p;

	end = -1;
	while (42 && end != 0)
	{
		i = 0;
		p = NULL;
		a = *list;
		b = a->next;
		while (b && i++ != end)
		{
			if (cmp(a, b) > 0)
				swap(p, &a, &b);
			*list = i == 1 && *list == b ? a : *list;
			p = a;
			a = b;
			b = b->next;
		}
		end = end == -1 ? i : end - 1;
	}
}

void			sort_list(t_file **list, unsigned int flags)
{
	if (*list)
	{
		bubble_sort(list, name_cmp);
		if (flags & LSF_T)
			bubble_sort(list, time_cmp);
		if (flags & LSF_S)
			bubble_sort(list, size_cmp);
		if (flags & LSF_R)
			reverse_list(list);
	}
}
