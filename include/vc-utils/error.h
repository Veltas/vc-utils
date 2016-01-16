/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VC_ERROR_H_INCLUDED
#define VC_ERROR_H_INCLUDED

#include <stddef.h>

// ASSERT is used to catch programming errors: things that shouldn't happen.
// e.g. ASSERT(x > 0, "x > 0 required but x = %d", x);
// Assertion failed in cstow_sqrt(), example.c line 20:
// x > 0 required but x = -3
// Program will now exit
#define ASSERT(condition, ...) \
	dynamicAssert((condition), __FILE__, __func__, __LINE__, __VA_ARGS__)

// WARNING: (variable) the expression is evaluated twice, do not put
// expressions with side effects in this argument.
// Description: Same as ASSERT but specifically for ranges
// Ensures (variable) is in range [start, end]
// e.g. BOUND(x, 0, INT_MAX/2, "value of x is %d", x);
#define BOUND(variable, start, end, ...) \
	ASSERT((variable) >= (start) && (variable) <= (end), __VA_ARGS__)

// Part of the ASSERT() mechanism
void dynamicAssert(
	int condition,
	const char *sourceFile,
	const char *functionName,
	size_t line,
	const char *formattedMessage,
	...
);

// Print an error message.
// e.g. ERROR("Problem loading config file '%s', skipped", filename);
// Would output:
// cstow: Problem loading config file '/etc/cstow', skipped\n
#define ERROR(...) \
	niceError(__VA_ARGS__)

// Part of the ERROR() mechanism
void niceError(
	const char *formattedMessage,
	...
);

#endif // VC_ERROR_H_INCLUDED
