#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_BUFFER_SIZE 500

int csv_reader(int *adjacency_matrix) {
    FILE *fp;
    char file_name[50];
    char buf[MAX_FILE_BUFFER_SIZE] = "";
    int j = 0;

    while (1) {
        printf("Pleas specify file name [test_matrix.csv]: \n");
        fgets(&file_name[0], sizeof(file_name), stdin);
        if (file_name[0] == '\n') {
            strcpy(file_name, "test_matrix.csv");
        }
        else if (file_name[0] == 'e')
            return -1;
        strtok(file_name, "\n");
        if ((fp = fopen(file_name, "r")) == NULL) {      //File validation check
            printf("%s", file_name);
            printf("File could not be opened. Retry input or exit by typing 'e'\n");
        }
        else
            break;
    }
    if (buf == NULL) {                                  //Memory check
        printf("No memory available.\n");
        return -2;
    }
    while (fgets(buf, 255, fp) != NULL) {
        int str_length = strlen(buf);             //Get current line's length
        for (int i = 0; i < str_length; i++) {
            if ((buf[i] >= 48) && (buf[i] <= 57)) {
                *(adjacency_matrix + j) = (buf[i] - 48);
                j++;
            }
        }
    }
}//CSV Data Reader


void matrix_multiplication(int *A, int *B, int *C, int A_row, int A_column, int B_row, int B_column) {
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
    int start_vector[1][10] = {0};
    int result_vector[1][10];
    int reachable_vector[10] = {0};
    int adjacency_matrix[10][10];
    char input_cmd[20];
    int m, n;
    printf("Please select Adjacency matrix input method (1 for csv file input, 2 for manual input)[1]: \n");
    fgets(&input_cmd[0], sizeof(input_cmd), stdin);
    if (input_cmd[0] == '\n' || input_cmd[0] == '1') {
        int return_code = csv_reader(&adjacency_matrix[0]);
        if ( return_code == -1){
            printf("Program exit on user command.");
            exit(-1);
        }
        else if (return_code == -2) {
            printf("Exit on lack of memory");
            exit(-2);
        }
    }//File adjacency matrix input
    else{
        printf("Please input Adjacency matrix:\n");
        for (int i = 0; i < 10; i++) {
            scanf("%d %d %d %d %d %d %d %d %d %d", &adjacency_matrix[i][0], &adjacency_matrix[i][1], &adjacency_matrix[i][2],
                  &adjacency_matrix[i][3], &adjacency_matrix[i][4], &adjacency_matrix[i][5], &adjacency_matrix[i][6],
                  &adjacency_matrix[i][7],
                  &adjacency_matrix[i][8], &adjacency_matrix[i][9]);
        }
    }//Manual adjacency matrix input
    printf("Please input start and end node ID:\n");
    scanf("%d %d", &m, &n);
    start_vector[0][m] = 1;    //Initialize the start vector
    reachable_vector[m] = 1; //The 0th step on the node itself

    for (int i = 0; i < 10; i++) {
        matrix_multiplication(&start_vector[0][0], &adjacency_matrix[0][0], &result_vector[0][0], 1, 10, 10, 10);
        memcpy(&start_vector[0][0], &result_vector[0][0], sizeof start_vector);
        for (int j = 0; j < 10; j++){
            if (start_vector[0][j]>0)
                reachable_vector[j]=1;
        }
    }

    printf("Reachable Vector is:\n");
    for (int i = 0; i < 10; i++)
        printf("%d ", reachable_vector[i]);
    printf("\n");

    if (reachable_vector[n] > 0)
        printf("Destination reachable\n");
    else
        printf("Destination unreachable\n");
    return 0;
}