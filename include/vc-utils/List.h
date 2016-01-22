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

typedef struct { void *p; } List;

typedef struct { void *p; } Link;

#define NULL_LINK ((Link){NULL})

// List functions
//////////////////

// Allocates new List, storing data sized dataSize, with corres. init and dest
// functions (NULL for init does memcpy, NULL for dest does nothing)
List List_alloc(size_t dataSize, InitFn dataInit, DestFn dataDest);

// Frees resources used by List
void List_free(List list);

// Returns front link (or NULL_LINK if empty)
Link List_front(List list);

// Inserts link after given link (or at front if NULL_LINK is given)
// Returns newly created link
Link List_insert(List list, Link link, void *data);

// Removes a link from the list, given the PRECEDING link (NULL to remove first
// link).
void List_remove(List list, Link link);

// Link functions
//////////////////

// Returns next link given previous (or NULL_LINK if nothing after given link)
Link Link_next(Link link);

// Returns true if l1 and l2 are equal (checks addresses, not data)
bool Link_equal(Link l1, Link l2);

// Gets contents of a link
void *Link_get(Link link);

#endif // VC_LIST_H_INCLUDED
