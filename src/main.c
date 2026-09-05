#include <stdio.h>
#include<string.h>

char firmware_path[256] = {};

int main(int argc, char *argv[]) {
    
    // parse flags
    for(int i = 1; i < argc; i++) {
        const char * curr = argv[i];
        if(!strncmp(curr, "--firmware=", 11)) snprintf(firmware_path, sizeof(firmware_path), "%s", curr+11);
        else if(!strcmp(curr, "-f") && i+1 < argc) snprintf(firmware_path, sizeof(firmware_path), "%c", *argv[i+1]); 
        else {
            fprintf(stderr, "Invalid arguments, exiting..\n");
            return 1;
        }
    }

    //load firmware file in read mode
    if(strlen(firmware_path) == 0) {
        fprintf(stderr, "Firmware not provided, exiting..\n");
        return 1;
    } else fprintf(stderr, "Validating firmware path: %s..\n", firmware_path);

    FILE* firmware = fopen(firmware_path, "rb");
    if(!firmware) {
        fprintf(stderr, "Failed to open file, exiting..\n");
        return 1;
    } else fprintf(stderr, "Firmware successfully initialized!\nProceeding to execution pipeline.\n");

    fclose(firmware);
}