/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include <vc-utils/List.h>

int main(void)
{
	List list = List_alloc(sizeof (int), NULL, NULL, NULL);

	// Insert 0 at the front of the list
	Link front = List_insert(list, NULL_LINK, &(int){0});

	// Inserts 1 after
	List_insert(list, front, &(int){1});

	// Print out the values of these two links
	printf(
		"My list: {%d, %d}\n",
		*(int *)Link_get(front),
		*(int *)Link_get(Link_next(front))
	);

	// Remove these links
	List_remove(list, NULL_LINK);
	List_remove(list, NULL_LINK);

	// Free list resources
	List_free(list);
}
