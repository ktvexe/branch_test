CC ?= gcc
CFLAGS ?= -Wall -std=gnu99 -g3 -DDEBUG -O0

EXEC = branch_normal branch_unlikely branch_likely branch_bitwise
.PHONY: all
all: $(EXEC)

branch_normal: branch.c
	$(CC) $(CFLAGS) \
		-o $@ -DNORMAL branch.c

branch_unlikely: branch.c
	$(CC) $(CFLAGS) \
		-o $@ -DUNLIKELY branch.c

branch_likely: branch.c
	$(CC) $(CFLAGS) \
		-o $@ -DLIKELY branch.c

branch_bitwise: branch.c
	$(CC) $(CFLAGS) \
		-o $@ -DBITWISE branch.c

branch_test: $(EXEC)
	sudo perf stat --repeat 50 -e branch-misses,branch-instructions ./branch_normal
	sudo perf stat --repeat 50 -e branch-misses,branch-instructions ./branch_unlikely
	sudo perf stat --repeat 50 -e branch-misses,branch-instructions ./branch_likely
	sudo perf stat --repeat 50 -e branch-misses,branch-instructions ./branch_bitwise
	 

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.*
