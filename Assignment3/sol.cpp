//checked by Microsoft Visual Studio 2015 to compile. A win32 console application of type visual c++ and net framwork 4.5.2 

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])

{
	char msg1[] = "Please input the number of loops: ";
	char msg2[] = "\nThe loop will run %d times. \n";
	char msg3[] = "\nIt is not an alphabet or numeric digit. Please try again!\n";
	
	char inside_loop[] = "\nPlease input an alpha-numerical character:";
	

	char runtime[] = "\n\nLooped %d times:\n";
	
	char checkpoint[] = "/";
	
	char result1[] = "The number of lowercase characters is %d.\n";
	char result2[] = "The number of uppercase characters is %d.\n";
	char result3[] = "The number of odd numbers is %d.\n";
	char result4[] = "The number of even numbers is %d.\n";
	
	char displayodd[] = "\nOdd\n";
	char displayeven[] = "\nEven\n";
	char displayUpper[] = "\nUppercase\n";
	char displayLower[] = "\nLowercase\n";
	char displayquit[] = "\nExiting\n";
	char ending[] = "Now enter a character to quit the program: ";
	
	char f_num[] = "%d";
	char f_char[] = "%s"; //!IMPORTANT for reading without repeated output
	
	char inputing;
	
	int looptime;
	int counter=0;
	int UPaccount;
	int LOWaccount;
	int EVENamout;
	int ODDamount;
	char endp;
	
	_asm {
		
		mov UPaccount, 0
		mov LOWaccount, 0
		mov EVENamout, 0
		mov ODDamount, 0 //initialize the counters
		
		lea eax, msg1
		push eax
		call printf
		add esp, 4
		
		lea eax, looptime
		push eax
		lea eax, f_num //read loop times
		push eax
		call scanf_s
		add esp, 8 // clean stack
		
		push looptime //put loop times to stack
		lea eax, msg2 //print "The loop will run %d times"
		push eax
		call printf
		add esp, 8 // clean counter and msg2
		
		mov ecx, looptime //give eax register the loop value
		cmp ecx, 0 //check looptime 
		jle finish //exec the program if it is less than 0
		mov ecx, looptime //initialize loop counter
		loopnum: push ecx //loop count index saved on stack
		
		input:
			lea eax, inside_loop
			push eax
			call printf
			add esp, 4
			
			lea eax, inputing
			push eax
			lea eax, f_char //read user input character
			push eax 
			call scanf
			add esp, 8
			
			mov al, inputing // get ready for comparison
			
			jmp compare //the compare label is outside the loop
			
			upper:
				lea eax, displayUpper
				push eax
				call printf
				add esp, 4
				inc UPaccount//increase uppercase count
				jmp looping
			
			lower:
				lea eax, displayLower
				push eax
				call printf
				add esp, 4			
				inc LOWaccount//increase lowercase count
				jmp looping
				
			isodd:
					lea eax, displayodd
					push eax
					call printf
					add esp, 4
					inc ODDamount
					jmp looping
				
			number: //source:http://stackoverflow.com/questions/29292455/parity-of-a-number-assembly-8086
				
				shr al, 0x01 //right shift number by 1
				jc isodd;
				lea eax, displayeven
				push eax
				call printf
				add esp, 4
				inc EVENamout
				jmp looping
	
		
			quitloop:
				lea eax, displayquit
				push eax
				call printf
				add esp, 4
				jmp result	

		
			looping:
				inc counter //increase counter by 1
				pop ecx //restore loop counter ready for test
				dec ecx
				test ecx, ecx
				jnz loopnum
			
			result:	
				mov eax, counter
				push eax
				lea eax, runtime  //print "Loop ran %d times"
				push eax
				call printf
				add esp, 8
				
				mov eax, LOWaccount
				push eax // print result number				
				lea eax, result1
				push eax //print result
				call printf
				add esp, 8
				
				mov eax, UPaccount
				push eax // print result number				
				lea eax, result2
				push eax //print result
				call printf
				add esp, 8
				
				mov eax, ODDamount
				push eax // print result number				
				lea eax, result3
				push eax //print result
				call printf
				add esp, 8			
		
				mov eax, EVENamout
				push eax // print result number				
				lea eax, result4
				push eax //print result
				call printf
				add esp, 8
				
				jmp finish //jump to the end	
				
				
			compare: 
				cmp al, 47 //compar the input with '/'
				je quitloop // if it is '/',  quit the loop
				jl special// if it is a non-numeric digit, jump to the special label
				cmp al, 57 // compare the input with 9
				jle number // if it is less or equal, jump to the number label
				cmp al, 65 // compare the input with 'A'
				jl special // if it is a non-alphabet, jump to the special label
				cmp al, 90 // compare the input with 'Z'
				jle upper // if it is less or equal, jump to the upper label
				cmp al, 97 // compare the input with 'a'
				jl special; // if it is a non-alphabet, jump to the special label
				cmp al, 122 // compare the input with 'z'
				jle lower // if it is less or equal, jump to the lower label
				jg special // if it is a non-alphabet, jump to the special label
			
			special:
				lea eax, msg3
				push eax
				call printf
				add esp, 4
				jmp input

	
		
		finish: //finish
			lea eax, ending
			push eax
			call printf
			add esp, 4
			
			lea eax, endp
			push eax
			lea eax, f_char
			push eax
			call scanf_s
			add esp, 8
		
		
		
		
	}
	return 0;
}