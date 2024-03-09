// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
const int BUFFER_SIZE = 1024;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file

    int16_t buffer[BUFFER_SIZE];

    size_t samples_read;
    while((samples_read = fread(buffer, sizeof(uint16_t), BUFFER_SIZE, input)) > 0) {
        for(size_t i = 0; i < samples_read; i++){
            buffer[i] *= factor;
        }
        fwrite(buffer, sizeof(uint16_t), BUFFER_SIZE, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
