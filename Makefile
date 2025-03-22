C=tcc
CFLAGS=-o main.out

all:
	@echo "Build..."
	@$(C) $(CFLAGS) main.c

clean:
	@echo "Clean..."
	@rm main.out
