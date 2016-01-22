/*
vc-utils  General C utilities
Copyright (C) 2016  Christopher Leonard

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vc-utils/error.h>

int main(void)
{
	ERROR("Testing ERROR()... %d\n", 666);
	BOUND(-1, 0, 5, "Testing ASSERT()/BOUND()... %d %d\n", 666, 999);
}
