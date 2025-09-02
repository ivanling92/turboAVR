/**
 * TurboAVR - AVR Programming Utility
 * Version: 3.5
 * Author: Ivan Ling (2020)
 * 
 * Description:
 * TurboAVR is a streamlined utility designed to simplify the AVR development
 * workflow for students and developers working with Il Matto boards. It automates
 * the compilation, linking, hex generation, and programming process in a single
 * command-line operation.
 * 
 * Target Hardware:
 * - Il Matto board (ATmega644P microcontroller)
 * - 12MHz external crystal oscillator
 * - USB ASP programmer interface
 * 
 * Workflow:
 * 1. Parse command-line arguments for source files
 * 2. Compile C source using avr-gcc with optimized settings
 * 3. Generate ELF executable for ATmega644P
 * 4. Convert ELF to Intel HEX format
 * 5. Program the microcontroller via avrdude
 * 6. Provide user feedback and logging
 * 
 * More information about Il Matto boards:
 * https://www.ecs.soton.ac.uk/outreach/kits/micro-arcana-series
 * 
 * Usage: turboAVR source1.c [source2.c ...]
 */

#include <stdio.h>   // Standard I/O functions (printf, sprintf, etc.)
#include <windows.h> // Windows console API for colored output and screen control




/**
 * Main function - Entry point for TurboAVR
 * 
 * This function handles the complete AVR programming workflow:
 * - Validates command-line arguments
 * - Sets up console output formatting
 * - Compiles source code using avr-gcc
 * - Generates hex files using avr-objcopy
 * - Programs the microcontroller using avrdude
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @return 0 on success, non-zero on error
 */
int main( int argc, char *argv[] )  {
	
	// Windows console handling for colored output
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
	FILE *fptr;
    
    // Save current console attributes to restore later
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;    	
	
	// Buffer for building system commands
	char command[255];
	
	// Display program header with blue text
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	system("cls"); // Clear screen
	printf("********************************************\n");
	printf("Turbo AVR V3.5\n");
	printf("Created by: Ivan Ling (2020)\n");
	printf("********************************************\n");
	SetConsoleTextAttribute(hConsole, saved_attributes);
	
	// Display decorative progress indicators in yellow
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_RED);
	for(int i = 0; i<20; i++)
		printf("%c ",1); // Print decorative characters
	SetConsoleTextAttribute(hConsole, saved_attributes);		
	// Argument validation - ensure user provided source files
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE);
	if(argv[1] == NULL)
	{
		// Display error message if no arguments provided
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_INTENSITY);
		printf("\nThat's not how this works, you dumbass!");
		printf("\nRead the documentations, punk!\n");
		printf("\nHint: \n\nturboAVR yourfilename.c\n\n");
		system("@echo off");
		printf("\nTake 5 seconds to read this properly!\n");
		
		// Dramatic 5-second countdown for user to read error message
		for(int i = 0; i<5; i++)
		{
			printf("%c ",'*');
			system("sleep 1");
		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
		return 0;
	}
	
	// User interaction - ensure hardware is ready for programming
	printf("\n\nPlease make sure Il-Matto is in programming mode...\n");
	system("pause"); // Wait for user acknowledgment
	
	// Begin compilation process
	printf("\n\nCompiling codes...\n");
	system("@echo off"); // Suppress command echo
	
	int i = 0;
	printf("\n\nLinking files and begin compilation...\n");
	
	/**
	 * Build avr-gcc command with proper flags:
	 * -mmcu=atmega644p: Target ATmega644P microcontroller
	 * -DF_CPU=12000000: Define CPU frequency as 12MHz
	 * -Wall: Enable all warnings
	 * -Os: Optimize for size (important for microcontrollers)
	 */
	sprintf(command, "avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os ");
	
	// Append all source files from command line arguments
	for(i = 1; i < argc; i++)
	{
		strcat(command, argv[i]);
		strcat(command, " ");
	}
	
	// Specify output ELF file
	strcat(command, "-o prog.elf");
	printf("\nCommand is: %s\n", command);
	
	// Execute compilation
	system(command);
	printf("ELF generated...\n");
	
	// Dramatic countdown before hex generation
	printf("3 seconds till HEX loaded...\n");
	for(int i = 0; i<3; i++)
	{
		printf("%c ",'*');
		system("sleep 1");
	}
	
	// Convert ELF to Intel HEX format for programming
	printf("\nLoading HEX...\n");
	system("avr-objcopy -O ihex prog.elf prog.hex");
	
	/**
	 * Program the microcontroller using avrdude:
	 * -c usbasp: Use USB ASP programmer
	 * -p m644p: Target ATmega644P
	 * -U flash:w:prog.hex: Write hex file to flash memory
	 * 2>&1 | tee LOG.txt: Capture output to log file
	 */
	system("avrdude -c usbasp -p m644p -U flash:w:prog.hex 2>&1 | tee LOG.txt");
	system("pause"); // Allow user to review programming results
	
	// Clear screen for final message
	system("cls");
	
	/* 
	 * Legacy code for log file parsing - currently commented out
	 * This section was intended to parse and display the avrdude log
	 * but is disabled in current version
	 */
/* 	fptr = fopen("LOG.txt","r");
	char *content;
	char ch;
	int j = 0;
	while (ch != EOF)
	{
		ch = fgetc(fptr);
		content[j] = ch;
		j++;
		printf("%c ", ch);
	}
	content[j] = '\0'; */
	//printf("Hello! %s", content);
	
	// Display completion message
	printf("PROGRAMMING DONE!\n");
	printf("Do check log for status!\n");
	printf("Thank you for using TurboAVR!\n");
	
	// Restore original console attributes
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
	SetConsoleTextAttribute(hConsole, saved_attributes);
    return 0;
}