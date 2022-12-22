Spell_Checker.o: Spell_Checker.cpp
	g++ -c Spell_Checker.cpp

Spell_Checker: Spell_Checker.o
	g++ Spell_Checker.o -o Spell_Checker

run: Spell_Checker
	./Spell_Checker

clean:
	rm -f *.o
	rm Spell_Checker
