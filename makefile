userInterface.o: userInterface.c restaurantWaitingListSystem.h
		gcc -c userInterface.c
	
linkedListFunctions.o: linkedListFunctions.c restaurantWaitingListSystem.h
		gcc -c linkedListFunctions.c

linkedListImp.o: linkedListImp.c restaurantWaitingListSystem.h
		gcc -c linkedListImp.c

all: userInterface.o linkedListFunctions.o linkedListImp.o
		gcc userInterface.o linkedListFunctions.o linkedListImp.o -o all
		