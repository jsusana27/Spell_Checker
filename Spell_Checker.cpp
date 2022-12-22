#include <iostream>					/*For standard cin and cout objects*/
#include <fstream>					/*To be able to use dictionary file provided*/
#include <string>					/*For string class, to be able to use ASCII values as key for hash table*/
#include "TimeInterval.h"				/*Including header file that was again provided*/
using namespace std;					/*For convenience, since speed is not a priority for me*/

//Using my hash table code from previous assignment, just fixing data types

class Hash_Input {						/*Creating a class for the input into a hash table*/
	private:
		int key;
		string data;
		Hash_Input *next;				/*The attributes of a hash input include the key, its data, and a pointer to another entry
								  of a hash input for chaining*/
	public:
		Hash_Input() {					/*Default constructor, which initializes everything to 0 or NULL*/
			key = 0;
			data = "";
			next = NULL;
		}

		Hash_Input(int key, string data) {		/*Parameterized constructor, which initializes the key and data to their repsective
								  parameters, and still initializes the next pointer to NULL*/
			this->key = key;
			this->data = data;
			this->next = NULL;
		}

		int key_getter() {
			return key;
		}

		string data_getter() {
			return data;
		}

		Hash_Input *next_getter() {
			return next;				/*Getters, which return their repsective attributes*/
		}

		void key_setter(int key) {
			this->key = key;
		}

		void data_setter(string data) {
			this->data = data;
		}

		void next_setter(Hash_Input *next) {		/*Setters, which initialize their repsective attributes*/
			this->next = next;
		}
};



class Hash_Table {						/*Creating a class for actual hash table*/
	private:
		Hash_Input **h_table;				/*Attribute for hash table will be a pointer to a pointer, named h_table(hash table), with
								  operations and functions from the Hash_Input class*/

	public:
		Hash_Table() {					/*Default contructor, there will be no parameterized constructor*/
			h_table = new Hash_Input*[250];		/*h_table initialized to an array of 250 pointers to hash inputs on the heap, since max 
								  ASCII value of 2 lowercase numbers could be 244*/
		}

		bool search(int key, string data) {		/*Dynamic (not really for this one) operation of search*/
								/*From lecture slides, it seems that all I will need is search, insert, and delete*/
			int hash_function_answer = key;		/*Our hash function is simply key in this case, since will be first letter/ASCII value*/
			if(h_table[hash_function_answer] == NULL) {				/*If slot in hash table is empty...*/
				return false;							/*Return false, meaning first letter is not any of the first
												  letters in the dictionary*/
			}
			else {									/*Otherwise, when slot is not empty...*/
				Hash_Input *input = h_table[hash_function_answer];		/*Create a pointer with attributes and methods of Hash_Input,
												  and initialize it to slot in hash table*/
				while(input!=NULL && input->key_getter()!=key) {		/*While that pointer is not empty and its key does not equal
												  the key passed in...*/
					input = input -> next_getter(); 			/*Make that pointer equal to the next element in hash table*/
				}
				if(input == NULL) {						/*If the input is null when exiting while loop...*/
					return false;						/*Return false, meaning word is not in dictionary*/
				}
				else {
					while(input != NULL && input->data_getter()!=data) {	/*Otherwise, when input is not NULL and input's current
												  data is not the same as the data passed in*/
						input = input -> next_getter();
					}
					if (input == NULL) {
						return false;					/*If input is NULL after "second check," return false, 
												  meaning word is not in dictionary*/
					}
					return true;						/*Return true otherwise if can get through all "checkpoints"*/
				}
			}
		}

		bool search_first_letter(int key) {						/*Search function for case 2*/
			if(h_table[key] == NULL) {						/*If no first letters match, return false*/
				return false;
			}
			else {									/*Otherwise...*/
				Hash_Input *input = h_table[key];

				while(input != NULL && input->key_getter() != key) {		/*While input is not empty and first letter doesn't match...*/
					input = input -> next_getter();				/*Go to next slot/letter*/
				}
				if(input == NULL) {						/*If first letter doesn't match any slots, return false*/
					return false;
				}
				else {
					return true;						/*Otherwise, we found a match, and return true*/
				}

			}
		}

