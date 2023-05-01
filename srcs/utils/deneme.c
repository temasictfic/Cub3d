#include "cub3d.h"

struct s_list
{
    void *strct;
    struct s_list *next;
}typedef t_list;

t_obj	*ft_obj_new(int x, int y, int frame)
{
	t_obj	*element;

	element = malloc (1 * sizeof(t_obj));
	if (element == NULL)
		return (NULL);
	element->x = x;
	element->y = y;
	element->frame = frame;
	//element->next = NULL; bunlar direk struct olarak init olacak
	return (element);
}

t_render	*ft_render_new(void)
{
	t_render	*element;

	element = malloc (1 * sizeof(t_render));
	if (element == NULL)
		return (NULL);
	//element->next = NULL; bunlar direk struct olarak init olacak
	return (element);
}

t_list	*list_new(void *strct)
{
	t_list	*lst;

	lst = malloc (1 * sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->strct = strct;
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
		head = ft_free(head); // strct kısmını freelemeyi unutma!
	}
	*lst = NULL;
}

void	list_remove(t_list **lst, int x, int y)
{
	t_list *prev;
	t_list *holder;
	t_obj  *obj;

	prev = *lst;
	holder = *lst;
	obj = holder->strct;
	if (holder && obj->x == x && obj->y == y)
	{
		*lst = (*lst)->next;
		holder = ft_free(holder);  // strct kısmını freelemeyi unutma!
		return;
	}
	while (holder)
	{
		obj = holder->strct;
		if (obj->x == x && obj->y == y)
		{
			prev->next = holder->next;
			holder = ft_free(holder);  // strct kısmını freelemeyi unutma!
			return;
		}
		prev = holder;
		holder = holder->next;
	}
}
