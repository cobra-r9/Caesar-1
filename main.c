// name : main.c 
// date : 2026-06-15 
// std  : C 23 standard 
// desc : implementation of the caesar chiper 

//---------------------------------- include header files -------------------------------
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 


// define a function for formatting the flags. 

int parse_flags(char *flag) {
    // for comparing the strings, we use strcmp.
    // the signature of the function is 
    // strcmp(const char *s1, const char *s2); 
    // it loops till the reach of null terminator and compares character one by one.
    // if the strings match, then it returns 0;
    if (strcmp(flag, "--help") == 0) {
        return 0; // code for help called. 
    } else if (strcmp(flag, "--enc") == 0) {
        return 1;
    } else if (strcmp(flag, "--dec") == 0) {
        return 2;
    } else {
        return -1; // status code for error;
    }
}

//--------------------------------------- encrypt ---------------------------------------
// create a function for encryption.
// this indeed is just doing the copy of the data, no pointers needed to modify the data.
int encrypt(char *plaintext, int key) {
    printf("Chipertext : ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char p = plaintext[i];
        // printf("%c", p);
        // works clean till now. note there is no null terminator here. 
        // we don't want to store stuff, just output to stdout. so I have zero formatting headaches.
        // here comes the modulo arithemtic.
        // normalise the char.
        char n = 125; // initialise it with garbage looking ascii.
        // easy diff of error here. 
        // case 1 : when it is between A and Z.
        if (65 <= p && p <= 90) {
            n = p - 'A';
            char c = ((n + key) % 26) + 'A';
            printf("%c", c);
        // case 2 : when it is between a and z.
        } else if (97 <= p && p <= 122) {
            n = p - 'a';
            char c = ((n + key) % 26) + 'a';
            printf("%c", c);
        // case 3 : when it is between 0 and 9; (for numbers)
        } else if (48 <= p && p <= 56) {
            n = p - '0';
            // here we use mod 10 because the numbers are 0 to 9; 10 numbers. 
            // 012 to shift key = 1 will be 123;
            char c = ((n + key) % 10) + '0';
            printf("%c", c);
        } else {
            printf("%c", p);
        }

    }
    printf("\nkey : %d\n", key);
    return 0;
}

//--------------------------------------- decrypt ---------------------------------------
// create a function for decryption.
int decrypt(char *chipertext, int key) {
    printf("Plaintext : ");
    for (int i = 0; chipertext[i] != '\0'; i++) {
        char c = chipertext[i];
        // normalise the char.
        char x = 125;  
        // easy diff of error here. 
        // case 1 : when it is between A and Z.
        if (65 <= c && c <= 90) {
            x = c - 'A';
            char p = ((x - key) % 26) + 'A';
            printf("%c", p);
        // case 2 : when it is between a and z.
        } else if (97 <= c && c <= 122) {
            x = c - 'a';
            char p = ((x - key) % 26) + 'a';
            printf("%c", p);
        // case 3 : when it is between 0 and 9; (for numbers)
        } else if (48 <= c && c <= 56) {
            x = c - '0';
            char p = ((x - key) % 10) + '0';
            printf("%c", p);
        } else {
            printf("%c", c);
        }

    }
    printf("\nkey : %d\n", key);
    return 0;
}



//--------------------------------------- main program ----------------------------------
int main(int argc, char *argv[argc + 1]) {
    // we shall build this as a command line tool. 
    // we need it to pass three arguments.
    // argv[1] should be mode : which should be this --flag stuff. 
    // argv[2] should be plaintext/chipertext based on context. 
    // argv[3] should be the key. 
    // if the argc is less than 3, we need to report missing an argument. 
    // note that the first argument will take precidence.
    // if there is only one argument provided, parse_flags and check for the return value to be 0; if it is 0, the flag is help flag, and then proceed to show help.
    if (argc == 1) {
        puts("No arguments provided...(see help)");
        return EXIT_FAILURE;
        // call the help here.
    // else, if only one argument is provided, and it equals --help
    } else if (argc == 2 && parse_flags(argv[1]) == 0) {
        puts("Help Section");
        // call the help here.
    } else if (argc == 4 && parse_flags(argv[1]) == 1) {
        puts("Encryption Section");
        // check if the second arg is an int.
        // we use atoi for doing that.
        int key = atoi(argv[2]);
        // if atoi fails, then it returns 0; yet there are no way to really tell if the string 
        // passed is "0"; in our encryption case, "0" key means no ecryption which is redundant.
        // so even if we are gonna pass string "0", we should not care about it. 
        if (key == 0) {
            puts("Encryption arguments mis-positioned...(see help)");
            return EXIT_FAILURE;
        } else {
            encrypt(argv[3], key);
        }
        // we shall now do the encryption; 
    } else if (argc == 4 && parse_flags(argv[1]) == 2) {
        puts("Decryption Section");
        int key = atoi(argv[2]);
        if (key == 0) {
            puts("Decryption arguments mis-positioned...(see help)");
            return EXIT_FAILURE;
        } else {
            decrypt(argv[3], key);
        }
    } else {
        puts("Invalid usage of CLI...(see help)");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