		void insert(int key, string data) {		/*Dynamic operation of insert*/
			int hash_function_answer = key;		/*Using hash function of key/10*/
			if(h_table[hash_function_answer] == NULL) {				/*If the slot is empty...*/
				h_table[hash_function_answer] = new Hash_Input(key, data);	/*Populate slot with hash input details, given to through the
												  parameters*/
			}
			else {									/*Otherwise, when slot is not empty*/
				Hash_Input *input = h_table[hash_function_answer];		/*Creating a pointer with hash input characteristics, and
												  initializing it to the current slot we are on*/
				while(input->next_getter() != NULL) {				/*While the pointer to next is not empty...*/
		//			if(input->key_getter() == key) {
		//				break;						/*If duplicate is found, break out of while loop (to fulfill
		//										//need of keeping only unique numbers)
					

				//commenting this out, because "duplicates" are what we want
					input = input->next_getter();				/*Otherwise, make pointer we created equal the next element,
												  and repeat until next pointer is NULL (if no dupilcates are
												  found)*/
				}
				if(input->next_getter() == NULL) {	/*If the next pointer is empty*/
					input->next_setter(new Hash_Input(key, data));		/*Use next setter with passed in parameters */
				}
			}
		}

		void remove(int key) {						/*Dynamic operation of remove, note that I can't use delete word since it is
									  	  of course a keyword in C++*/
			int hash_function_answer = key;				/*Using hash function of key/10*/
			if(h_table[hash_function_answer] != NULL) {		/*If the slot is not empty...*/
				Hash_Input *previous_input = NULL;		/*Create a pointer to hold previous element in chain, and initialize it to
										  NULL*/
			       	Hash_Input *input = h_table[hash_function_answer];		/*Create a pointer equal to current slot*/
				while(input->next_getter() != NULL && input->key_getter() != key) {		/*While pointer's next pointer is not empty
														  and current pointer is not equal to value
														  we want to delete*/
					previous_input = input;					/*Make previous pointer equal to current*/
					input = input->next_getter();				/*Make current equal to next*/
				}
				if(input->key_getter() == key) {				/*If current pointer equals value we want to delete*/
					Hash_Input*next_input = input->next_getter();		/*Create a pointer for next, but with characteristics of
												  hash input, and of course make it equal to next*/
					if(previous_input == NULL) {				/*If we did not have to move up the chain...*/
						delete input;					/*Delete current element*/
						h_table[hash_function_answer] = next_input;	/*Make first value in slot equal to that next pointer from
												  earlier*/
					}
					else {							/*Otherwise, when not first element*/
						delete input;					/*Delete current element*/
						previous_input->next_setter(next_input);	/*Change the previous input's next pointer information, since
												  we are deleting element "in the middle"*/
					}
				}
			}
			else {
				cout << "Your word does not exist" << endl;			/*If slot is empty, tell user their value is not
													  within the hash table*/
			}
		}

		void print_suggestions(int key, int second_letter) {		//Function to print entries of a table slot, as stated in asignment guidelines
			while(h_table[key] != NULL) {				//While table is not NULL
				string sample = h_table[key]->data_getter();	/*So we can use string library functions, current data equals string variable
										  I created */
				if(sample[1] == second_letter) {			/*If 2nd letter passed in equals 2nd letter 2nd letter in 
											  diciontary*/
					cout << h_table[key]->data_getter() << endl;	/*Print current word we are on*/
					h_table[key] = h_table[key]->next_getter();	/*Go to next word to check again*/
				}
				else {
					h_table[key] = h_table[key]->next_getter();	/*Otherwise, just go to next word*/
				}
			}
		}

		string print_when_false(int key) {				/*Suggestion print for case 2*/
			return h_table[key]->data_getter();			/*Just print 1 suggestion like the assignment guidelines says to do*/	
		}

