CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/basicStrategyTrainer

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)
