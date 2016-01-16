/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// xarray is an extendable array, it handles managing size/capacity
// separately automatically. It manages allocated arrays as pointers
// to the arrays themselves, which makes using this in C especially
// easy.

#ifndef VC_VECTOR_H_INCLUDED
#define VC_VECTOR_H_INCLUDED

#include <stddef.h>

// Allocates new Vector with a given initial size.
// On allocation error terminates program with error message.
void *Vector_alloc(size_t elementSize, size_t initialSize);

// Frees resources for a previously allocated Vector. If given NULL, no
// action is taken. Given one of these two, provided the heap is not
// corrupted, this function will not fail.
void Vector_free(void *vector);

// Extends the Vector, given a pointer to where the array pointer is
// stored. May change the array pointer as part of reallocating array
// space. Failure results in termination of program. extendAmount is
// a count of elements, not bytes.
void Vector_extend(void *vectorPtr, size_t extendAmount);

// Returns the current size (not capacity) of a Vector (not bytes)
size_t Vector_size(const void *vector);

#endif // VC_VECTOR_H_INCLUDED
