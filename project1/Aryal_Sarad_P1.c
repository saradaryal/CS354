#include <stdio.h>

// avoid hardcoding with numeric constants for array lengths
#define MAX_BINARY_STRING_LENGTH 33
#define MAX_HEXADECIMAL_STRING_LENGTH 9

// function declarations (prototypes)
// do not change these
int Get_Number_From_User();
void Convert_Number_To_Binary(const int num,char *binary);
void Convert_Number_To_Hexadecimal(const int num, const char *binary, char *hexadecimal);

// you do not need to change main
// feel free to add additional printf statments while debugging 
// but remove them before submitting
// this is know as scaffolding and can be helpful when debugging
int main () {
    int num;
    char binary[MAX_BINARY_STRING_LENGTH];
    char hexadecimal[MAX_HEXADECIMAL_STRING_LENGTH] ;

    num = Get_Number_From_User();
    if (num > 0) {
        Convert_Number_To_Binary(num, binary);
        Convert_Number_To_Hexadecimal(num, binary, hexadecimal);
        printf("num = %d\tbinary = %s\thexadecimal = 0x%s\n",num, binary, hexadecimal);
    }
 return 0;
}
int Get_Number_From_User() {
    // replace the code below
    // use scanf to get a number from the user
    // you may assume that all input is valid

       //Declare a variable for the integer to be entered.
        int num;
        //prompt user to enter the radius 
         printf("Enter a positive integer: ");
        //assign the value entered to the address of the variable radius
        scanf("%d", &num);
        printf("\n");
    return 0;
}
void Convert_Number_To_Binary(const int num,char *binary) {
    // replace the code below
    // find a function on the internet that converts an integer
    // to a binary string and adapt it as needed 
    // cite where you copied the code from.
    // add comments to the code to indicate that you understand
    // the function you copied.
        //array          
        int n = num;i
        int i, c = 0;

        prntf("%d", num);

        for (i = sizeof(int) * 8 -1; i>=0; i--){
                n = num >> i;
                *((int)binary[i] + c) = (n&1)?'1':'0';
                c++;
        }
        *(binary+c) = NULL;
        printf("%s", binary);
        return binary;
    
    
    binary[0] = '1'; // 19 >= 16 remainder 3
    binary[1] = '0'; // 3 < 8
    binary[2] = '0'; // 3 < 4
    binary[3] = '1'; // 3 >= 2   remainder 1
    binary[4] = '1'; // 1 >= 1   remainder 0
    binary[5] = '\0';// null terminal to end the string         
 }
void Convert_Number_To_Hexadecimal(const int num, const char *binary, char *hexadecimal) {
    // replace the code below
    // find a function on the internet that converts an integer
    // to a binary string and adapt it as needed 
    // cite where you copied the code from.
    // add comments to the code to indicate that you understand
    // the function you copied.
    int i = 0;
    while (n! = 0){
        int temp = 0;

        temp = num % 16;
        if (temp < 10) {
                hexadecimal[i] = temp + 48;
                i++;
        }
        else
        {
                hexaDecimal[i] = temp + 55;
                i++;
        }
        num = num/16;
    }
    hexadecimal[0]='1';
    hexadecimal[1]='3';
    hexadecimal[2]='\0';

}
                                                              100,1         98%

                                                              1,1           Top
