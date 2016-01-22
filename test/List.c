#include <stdio.h>
#include <stdlib.h>

#include <vc-utils/List.h>

int main(void)
{
	struct List list = List_alloc(sizeof (int), NULL, NULL);

	// Insert 0 at the front of the list
	struct List_Link front = List_insert(list, NULL_LINK, (int []){0});

	// Inserts 1 after
	List_insert(list, front, (int []){1});

	// Print out the values of these two links
	printf(
		"My list: {%d, %d}\n",
		*(int *)List_Link_get(front),
		*(int *)List_Link_get(List_Link_next(front))
	);

	// Remove these links
	List_remove(list, NULL_LINK);
	List_remove(list, NULL_LINK);

	// Free list resources
	List_free(list);
}
