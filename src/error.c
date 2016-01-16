/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <vc-utils/error.h>

void dynamicAssert(
	const int condition,
	const char *const sourceFile,
	const char *const functionName,
	const size_t line,
	const char *const formattedMessage,
	...)
{
	if (!condition) {
		fprintf(
			stderr,
			"Assertion failed in %s, %s line %zu:\n",
			functionName, sourceFile, line
		);
		va_list args;
		va_start(args, formattedMessage);
		vfprintf(stderr, formattedMessage, args);
		va_end(args);
		fputc('\n', stderr);
		exit(EXIT_FAILURE);
	}
}

void niceError(
	const char *const formattedMessage,
	...)
{
	va_list args;
	va_start(args, formattedMessage);
	vfprintf(stderr, formattedMessage, args);
	va_end(args);
	fputc('\n', stderr);
	fflush(stderr);
}
