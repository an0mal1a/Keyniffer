#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
//#include <stdin.h>

//Prototipo
int startLogKey();
void Logkey();


void LogKey(){
    char c;
    while (true){
        c = _getch();
        printf("%c", c);
        if (c == 'q')
            break;
    }
}

int startLogKey(){
    LogKey();
}

int main(){
    LogKey();
}