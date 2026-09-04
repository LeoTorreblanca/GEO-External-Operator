CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -fPIC
CPPFLAGS ?= -Iinclude
LDLIBS ?= -lm

SOURCES := $(wildcard src/*.c)
TARGET := libgeo_public.so

all: $(TARGET)

$(TARGET): $(SOURCES) include/geo_engine.h include/geo_public.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -shared $(SOURCES) $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
