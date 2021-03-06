#PARA ENTREGAR:
CURRENT=$(dir Makefile)
CFLAGS=-Ofast -Wall -Wextra -std=c11 -fomit-frame-pointer -march=native -I$(CURRENT)include $(OPTFLAGS)
#PARA DEBUG: 
#CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG -std=c11 -I$(CURRENT)include $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard testes/*_testes.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

INTERFACE_SRC=$(wildcard interface/*.c)
INTERFACE=$(patsubst %.c,%,$(INTERFACE_SRC))

GERADOR_SRC=$(wildcard gerador/*.c)
GERADOR=$(patsubst %.c,%,$(GERADOR_SRC))

TARGET=build/libgrafos.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) testes gerador interface

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC 
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@
$(SO_TARGET): CFLAGS += -lm
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: testes 
testes: LDLIBS += $(TARGET)
testes: $(TESTS)
	sh ./testes/testar.sh

interface: LDLIBS += $(TARGET)
interface: $(INTERFACE)

gerador: LDLIBS += $(TARGET)
gerador: $(GERADOR)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS) $(INTERFACE) $(GERADOR)
	rm -f testes/testes.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
