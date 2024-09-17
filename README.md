# Spell Checker

A C++ spell checker program that compares input words against a dictionary and offers suggestions based on the initial letters of the word.

## Features
- Checks if the entered word exists in the dictionary.
- Provides suggestions if the word starts with the same two letters as any word in the dictionary.
- Measures and outputs the execution time for successful matches.

## Installation & Usage

### Requirements
- C++ Compiler (g++)
- Make

### How to Compile

1. Open a terminal and navigate to the project directory.
2. To compile the program, run:
   ```bash
   make
   ```

3. To compile and then execute the program, run:
   ```bash
   make run
   ```

4. To clean the directory of all object files and the executable (`Spell_Checker`), run:
   ```bash
   make clean
   ```

### How to Run

- After compiling the program, it will prompt you to enter a word.
  
  - If the word matches a word in `dictionary.txt`, the program will return `true` and provide suggestions based on the first two letters.
  - The execution time in microseconds will be displayed for successful matches.
  
- If the word does not match exactly but shares the same first letter with words in the dictionary, it will ask if you meant a specific word.
  
  - If you confirm (`yes`), the program will output `true` and provide suggestions.
  - If you do not confirm (`no`), the program will return `false`.

- If the word does not share the first letter with any word in the dictionary, the program will return `false`.

### Example Usage
```bash
Please enter a word:
were
True

Here are some suggestions:
were
we
well
went

1.65634e+06 micro-seconds
```

## Notes

- Execution time is displayed only when there is a match (case 1).
- The dictionary is stored in `Dictionary.txt`, and you can modify or expand this file with additional words if necessary.
