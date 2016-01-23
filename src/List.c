/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <stdlib.h>

#include <vc-utils/List.h>
#include <vc-utils/error.h>

// Links are LinkInternals + dataSize bytes
// TODO: account for alignment requirements

struct LinkInternals;
typedef struct LinkInternals LinkInternals;
struct LinkInternals {
	LinkInternals *next;
};

typedef struct {
	size_t dataSize;
	void *fnState;
	InitFn dataInit;
	DestFn dataDest;
	LinkInternals *front;
} Internals;

List List_alloc(
	const size_t dataSize,
	void *fnState,
	const InitFn dataInit,
	const DestFn dataDest)
{
	// Allocate and init internals
	Internals *const internals = malloc(sizeof (Internals));
	ASSERT(internals != NULL, "malloc failed");
	*internals = (Internals){dataSize, fnState, dataInit, dataDest, NULL};

	// Return result
	return (List){internals};
}

void List_free(const List list)
{
	// Remove all list elements
	while (!Link_equal(List_front(list), NULL_LINK)) {
		List_remove(list, NULL_LINK);
	}

	// Free internals struct
	free(list.p);
}

Link List_front(const List list)
{
	Internals *const internals = list.p;

	// Return front pointer
	return (Link){internals->front};
}

Link Link_next(const Link link)
{
	LinkInternals *const linkInternals = link.p;

	// Return next pointer
	return (Link){linkInternals->next};
}

bool Link_equal(const Link l1, const Link l2)
{
	// Compare contents of the link pointer wrappers
	return !memcmp(&l1, &l2, sizeof (Link));
}

Link List_insert(
	const List list,
	const Link link,
	void *const data)
{
	Internals *const internals = list.p;

	// Allocate space for new link
	void *const newLink =
		malloc(sizeof (LinkInternals) + internals->dataSize);
	ASSERT(newLink != NULL, "malloc failed");

	// Locate internals for new, old and next link
	LinkInternals
		*const newLinkInt = newLink,
		*const oldLinkInt = link.p,
		*const nextLinkInt = oldLinkInt ? oldLinkInt->next : internals->front;

	// Update 'next'/front pointers
	if (oldLinkInt) oldLinkInt->next = newLinkInt;
	else internals->front = newLinkInt;
	newLinkInt->next = nextLinkInt;

	// Initialize data
	if (internals->dataInit)
		internals->dataInit(
			internals->fnState,
			(unsigned char *)newLinkInt + sizeof (LinkInternals),
			data
		);
	else
		memcpy(
			(unsigned char *)newLinkInt + sizeof (LinkInternals),
			data,
			internals->dataSize
		);

	// Return new link
	return (Link){newLink};
}

void List_remove(const List list, const Link link)
{
	Internals *const internals = list.p;

	// Locate internals for link and next link
	LinkInternals
		*const linkInt = link.p,
		*const nextInt = linkInt ? linkInt->next : internals->front;

	// Update next/front pointer
	if (linkInt) linkInt->next = nextInt->next;
	else internals->front = nextInt->next;

	// Destroy link's data
	if (internals->dataDest)
		internals->dataDest(
			internals->fnState,
			(unsigned char *)nextInt + sizeof (LinkInternals)
		);

	// Free link memory
	free(nextInt);
}

void *Link_get(const Link link)
{
	LinkInternals *const linkInt = link.p;
	return (unsigned char *)linkInt + sizeof (LinkInternals);
}
