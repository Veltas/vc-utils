# vc-utils  General C utilities
# Copyright (C) 2016  Christopher Leonard
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CFLAGS = -O2
prefix = /usr/local
CC = gcc

STATICS = -std=c11 -Wall -pedantic -Iinclude -Llib
LD_CMD = $(CC) $(STATICS) $(CFLAGS)
CC_CMD = $(LD_CMD) -c

SHH = >/dev/null 2>/dev/null

# Primary targets
##################
.PHONY: all
all: test lib/libvc-utils.so

# Directories
##############
bin/test lib $(prefix)/lib $(prefix)/include/vc-utils:
	mkdir -p $@

# Binary
#########
lib/libvc-utils.so: src/Vector.c src/error.c | lib
	$(LD_CMD) -fpic -shared $^ -o$@

# Test targets
###############
.PHONY: test
test: bin/test/error bin/test/Vector
	! bin/test/error $(SHH)
	bin/test/Vector $(SHH)

bin/test/error: test/error.c lib/libvc-utils.so | bin/test
	$(LD_CMD) $^ -o$@

bin/test/Vector: test/Vector.c lib/libvc-utils.so | bin/test
	$(LD_CMD) $^ -o$@

# Clean target
###############
.PHONY: clean
clean:
	-rm -r bin lib

# Install target
#################
.PHONY: install
install: lib/libvc-utils.so | $(prefix)/lib $(prefix)/include/vc-utils
	install lib/* $(prefix)/lib
	install include/vc-utils/* $(prefix)/include/vc-utils
