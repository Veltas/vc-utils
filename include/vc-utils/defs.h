/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VC_DEFS_H_INCLUDED
#define VC_DEFS_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>

// In each of these functions, state is a pointer that should be given to the
// relevant structure at allocation.

// An InitFn will initialise an object at the first pointer, as a copy of the
// object at the second pointer, and returns the first pointer.
typedef void *(*InitFn)(void *state, void *restrict, const void *restrict);

// A DestFn will destroy an object at the pointer, freeing any resources
// allocated during its life or in a Map_Init.
typedef void (*DestFn)(void *state, void *);

// An EqualFn will check to see if two given objects are considered the same.
typedef bool (*EqualFn)(void *state, const void *, const void *);

// A HashFn takes a pointer to the object, and generates a deterministic
// value based on it. Ideally the hash has good spread, and in constant time.
typedef size_t (*HashFn)(void *state, const void *);

#endif // VC_DEFS_H_INCLUDED
