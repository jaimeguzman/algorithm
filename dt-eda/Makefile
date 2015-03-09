CC = g++

DEBUG = 
OPT = -O3 -foptimize-sibling-calls -funroll-all-loops

FLAG = -c -Wall $(DEBUG) $(OPT)
LFLAG = -lm $(DEBUG) $(OPT)

OBJS = \
	bisection.o \
	eda.o \
	heap.o \
	main.o \
	MT.o \
	obj-function.o \
	parse-input.o \
	random.o \
	stats.o \
	status.o \
	tree-model.o

dt-eda: $(OBJS)
	$(CC) -o dt-eda $(OBJS) $(LFLAG)

bisection.o: bisection.cpp
	$(CC) $(FLAG) bisection.cpp 

eda.o: eda.cpp
	$(CC) $(FLAG) eda.cpp

heap.o: heap.cpp
	$(CC) $(FLAG) heap.cpp

main.o: main.cpp
	$(CC) $(FLAG) main.cpp

MT.o: MT.cpp
	$(CC) $(FLAG) MT.cpp

obj-function.o: obj-function.cpp
	$(CC) $(FLAG) obj-function.cpp

parse-input.o: parse-input.cpp
	$(CC) $(FLAG) parse-input.cpp

random.o: random.cpp
	$(CC) $(FLAG) random.cpp

stats.o: stats.cpp
	$(CC) $(FLAG) stats.cpp

status.o: status.cpp
	$(CC) $(FLAG) status.cpp

tree-model.o: tree-model.cpp
	$(CC) $(FLAG) tree-model.cpp

clean: 
	@rm -f $(OBJS) dt-eda dt-eda.exe

all:
	@make clean
	@make dt-eda
