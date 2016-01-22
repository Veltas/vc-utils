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

struct LinkInternals {
	struct LinkInternals *next;
};

struct Internals {
	size_t dataSize;
	InitFn dataInit;
	DestFn dataDest;
	struct LinkInternals *front;
};

struct List List_alloc(
	const size_t dataSize,
	const InitFn dataInit,
	const DestFn dataDest)
{
	// Allocate and init internals
	struct Internals *const internals = malloc(sizeof (struct Internals));
	ASSERT(internals != NULL, "malloc failed");
	*internals = (struct Internals){dataSize, dataInit, dataDest, NULL};

	// Return result
	return (struct List){internals};
}

void List_free(const struct List list)
{
	// Remove all list elements
	while (!List_Link_equal(List_front(list), NULL_LINK)) {
		List_remove(list, NULL_LINK);
	}

	// Free internals struct
	free(list.p);
}

struct List_Link List_front(const struct List list)
{
	struct Internals *const internals = list.p;

	// Return front pointer
	return (struct List_Link){internals->front};
}

struct List_Link List_Link_next(const struct List_Link link)
{
	struct LinkInternals *const linkInternals = link.p;

	// Return next pointer
	return (struct List_Link){linkInternals->next};
}

bool List_Link_equal(const struct List_Link l1, const struct List_Link l2)
{
	// Compare contents of the link pointer wrappers
	return !memcmp(&l1, &l2, sizeof (struct List_Link));
}

struct List_Link List_insert(
	const struct List list,
	const struct List_Link link,
	void *const data)
{
	struct Internals *const internals = list.p;

	// Allocate space for new link
	void *const newLink =
		malloc(sizeof (struct LinkInternals) + internals->dataSize);
	ASSERT(newLink != NULL, "malloc failed");

	// Locate internals for new, old and next link
	struct LinkInternals
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
			(unsigned char *)newLinkInt + sizeof (struct LinkInternals),
			data
		);
	else
		memcpy(
			(unsigned char *)newLinkInt + sizeof (struct LinkInternals),
			data,
			internals->dataSize
		);

	// Return new link
	return (struct List_Link){newLink};
}

void List_remove(const struct List list, const struct List_Link link)
{
	struct Internals *const internals = list.p;

	// Locate internals for link and next link
	struct LinkInternals
		*const linkInt = link.p,
		*const nextInt = linkInt ? linkInt->next : internals->front;

	// Update next/front pointer
	if (linkInt) linkInt->next = nextInt->next;
	else internals->front = nextInt->next;

	// Destroy link's data
	if (internals->dataDest)
		internals->dataDest(
			(unsigned char *)nextInt + sizeof (struct LinkInternals)
		);

	// Free link memory
	free(nextInt);
}

void *List_Link_get(const struct List_Link link)
{
	struct LinkInternals *const linkInt = link.p;
	return (unsigned char *)linkInt + sizeof (struct LinkInternals);
}
