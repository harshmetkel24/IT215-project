IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)
ODIR=obj
_DEPS=start.h user_utils.h courier_utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ= start.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# only generate executable using object files
project: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	./project

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~