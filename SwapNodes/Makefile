DEFINES:=
a.out: main.cpp
	g++ main.cpp $(DEFINES)

.PHONY: run clean test strategy1 strategy2 strategy3 strategy1_setup

run: a.out
	time ./run.sh

clean:
	rm -f a.out
	echo "" > output.txt

test: strategy1 strategy2 strategy3

strategy1_setup: clean
	$(eval DEFINES=-DSTRATEGY_1)

strategy2_setup: clean
	$(eval DEFINES=-DSTRATEGY_2)

strategy3_setup: clean
	$(eval DEFINES=-DSTRATEGY_3)

strategy1: strategy1_setup run

strategy2: strategy2_setup run

strategy3: strategy3_setup run
