	To simply compile this program, type "make". To compile then execute this program, type "make run". To clean directory of all object files and the 
executable file, "Spell_Checker", type "make clean".
	In terms of actually running the program, the program will first ask you to enter a word. If the word matches something in the dicionary.txt file, 
the program will return and output true, and give suggestions, or all the words in the dictionary that start with the same 2 letters as your word. Also,
the execution time in micro-seconds is given. If the word does not match something in he dictionary.txt file, but has the first letter as a word in the 
dictionary, the program will ask if you mean a certain word. If the word is something you meant to type, and you enter yes, the program will return and 
output true, and give suggestions. If you enter no, then the program will return and output false. Otherwise, if your word's first letter does not 
match any of the first letter's in the dictionary.txt file, then the program will simply return false.

	Note, before I had it so that execution time was shown regardless of the case. Now I have it so that only case 1 shows execution time. I want to 
clarify this here since I don't want to lose points for not showing execution time in other cases. I am interpreting the assignment guidelines as 
showing the execution time for case 1 only. I am getting this interpretation from the bottom of the canas assignment, under the grading section. 
