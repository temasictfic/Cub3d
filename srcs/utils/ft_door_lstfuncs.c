/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_door_lstfuncs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 23:37:49 by hel-makh          #+#    #+#             */
/*   Updated: 2023/04/15 16:53:44 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_door	*ft_door_lstnew(int x, int y, int frame)
{
	t_door	*element;

	element = malloc (1 * sizeof(t_door));
	if (element == NULL)
		return (NULL);
	element->x = x;
	element->y = y;
	element->frame = frame;
	element->next = NULL;
	return (element);
}

void	ft_door_lstadd_front(t_door **lst, t_door *new)
{
	t_door	*holder;

	holder = *lst;
	*lst = new;
	(*lst)->next = holder;
}

void	ft_door_lstdel(t_door **lst, int x, int y)
{
	t_door	*holder;
	t_door	*prev_holder;

	holder = *lst;
	prev_holder = *lst;
	if (holder && holder->x == x && holder->y == y)
	{
		*lst = (*lst)->next;
		holder = ft_free(holder);
		return ;
	}
	while (holder)
	{
		if (holder->x == x && holder->y == y)
		{
			prev_holder->next = holder->next;
			holder = ft_free(holder);
			return ;
		}
		prev_holder = holder;
		holder = holder->next;
	}
}

void	ft_door_lstclear(t_door **lst)
{
	t_door	*holder;

	if (!lst)
		return ;
	while (*lst)
	{
		holder = *lst;
		*lst = (*lst)->next;
		holder = ft_free(holder);
	}
	*lst = NULL;
}
