#include "linked_list.h"

/**
 * Create a new linked list
*/
t_list list_new(void)
{
    t_list	list;

    list.head = (t_list_node*)malloc(sizeof(t_list_node));
    list.head->next = list.head;
    list.head->prev = list.head;
    list.size = 0;
    return (list);
}

/**
 *  Add an element at the end of the list
*/
void *list_push(t_list *lst, void const *content, unsigned int content_size)
{
    t_list_node *node = (t_list_node*)malloc(sizeof(t_list_node) + content_size);
    if (node == NULL)
    {
        return (NULL);
    }
    memcpy(node + 1, content, content_size);
    node->content_size = content_size;

    t_list_node *tmp = lst->head->prev;

    lst->head->prev = node;
    tmp->next = node;

    node->prev = tmp;
    node->next = lst->head;

    lst->size++;

    return (node + 1);
}

/**
 * Add an element in head of the list
*/
void *list_add(t_list *lst, void const *content, unsigned int content_size)
{
    t_list_node *node = (t_list_node*)malloc(sizeof(t_list_node) + content_size);
    if (node == NULL)
    {
        return (NULL);
    }
    memcpy(node + 1, content, content_size);
    node->content_size = content_size;

    t_list_node *tmp = lst->head->next;

    lst->head->next = node;
    tmp->prev = node;

    node->prev = lst->head;
    node->next = tmp;

    lst->size++;

    return (node + 1);
}

/** internal list function to remove a node */
static void list_remove_node(t_list *lst, t_list_node *node)
{
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }

    node->next = NULL;
    node->prev = NULL;
    free(node);
    lst->size--;
}

/**
 * Remove first / last element of the list. Return 1 if it was removed, 0 else
*/
int list_remove_first(t_list *lst)
{
	if (lst->size == 0)
	{
		return (0);
	}
	list_remove_node(lst, lst->head->next);
	return (1);
}

int list_remove_last(t_list *lst)
{
	if (lst->size == 0)
	{
		return (0);
	}
	list_remove_node(lst, lst->head->prev);
	return (1);
}

/**
 *	remove list head
 */
void *list_pop(t_list *lst)
{
	if (lst->size == 0)
	{
		return (NULL);
	}
	
	void *data = lst->head->next + 1;
    if (lst->size > 0)
    {
		list_remove_first(lst);
    }
	return (data);
}

/** return content at the begining of the list */
void *list_head(t_list *lst)
{
    if (lst->size > 0)
    {
        return (lst->head->next + 1);
    }
    return (NULL);
}


/** remove if the comparison return elements are equals (works like strcmp) */
int  list_remove(t_list *lst, t_cmp_function cmpf, void *cmpd)
{
    t_list_node *node;

    node = lst->head->next;
    while (node != lst->head)
    {
        if (cmpf(node + 1, cmpd) == 0)
        {
            list_remove_node(lst, node);
            return (1);
        }
        node = node->next;
    }
    return (0);
}

/**
 *  Return the list node data which match with the given comparison function
 *  and reference data. (cmpf should acts like 'strcmp()')
*/
void *list_get(t_list *lst, t_cmp_function cmpf, void *cmpd)
{
	if (lst->size == 0)
	{
		return (NULL);
	}
	
	if (cmpf(lst->head + 1, cmpf) == 0)
	{
		return (lst->head);
	}
	
	t_list_node *node = lst->head->next;
    while (node != lst->head)
    {
        if (cmpf(node + 1, cmpd) == 0)
        {
            return (node + 1);
        }
        node = node->next;
    }
	
    return (NULL);
}

/**
 * Remove the node which datas match with the given comparison function
 * and the given data reference
*/
void list_delete(t_list *lst)
{
	if (lst->size == 0)
	{
		goto end;
	}
	
    t_list_node *node = lst->head->next;
    while (node != lst->head)
    {
        t_list_node *next = node->next;
        free(node);
        node = next;
    }
	free(lst->head);
	
	end:
		lst->head = NULL;
		lst->size = 0;
}


/**
 *  write the list to a file descriptor
 */
int list_to_fd(t_list *list, int fd)
{	
	//TODO
	(void)list;
	(void)fd;
    return (0);
}

/**
 *  read and return a list from the given file descriptor
*/
t_list list_from_fd(int fd)
{
	t_list lst;
	
	//TODO
	
	(void)fd;
    return (lst);
}


int main()
{
    puts("\tLINKED LIST TESTS STARTED");
	
	t_list lst = list_new();

    unsigned long int i = 0;
    unsigned long int max = 10000000;

    unsigned long int t1;
    unsigned long int t2;
    unsigned long int t;
	
	MICROSEC(t1);
    while (i < max)
    {
        list_push(&lst, "a", 2);
        ++i;
    }
	MICROSEC(t2);
	t = t2 - t1;
	
    printf("\t%-30s%lu\n", "elements pushed : ", max);
    printf("\t%-30s%lu\n", "list number of elements : ", lst.size);
    printf("\t%-30s%lf s\n", "time taken: ", t / 1000000.0f);
	
    puts("\tLINKED LIST TESTS PASSED");

	return (0);
}