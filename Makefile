CC=cc
CFLAGS=-Wall
LDFLAGS=
SRCS=main.c lexer.c s.c parser.c
TARGET=pratt

$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

run: $(TARGET)
	@./$(TARGET)

.PHONY: run