/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>

#include <vc-utils/Vector.h>
#include <vc-utils/error.h>

// Data header that goes in the front of the block, followed by array
struct Data
{
	size_t elementSize, size, capacity;
};

// Converts vector pointer to block pointer (start of allocated memory)
static void *arrayToBlock(void *const array)
{
	return (unsigned char *)array - sizeof (struct Data);
}

// arrayToBlock with const qualification
static const void *arrayToBlockC(const void *const array)
{
	return (const unsigned char *)array - sizeof (struct Data);
}

// Converts block pointer to vector pointer (start of Vector array)
static void *blockToArray(void *const blockP)
{
	return (unsigned char *)blockP + sizeof (struct Data);
}

void *Vector_alloc(
	const size_t elementSize,
	const size_t initialSize)
{
	// Choose capacity
	const size_t initialCapacity = initialSize > 0 ? initialSize : 1;

	// Allocate block
	const size_t blockSize =
		sizeof (struct Data) + elementSize * initialCapacity;
	void *const blockP = malloc(blockSize);
	ASSERT(blockP != NULL, "failed to malloc %zu bytes", blockSize);

	// Initialise data
	struct Data *const data = (struct Data *)blockP;
	*data = (struct Data) {
		elementSize,
		initialSize,
		initialCapacity
	};

	// Return array
	return blockToArray(blockP);
}

void Vector_free(void *const vector)
{
	if (vector != NULL) free(arrayToBlock(vector));
}

void Vector_extend(
	void *const vectorPtr,
	const size_t extendAmount)
{
	// Check capacity
	void *blockP = arrayToBlock(*(void **)vectorPtr);
	struct Data *data = blockP;

	if (data->capacity < data->size + extendAmount) {
		// Increase size of array
		size_t targetSize;
		if (data->capacity * 2 >= data->size + extendAmount) {
			targetSize =
			sizeof (struct Data) +
			data->elementSize * data->capacity * 2;
		} else {
			targetSize =
			sizeof (struct Data) +
			(data->size + extendAmount) * data->elementSize;
		}
		blockP = realloc(blockP, targetSize);
		ASSERT(blockP != NULL, "failed realloc to %zu", targetSize);

		// Update values
		*(void **)vectorPtr = blockToArray(blockP);
		data = blockP;
		data->capacity =
		(targetSize - sizeof (struct Data)) / data->elementSize;
	}
	data->size += extendAmount;
}

size_t Vector_size(
	const void *const vector)
{
	const struct Data *const data = arrayToBlockC(vector);
	return data->size;
}
