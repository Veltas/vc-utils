/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

#include <vc-utils/Vector.h>
#include <vc-utils/error.h>

int main(void)
{
	const int testNumbers[] = {1, 2, 3, 4, 5, 6, 7};
	const size_t length = sizeof (testNumbers) / sizeof (int);

	// Test creating a new Vector
	int *testVector = Vector_alloc(sizeof (int), 0);
	ASSERT(
		Vector_size(testVector) == 0,
		"Vector_size(test) = %zu",
		Vector_size(testVector)
	);

	// Test extending and working with the Vector
	for (size_t i = 0; i < length; ++i) {
		Vector_extend(&testVector, 1);
		testVector[i] = testNumbers[i];
	}

	// Print contents
	fputs("Array : {", stdout);
	for (size_t i = 0; i < length; ++i) {
		printf("%d%c ", testVector[i], i == length - 1 ? '}' : ',');
	}
	printf("size %zu\n", Vector_size(testVector));

	// Test extending a few times more
	Vector_extend(&testVector, 80000);

	// Test freeing the vector
	Vector_free(testVector);

	return 0;
}
