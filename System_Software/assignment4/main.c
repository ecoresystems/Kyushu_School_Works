#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_BUFFER_SIZE 500

int csv_reader(float *adjacency_matrix) {
    FILE *fp;
    char file_name[50];
    char buf[MAX_FILE_BUFFER_SIZE] = "";
    int j = 0;

    while (1) {
        printf("Pleas specify file name [test_matrix.csv]: \n");
        fgets(&file_name[0], sizeof(file_name), stdin);
        if (file_name[0] == '\n') {
            strcpy(file_name, "test_matrix.csv");
        } else if (file_name[0] == 'e')
            return -1;
        strtok(file_name, "\n");
        if ((fp = fopen(file_name, "r")) == NULL) {      //File validation check
            printf("%s", file_name);
            printf("File could not be opened. Retry input or exit by typing 'e'\n");
        } else
            break;
    }
    if (buf == NULL) {                                  //Memory check
        printf("No memory available.\n");
        return -2;
    }
    while (fgets(buf, 255, fp) != NULL) {
        int str_length = strlen(buf);             //Get current line's length
        char temp[50] = "";
        int dec_counter = 0;
        for (int i = 0; i < str_length; i++) {
            if (buf[i] != ',' && i != (str_length - 1)) {
                temp[dec_counter] = buf[i];
                dec_counter++;
            }
            if (i == (str_length - 1)) {
                temp[dec_counter] = buf[i];
                *(adjacency_matrix + j) = atof(temp);
                memset(temp, '\0', sizeof temp);
                dec_counter = 0;
                j++;
            }
            if (buf[i] == ',') {
                *(adjacency_matrix + j) = atof(temp);
                memset(temp, '\0', sizeof temp);
                dec_counter = 0;
                j++;
            }
        }
    }
}//CSV Data Reader


void matrix_multiplication(float *A, float *B, float *C, int A_row, int A_column, int B_row, int B_column) {
    if (A_column != B_row)
        printf("Error on matrix dimension\n");
    else {
        for (int i = 0; i < A_row; i++) {
            for (int j = 0; j < B_column; j++) {
                *(C + j + i * B_column) = 0;
                for (int k = 0; k < B_row; k++) {
                    *(C + j + i * B_column) += *(A + i * A_column + k) * *(B + j + k * B_column);
                }
            }
        }
    }
}

int main() {
    float adjacency_matrix[12][12];
    char input_cmd[20];
    char cmd = '\0';
    int m, n;
    printf("Please select Adjacency matrix input method (1 for csv file input, 2 for manual input)[1]: \n");
    fgets(&input_cmd[0], sizeof(input_cmd), stdin);
    if (input_cmd[0] == '\n' || input_cmd[0] == '1') {
        int return_code = csv_reader(&adjacency_matrix[0][0]);
        if (return_code == -1) {
            printf("Program exit on user command.");
            exit(-1);
        } else if (return_code == -2) {
            printf("Exit on lack of memory");
            exit(-2);
        }
    }//File adjacency matrix input
    else {
        printf("Please input Adjacency matrix:\n");
        for (int i = 0; i < 10; i++) {
            scanf("%f %f %f %f %f %f %f %f %f %f", &adjacency_matrix[i][0], &adjacency_matrix[i][1],
                  &adjacency_matrix[i][2],
                  &adjacency_matrix[i][3], &adjacency_matrix[i][4], &adjacency_matrix[i][5], &adjacency_matrix[i][6],
                  &adjacency_matrix[i][7],
                  &adjacency_matrix[i][8], &adjacency_matrix[i][9]);
        }
    }//Manual adjacency matrix input
    while(cmd != 'e'){
        float start_vector[1][12] = {0};
        float result_vector[1][12] = {0};
        printf("Please input starting point and steps:\n");
        scanf("%d %d", &m, &n);
        start_vector[0][m] = 1;    //Initialize the start vector

        for (int i = 0; i < n; i++) {
            matrix_multiplication(&start_vector[0][0], &adjacency_matrix[0][0], &result_vector[0][0], 1, 12, 12, 12);
            memcpy(&start_vector[0][0], &result_vector[0][0], sizeof start_vector);
            printf("The next input vector is:\n");
            for (int k = 0; k < 12; k++)
                printf("%f ", start_vector[0][k]);
            printf("\n");
        }

        printf("The result vector is:\n");
        for (int i = 0; i < 12; i++)
            printf("%f ", result_vector[0][i]);
        printf("\n");
        printf("Input 'e' to exit and others to re-run:\n");
        scanf(" %c",&cmd);
    }
    return 0;
}