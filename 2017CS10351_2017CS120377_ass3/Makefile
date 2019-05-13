CC=g++
CFLAGS=-g -Wall
RM=/bin/rm -f

all:	subtask1
max_pooling.o:  max_pooling.cpp
	${CC} ${CFLAGS} -c max_pooling.cpp
convolution_matrix_mult.o:  convolution_matrix_mult.cpp
	${CC} ${CFLAGS} -c convolution_matrix_mult.cpp
relu.o:  relu.cpp
	${CC} ${CFLAGS} -c relu.cpp
softmax.o:  softmax.cpp
	${CC} ${CFLAGS} -c softmax.cpp
subtask1.o:  subtask1.cpp
	${CC} ${CFLAGS} -c subtask1.cpp
subtask1:subtask1.o convolution_matrix_mult.o max_pooling.o relu.o softmax.o
	${CC} ${CFLAGS} -o subtask1 subtask1.o convolution_matrix_mult.o max_pooling.o relu.o softmax.o
	
clean:
	${RM} *.o subtask1
