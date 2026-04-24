TARGET = monitor

all: $(TARGET)

$(TARGET): ConcurrencyQueue.o monitor.o
	gcc $^ -o $@

%.o: %.c ConcurrencyQueue.h
	gcc -c $< -o $@

.PHONY: all clean

clean:
	rm -f *.o $(TARGET)