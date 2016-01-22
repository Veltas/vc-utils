/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VC_LIST_H_INCLUDED
#define VC_LIST_H_INCLUDED

#include <stddef.h>
#include <vc-utils/defs.h>

struct List { void *p; };

struct List_Link { void *p; };

#define NULL_LINK ((struct List_Link){NULL})

// Allocates new List, storing data sized dataSize, with corres. init and dest
// functions (NULL for init does memcpy, NULL for dest does nothing)
struct List List_alloc(
	size_t dataSize,
	InitFn dataInit,
	DestFn dataDest
);

// Frees resources used by List
void List_free(struct List list);

// Returns front link (or NULL_LINK if empty)
struct List_Link List_front(struct List list);

// Returns next link given previous (or NULL_LINK if nothing after given link)
struct List_Link List_Link_next(struct List_Link link);

// Returns true if l1 and l2 are equal (checks addresses, not data)
bool List_Link_equal(
	struct List_Link l1,
	struct List_Link l2
);

// Inserts link after given link (or at front if NULL_LINK is given)
// Returns newly created link
struct List_Link List_insert(
	struct List list,
	struct List_Link link,
	void *data
);

// Removes a link from the list, given the PRECEDING link (NULL to remove first
// link).
void List_remove(struct List list, struct List_Link link);

// Gets contents of a link
void *List_Link_get(struct List_Link link);

#endif // VC_LIST_H_INCLUDED
