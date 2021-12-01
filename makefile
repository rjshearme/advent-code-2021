solve: compile
	./day_$(day)/solution.run $(part) ./day_$(day)/input_$(part).txt

compile:
	g++ -o day_$(day)/solution.run ./day_$(day)/solution.cpp

test:
	echo $(day)