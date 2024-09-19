#include "utils.h"

t_object	*object(t_object_type type, void *element, t_attribute attrib)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->element = element;
	new->albedo = attrib.albedo;
	new->cd = attrib.cd;
	new->ksn = attrib.ksn;
	new->next = NULL;
	return (new);
}

void	oadd(t_object **list, t_object *new_obj)
{
	t_object	*cur;

	if (*list == NULL)
	{
		*list = new_obj;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new_obj;
}

t_object	*olast(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
