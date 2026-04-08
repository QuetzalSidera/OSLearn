SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)
Target=mem

$(Target):$(OBJ)
	cc $^ -o $@

%.d: %.c
	rm -f $@; \
	$(CC) -MM $< > $@.tmp; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
	rm -f $@.tmp

%.o:%.c
	cc -c $< -o $@

.PHONY:clean
clean:
	rm -rf $(OBJ) $(DEP) $(Target)


-include $(DEP)