		~Hash_Table() {							/*Destructor for hash table*/
			for(int i=0; i<200; i++) {				/*For loop for all slots of hash table*/
				if(h_table[i] != NULL) {			/*If slot in hash table is not empty...*/
					Hash_Input *previous_input = NULL;	/*Create a previous input pointer as essentially a holder*/
					Hash_Input *input = h_table[i];		/*Creata a current input pointer equal to current slot*/
					while(input != NULL) {			/*Until the current input pointer is empty...*/
						previous_input = input;		/*Make the previous input equal to current input*/
						input = input->next_getter();	/*Make the current input equal to the next input/element*/
						delete previous_input;		/*Delete the previous input that we just made equal to the "current"*/
					}
				}
			}
			delete[] h_table;					/*Delete entire table, which should be completely NULL now*/
		}

};

int main() {
	TimeInterval time_interval;			/*Creating TimeInterval object*/
	time_interval.start();				/*Starting timer*/

	ifstream input_file;				/*Declaring input file stream variable*/
	input_file.open("Dictionary.txt");		/*Opening file stream*/
	if (!input_file) {				/*If there is no input file...*/
    		cout << "Unable to open file Dictionary.txt" << endl;			
    		exit(1);  				/*Display error message and exit the program*/
	}

	Hash_Input hash_input;
	Hash_Table hash_table;				/*Creating objects for our hash input and hash table*/

	string current_word;				/*Variable for word we are on in scanning dictionary*/
	int current_key;				/*Variable for the key for the word we are on*/
	while(input_file >> current_word) {		/*While we can read the input file into our variable...*/
		if(current_word[0] == 65) {		/*ASCII value for capital A*/
			current_word[0] = 97;		/*Converting to lower case A*/
		}
		if(current_word[0] == 73) {		/*ASCII value for capital I*/
			current_word[0] = 105;		/*Converting to lower case I*/
		}
		current_key = static_cast<int>(current_word[0]);	
										/*The key simply equals the ASCII value of the first letter of the word*/
		hash_table.insert(current_key, current_word);			/*Insert word into hash table using key and actual word as parameters*/
	}

	input_file.close();				/*Closing input file stream*/

	cout << "Please enter a word:" << endl;
	string user_input;		
	cin >> user_input;				/*Getting user input for word they want to spell check*/

	int user_input_key;
	if(user_input[0] == 65) {
		user_input[0] = 97;
	}
	if(user_input[0] == 73) {
		user_input[0] = 105;			/*Converting one letter lower case letters like above*/
	}
	user_input_key = static_cast<int>(user_input[0]);	/*User's key equals ASCII value of user's first letter*/

	int result = hash_table.search(user_input_key, user_input);	/*Result equals result of search function, with user's info as parameters. Since
									  Boolean, if result equals 1, then true/match found. Otherwise (if 0), no match 
									  found*/

	if(result == 1) {
		cout << "True\n" << endl;

		cout << "Here are some suggestions:" << endl;
		hash_table.print_suggestions(user_input_key, user_input[1]);
		cout << endl;

		time_interval.stop();
		float time;						
		time = time_interval.GetInterval();
		cout << time << " micro-seconds"  << endl;		/*If match/word is found in dictionary, return true, show suggestions, and show 
									  execution time*/
	}
	else {
		int second_result;
		second_result = hash_table.search_first_letter(user_input_key);

		if(second_result == 1) {				/*If word is not found, but first letter is in dictionary*/
			string suggestion = hash_table.print_when_false(user_input_key);
			cout << "Did you mean " << suggestion << " ?" << endl;
			cout << "(For yes, enter lower case yes. Otherwise, enter anything else)" << endl;
			string choice;
			cin >> choice;					/*Print one suggestion, then ask if that's what user was looking for*/
			if(choice == "yes") {
				cout << "True\n" << endl;

				cout << "Here are some suggestions:" << endl;
				hash_table.print_suggestions(user_input_key, user_input[1]);
				cout << endl;

				time_interval.stop();				/*If they respond yes, return true and show suggestions*/
			}
			else {
				cout << "False\n" << endl;		
				time_interval.stop();				/*If they respond no, return false*/
			}
		}
		else {
			cout << "False" << endl;
			time_interval.stop();					/*If not even first letter is found in dictionary, return false*/
		}
	}
	

}
