/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:11:01 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/06 05:49:27 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_obj	*obj_new(int x, int y, int frame)
{
	t_obj	*element;

	element = malloc(1 * sizeof(t_obj));
	if (element == NULL)
		return (NULL);
	element->x = x;
	element->y = y;
	element->frame = frame;
	return (element);
}

t_list	*list_new(void *obj)
{
	t_list	*lst;

	lst = malloc(1 * sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->obj = obj;
	lst->next = NULL;
	return (lst);
}

void	list_add_front(t_list **lst, t_list *new)
{
	t_list	*head;

	head = *lst;
	*lst = new;
	(*lst)->next = head;
}

void	list_clear(t_list **lst)
{
	t_list	*head;

	if (!lst)
		return ;
	while (*lst)
	{
		head = *lst;
		*lst = (*lst)->next;
		ft_free(head->obj);
		head = ft_free(head);
	}
	*lst = NULL;
}

void	list_remove(t_list **lst, int x, int y)
{
	t_list	*prev;
	t_list	*cur;

	prev = *lst;
	cur = *lst;
	if (cur && ((t_obj *)(cur->obj))->x == x && ((t_obj *)(cur->obj))->y == y)
	{
		*lst = (*lst)->next;
		ft_free((t_obj *)(cur->obj));
		cur = ft_free(cur);
		return ;
	}
	while (cur)
	{
		if (((t_obj *)(cur->obj))->x == x && ((t_obj *)(cur->obj))->y == y)
		{
			prev->next = cur->next;
			ft_free((t_obj *)(cur->obj));
			cur = ft_free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
