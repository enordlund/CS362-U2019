CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
unitTests: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c dominion.o rngs.o
	gcc -o unitTest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unitTest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unitTest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unitTest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unitTest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)

cardTests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c dominion.o rngs.o
	gcc -o cardTest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardTest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardTest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardTest5 -g cardtest5.c dominion.o rngs.o $(CFLAGS)
	
randomtestresults: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o
	gcc -o randomTestCard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomTestCard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	gcc -o randomTestCard3 -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	./randomTestCard1 &> randomtestresults.out
	gcov dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	./randomTestCard2 &> randomtestresults.out
	gcov dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	./randomTestCard3 &> randomtestresults.out
	gcov dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
