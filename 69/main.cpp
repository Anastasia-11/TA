#include <algorithm>

int main() {
    FILE *outputFile = fopen("output.txt", "w");
    FILE *inputFile = fopen("input.txt", "r");

    int size, value;
    fscanf(inputFile, "%i", &size);

    int* values = new int[size];
    for (int i = 0; i < size; ++i) {
        fscanf(inputFile, "%i", &value);
        values[i] = value;
    }

    switch (size) {
        case 0:
        case 2: {
            fprintf(outputFile, "%i", -1);
            break;
        }
        case 1: {
            fprintf(outputFile, "%i", values[0]);
            break;
        }
        default: {
            int* F = new int[size]{0};
            F[0] = values[0];
            F[1] = 0;
            F[2] = values[0] + values[2];
            F[3] = values[0] + values[3];

            for (int i = 2; i < size - 2; ++i) {
                F[i + 2] = std::max(F[i + 2], F[i] + values[i + 2]);
                if(i != size - 3) {
                    F[i + 3] = std::max(F[i + 3], F[i] + values[i + 3]);
                }
            }

            fprintf(outputFile, "%i", F[size - 1]);
        }

    }

    fclose(outputFile);
    fclose(inputFile);
    return 0;
}