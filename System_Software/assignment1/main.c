#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DB_NAME "db.cdb"
#define MAX_INPUT 100
#define MAX_STD_NUM 50
#define MAX_NAME_LENGTH 50
#define MAX_FILE_LENGTH 50
#define MAX_FILE_BUFFER_SIZE 500

typedef struct {
    char name[MAX_NAME_LENGTH];
    int eng_grade;
    int lan_grade;
    int math_grade;
    int total_grade;
} std;

void express_help_menu() {
    printf("i 成績の追加\n"
           "i -f ファイル入力\n"
           "i 名前 英語成績 国語成績 数学成績 省力入力\n"
           "o 集計結果表示\n"
           "o -f 集計結果ファイル出力\n"
           "o -u (-f ファイル名) 登録されている学生の名前一覧表示(ファイル出力)\n"
           "o -n 学生名 (-f ファイル名) 引数で与えた学生の成績を表示(ファイル出力)\n"
           "o -e (-f ファイル名) 英語の点数が高い方から順に、学生名とその点数を表示(ファイル出力)\n"
           "o -l (-f ファイル名) 国語の点数が高い方から順に、学生名とその点数を表示(ファイル出力)\n"
           "o -m (-f ファイル名) 数学の点数が高い方から順に、学生名とその点数を表示(ファイル出力)\n");
}

int struct_cmp_by_name(void *a, void *b) {
    std *ia = (std *const *) a;
    std *ib = (std *const *) b;
    return strcmp(ia->name, ib->name);
} //Quick sort's compare function by Name

int struct_cmp_by_en(void *a, void *b) {
    std *ia = (std *const *) a;
    std *ib = (std *const *) b;
    return (int) (ia->eng_grade - ib->eng_grade);
} //Quick sort's compare function by English

int struct_cmp_by_lan(void *a, void *b) {
    std *ia = (std *const *) a;
    std *ib = (std *const *) b;
    return (int) (ia->lan_grade - ib->lan_grade);
} //Quick sort's compare function by lananese

int struct_cmp_by_ma(void *a, void *b) {
    std *ia = (std *const *) a;
    std *ib = (std *const *) b;
    return (int) (ia->math_grade - ib->math_grade);
} //Quick sort's compare function by Math

int struct_cmp_by_total(void *a, void *b) {
    std *ia = (std *const *) a;
    std *ib = (std *const *) b;
    return (int) (ia->total_grade - ib->total_grade);
} //Quick sort's compare function by Total Grade

int csv_reader(char *file_name, int *pstd_count, std *pstd_info) {
    FILE *fp;
    char buf[MAX_FILE_BUFFER_SIZE] = "";
    char std_name[MAX_NAME_LENGTH] = "";
    char temp[MAX_NAME_LENGTH] = "";
    int en_grade, lan_grade, b_point, ma_grade,counter;

    counter = *pstd_count;

    if (buf == NULL)                                  //Memory check
        printf("No memory available.\n");

    if ((fp = fopen(file_name, "r")) == NULL)      //File validation check
        printf("File could not be opened.\n");

    while (fgets(buf, 255, fp) != NULL) {
        int str_length = strlen(buf);             //Get current line's length

        for (int i = 0; i < str_length; i++) {
            if (buf[i] != ',')
                std_name[i] = buf[i];
            else {
                b_point = i + 1;
                break;
            }
        }                                         //Extracting name

        for (int i = b_point; i < str_length; i++) {
            if (buf[i] != ',')
                temp[i - b_point] = buf[i];
            else {
                b_point = i + 1;
                en_grade = atoi(temp);
                break;
            }
        }                                       //Extracting English grade

        for (int i = b_point; i < str_length; i++) {
            if (buf[i] != ',')
                temp[i - b_point] = buf[i];
            else {
                b_point = i + 1;
                lan_grade = atoi(temp);
                break;
            }
        }                                     //Extracting language grade

        for (int i = b_point; i < str_length + 2; i++) {
            if (buf[i] != '\n')
                temp[i - b_point] = buf[i];
            else {
                ma_grade = atoi(temp);
                break;
            }
        }                                    //Extracting Math grade

        strcpy(pstd_info[*pstd_count].name,
               std_name);                            //Write current line's data into struct
        pstd_info[*pstd_count].eng_grade = en_grade;
        pstd_info[*pstd_count].lan_grade = lan_grade;
        pstd_info[*pstd_count].math_grade = ma_grade;
        pstd_info[*pstd_count].total_grade = en_grade + lan_grade + ma_grade;
        *pstd_count += 1;                           //Student count +1
        memset(std_name, 0,
               strlen(std_name));                   //Clean up temporary std_name
        memset(buf, 0,
               strlen(buf));                        //Clean up temporary buffer
    }
    fclose(fp);                                     //Some Clean Up work
    counter = *pstd_count - counter;
    printf("%d人の成績を登録しました\n",counter);
    return 1;
}//CSV Data Reader

void interactive_data_input(int *pstd_count, std *pstd_info) {
    printf("%d人目の成績を入力してください\n", *pstd_count + 1);
    printf("名前:");
    scanf("%s", pstd_info[*pstd_count].name);
    printf("英語:");
    scanf("%d", &pstd_info[*pstd_count].eng_grade);
    printf("国語:");
    scanf("%d", &pstd_info[*pstd_count].lan_grade);
    printf("数学:");
    scanf("%d", &pstd_info[*pstd_count].math_grade);
    printf("%d人目の成績を登録しました\n", *pstd_count + 1);
    pstd_info[*pstd_count].total_grade =
            pstd_info[*pstd_count].eng_grade + pstd_info[*pstd_count].lan_grade + pstd_info[*pstd_count].math_grade;
    *pstd_count += 1;
}//Interactive Data Input Module

void qck_data_input(char *src_str, int str_length, int *pstd_count, std *pstd_info) {
    char std_name[20] = "";                                         //Initialize some essential local variable
    char temp[20] = "";
    int en_grade, lan_grade, b_point, ma_grade;

    for (int i = 0; i < str_length; i++) {
        if ((src_str[i + 1] < 48) || (src_str[i + 1] > 57))
            std_name[i] = src_str[i];
        else {
            b_point = i + 1;
            break;
        }
    }//Get the name

    for (int i = b_point; i < str_length; i++) {
        if (src_str[i] != ' ')
            temp[i - b_point] = src_str[i];
        else {
            b_point = i + 1;
            en_grade = atoi(temp);
            break;
        }
    }//Get English Grade

    for (int i = b_point; i < str_length; i++) {
        if (src_str[i] != ' ')
            temp[i - b_point] = src_str[i];
        else {
            b_point = i + 1;
            lan_grade = atoi(temp);
            break;
        }
    }//Get language Grade

    for (int i = b_point; i < str_length + 2; i++) {
        if (src_str[i] != '\n')
            temp[i - b_point] = src_str[i];
        else {
            ma_grade = atoi(temp);
            break;
        }
    }//Get Math Grade

    strcpy(pstd_info[*pstd_count].name, std_name);           //Data Injection
    pstd_info[*pstd_count].eng_grade = en_grade;
    pstd_info[*pstd_count].lan_grade = lan_grade;
    pstd_info[*pstd_count].math_grade = ma_grade;
    pstd_info[*pstd_count].total_grade = en_grade + lan_grade + ma_grade;
    *pstd_count += 1;
    printf("%d人目の成績を登録しました\n", *pstd_count);
}//Quick data input module

void sorting_module(int *pstd_count, std *pstd_info, char opt) {
    switch (opt) {
        case 'e'://Ascend order by English grade
            qsort(pstd_info, *pstd_count, sizeof(std), struct_cmp_by_en);
            break;
        case 'l'://Ascend order by language grade
            qsort(pstd_info, *pstd_count, sizeof(std), struct_cmp_by_lan);
            break;
        case 'm'://Ascend order by math grade
            qsort(pstd_info, *pstd_count, sizeof(std), struct_cmp_by_ma);
            break;
        case 't'://Ascend order by total grade
            qsort(pstd_info, *pstd_count, sizeof(std), struct_cmp_by_total);
            break;
        case 'n'://Ascend order by name
            qsort(pstd_info, *pstd_count, sizeof(std), struct_cmp_by_name);
            break;
        default://Error option
            printf("Sort option error.\n");
    }
}//Sorting function selector(e,l,m,t,n)

void statistics_module(int *pstd_count, std *pstd_info, float *pstats_data, short f_flag, char *file_name) {
    int eng_sum = 0;
    int lan_sum = 0;
    int math_sum = 0;
    float en_avg, lan_avg, ma_avg, total_avg, en_stdev, lan_stdev, ma_stdev, total_stdev;
    float sq_dev = 0;                                                               //Initiating required local variable

    for (int i = 0; i < *pstd_count; i++)                                              //Calculating sum of each subject
        eng_sum += pstd_info[i].eng_grade;

    for (int i = 0; i < *pstd_count; i++)
        lan_sum += pstd_info[i].lan_grade;

    for (int i = 0; i < *pstd_count; i++)
        math_sum += pstd_info[i].math_grade;

    en_avg = (float) eng_sum / *pstd_count;                                  //Calculating average grade of each subject
    lan_avg = (float) lan_sum / *pstd_count;
    ma_avg = (float) math_sum / *pstd_count;

    total_avg = en_avg + lan_avg + ma_avg;                                            //Calculating total average by add

    for (int i = 0; i < *pstd_count; i++) {                              //Calculating each subject's standard deviation
        sq_dev += pow((float) (pstd_info[i].eng_grade - en_avg), 2);
    }
    en_stdev = sqrt(sq_dev / (float) *pstd_count);
    sq_dev = 0;

    for (int i = 0; i < *pstd_count; i++) {
        sq_dev += pow((float) (pstd_info[i].lan_grade - en_avg), 2);
    }
    lan_stdev = sqrt(sq_dev / (float) *pstd_count);
    sq_dev = 0;

    for (int i = 0; i < *pstd_count; i++) {
        sq_dev += pow((float) (pstd_info[i].math_grade - en_avg), 2);
    }
    ma_stdev = sqrt(sq_dev / (float) *pstd_count);
    sq_dev = 0;

    for (int i = 0; i < *pstd_count; i++) {
        sq_dev += pow((float) (pstd_info[i].total_grade - total_avg), 2);
    }
    total_stdev = sqrt(sq_dev / (float) *pstd_count);

    *pstats_data = en_avg;                                                         //Write results into statistic matrix
    *(pstats_data + 1) = lan_avg;
    *(pstats_data + 2) = ma_avg;
    *(pstats_data + 3) = total_avg;
    *(pstats_data + 4) = en_stdev;
    *(pstats_data + 5) = lan_stdev;
    *(pstats_data + 6) = ma_stdev;
    *(pstats_data + 7) = total_stdev;

    sorting_module(pstd_count, pstd_info, 'e');                                //Find min and max score for each subject
    *(pstats_data + 8) = pstd_info[0].eng_grade;                                  //and write them into statistic matrix
    *(pstats_data + 12) = pstd_info[*pstd_count - 1].eng_grade;

    sorting_module(pstd_count, pstd_info, 'l');
    *(pstats_data + 9) = pstd_info[0].lan_grade;
    *(pstats_data + 13) = pstd_info[*pstd_count - 1].lan_grade;

    sorting_module(pstd_count, pstd_info, 'm');
    *(pstats_data + 10) = pstd_info[0].math_grade;
    *(pstats_data + 14) = pstd_info[*pstd_count - 1].math_grade;

    sorting_module(pstd_count, pstd_info, 't');
    *(pstats_data + 11) = pstd_info[0].total_grade;
    *(pstats_data + 15) = pstd_info[*pstd_count - 1].total_grade;

    if (f_flag == 1) {                                                //Write result into file if it is required by user
        FILE *fp;
        if ((fp = fopen(file_name, "w+")) == NULL) {
            printf("Cannot open file to write.\n");
        }
        for (int i = 0; i < *pstd_count; i++) {
            fprintf(fp, "%s,%d,%d,%d\n", pstd_info[i].name, pstd_info[i].eng_grade, pstd_info[i].lan_grade,
                    pstd_info[i].math_grade);
        }
        fclose(fp);
        printf("%s　ファイルに出力しました\n", file_name);
    }

    printf("---　成績一覧　---\n");
    printf("登録者数　:　%d　人\n", *pstd_count);
    printf("　　　　　　　　英語　 　国語 　　数学  　　合計\n");

    printf("　　平均　:");
    for (int i = 0; i < 4; i++)
        printf("　 %3.1f点", *(pstats_data + i));

    printf("\n　最高点　:");
    for (int i = 12; i < 16; i++) {
        if (i == 15)
            printf(" ");
        printf("　 %4d点", (int) *(pstats_data + i));
    }

    printf("\n　最低点　:");
    for (int i = 8; i < 12; i++) {
        if (i == 11)
            printf(" ");
        printf("　 %4d点", (int) *(pstats_data + i));
    }
    printf("\n標準偏差　:");
    for (int i = 4; i < 8; i++) {
        if (i == 7)
            printf(" ");
        printf("　  %4.2f", *(pstats_data + i));
    }
    printf("\n");

}

void output_generator(short file_flag, char *file_name, char *pstd_name, int *pstd_count, std *pstd_info,
                      int option) {
    short true_name_len;
    switch (option) {
        case 16://Printing out specified student
            for (int i = 0; i < *pstd_count; i++) {
                if (strcmp(pstd_info[i].name, pstd_name) == 0) {

                    if (file_flag == 1) {
                        FILE *fp;
                        fp = fopen(file_name, "w+");
                        fprintf(fp, "名前,英語,国語,数学\n");
                        fprintf(fp, "%s,%d,%d,%d", pstd_info[i].name, pstd_info[i].eng_grade, pstd_info[i].lan_grade,
                                pstd_info[i].math_grade);
                        fclose(fp);
                        printf("%s　ファイルに出力しました\n", file_name);
                    } else {
                        printf("名前");
                        true_name_len = strlen(pstd_info[i].name);
                        if ((true_name_len % 2) == 0) {
                            for (int j = 0; j < true_name_len; j++) {
                                printf(" ");
                            }
                        } else {
                            for (int j = 0; (j < true_name_len - 1); j++) {
                                printf(" ");
                            }
                        }

                        printf("英語　　数学　　国語　　 合計\n");
                        printf("%s", pstd_info[i].name);
                        if ((true_name_len % 2) == 0) {
                            printf("  ");
                        } else {
                            printf(" ");
                        }
                        printf("%4d点　%4d点　%4d点　 %4d点\n", pstd_info[i].eng_grade, pstd_info[i].lan_grade,
                               pstd_info[i].math_grade, pstd_info[i].total_grade);
                    }
                }
            }
            break;

        case 8:                                                                               //Print out logged student
            sorting_module(pstd_count, pstd_info, 'n');
            if (file_flag == 1) {
                FILE *fp;
                fp = fopen(file_name, "w+");
                fprintf(fp, "名前\n");
                for (int i = 0; i < *pstd_count; i++)
                    fprintf(fp, "%s\n", pstd_info[i].name);
                fclose(fp);
                printf("%s　ファイルに出力しました\n", file_name);
            } else {
                printf("登録学生一覧\n");
                for (int i = 0; i < *pstd_count; i++) {
                    printf("%s\n", pstd_info[i].name);
                }
            }
            break;

        case 4:                                              //Print out student name and english grade by descend order
            sorting_module(pstd_count, pstd_info, 'n');
            true_name_len = strlen(pstd_info[*pstd_count - 1].name);
            sorting_module(pstd_count, pstd_info, 'e');
            if (file_flag == 1) {
                FILE *fp;
                fp = fopen(file_name, "w+");
                fprintf(fp, "--- 英語の成績 ---\n登録者数: %d人\n名前,点数\n", *pstd_count);
                for (int i = *pstd_count - 1; i >= 0; i--)
                    fprintf(fp, "%s %d\n", pstd_info[i].name, pstd_info[i].eng_grade);
                fclose(fp);
                printf("%s　ファイルに出力しました\n", file_name);
            } else {
                printf("--- 英語の成績 ---\n登録者数　:　%d人\n", *pstd_count);
                printf("名前");
                if ((true_name_len % 2) == 0) {
                    for (int j = 0; j < true_name_len; j++) {
                        printf(" ");
                    }
                } else {
                    for (int j = 0; (j < true_name_len - 1); j++) {
                        printf(" ");
                    }
                }
                printf("　点数\n");
                for (int i = *pstd_count - 1; i >= 0; i--)
                    printf("%-*s %3d点\n", (true_name_len + 4), pstd_info[i].name, pstd_info[i].eng_grade);
            }
            break;

        case 2:
            sorting_module(pstd_count, pstd_info, 'n');
            true_name_len = strlen(pstd_info[*pstd_count - 1].name);
            sorting_module(pstd_count, pstd_info, 'l');
            if (file_flag == 1) {
                FILE *fp;
                fp = fopen(file_name, "w+");
                fprintf(fp, "--- 国語の成績 ---\n登録者数: %d人\n名前,点数\n", *pstd_count);
                for (int i = *pstd_count - 1; i >= 0; i--)
                    fprintf(fp, "%s %d\n", pstd_info[i].name, pstd_info[i].lan_grade);
                fclose(fp);
                printf("%s　ファイルに出力しました\n", file_name);
            } else {
                printf("--- 国語の成績 ---\n登録者数　:　%d人\n", *pstd_count);
                printf("名前");
                if ((true_name_len % 2) == 0) {
                    for (int j = 0; j < true_name_len; j++) {
                        printf(" ");
                    }
                } else {
                    for (int j = 0; (j < true_name_len - 1); j++) {
                        printf(" ");
                    }
                }
                printf("　点数\n");
                for (int i = *pstd_count - 1; i >= 0; i--)
                    printf("%-*s %3d点\n", (true_name_len + 4), pstd_info[i].name, pstd_info[i].lan_grade);
            }
            break;

        case 1:
            sorting_module(pstd_count, pstd_info, 'n');
            true_name_len = strlen(pstd_info[*pstd_count - 1].name);
            sorting_module(pstd_count, pstd_info, 'm');
            if (file_flag == 1) {
                FILE *fp;
                fp = fopen(file_name, "w+");
                fprintf(fp, "--- 数学の成績 ---\n登録者数: %d人\n名前,点数\n", *pstd_count);
                for (int i = *pstd_count - 1; i >= 0; i--)
                    fprintf(fp, "%s %d\n", pstd_info[i].name, pstd_info[i].math_grade);
                fclose(fp);
                printf("%s　ファイルに出力しました\n", file_name);
            } else {
                printf("--- 数学の成績 ---\n登録者数　:　%d人\n", *pstd_count);
                printf("名前");
                if ((true_name_len % 2) == 0) {
                    for (int j = 0; j < true_name_len; j++) {
                        printf(" ");
                    }
                } else {
                    for (int j = 0; (j < true_name_len - 1); j++) {
                        printf(" ");
                    }
                }
                printf("　点数\n");
                for (int i = *pstd_count - 1; i >= 0; i--)
                    printf("%-*s %3d点\n", (true_name_len + 4), pstd_info[i].name, pstd_info[i].math_grade);
            }
            break;

        default:
            printf("Too many input arguments.\n");
    }

}

int input_parser(int *pstd_count, std *pstd_info, float *pstats_data) {
    char input[MAX_INPUT] = "";
    char usr_input[MAX_INPUT - 2] = "";
    short length;
    char file_name[MAX_FILE_LENGTH] = "";
    char std_name[MAX_NAME_LENGTH] = "";
    short f_flag = 0;
    short subcmd = 0;

    printf(":");
    fgets(input, MAX_INPUT, stdin);
    length = strlen(input) - 1;

    if (input[0] ==
        'i') {                                                                                            //Option for i
        if (length > 1) {
            if (input[2] == '-' && input[3] == 'f') {
                for (int i = 5; i < length; i++) {
                    file_name[i - 5] = input[i];
                }                                                                                        //Get File Name

                csv_reader(&file_name, pstd_count, pstd_info);                                  //Load File Input Module
            } else {
                strcpy(usr_input,
                       input + 2);                                                                 //choke input command
                qck_data_input(&usr_input, length - 2, pstd_count, pstd_info);
            }  //Load Quick Data Input Module
        } else {
            interactive_data_input(pstd_count, pstd_info);
            getchar();
        }//Load Interactive Data Input Module
    }

    if (input[0] == 'q')
        return 1;//Exit Program Upon signal 1

    if (input[0] == 'h') {
        FILE *fp;
        char buf[200] = "";
        printf("\n");
        if (buf ==
            NULL) {                                                                                 //Memory check
            printf("No memory available. Switching to Streamlined help mode\n");
            express_help_menu();
        }

        if ((fp = fopen("help.txt", "r")) == NULL) {      //File validation check
            printf("Help file doesn't exist or could not be opened. Switching to Streamlined help mode\n");
            express_help_menu();
        }

        while (fgets(buf, 255, fp) != NULL)
            printf("%s", buf);

        free(buf);                                                                                      //Some Clean Up work
        fclose(fp);
    }

    if (input[0] == 'o') {
        if (length > 1) {
            for (short index = 1; index < length; index++) {
                if (input[index] == '-' && input[index + 1] == 'f') {
                    f_flag = 1;                                                         //File output option set to true
                    for (int i = index + 3; i <= length; i++) {
                        if (input[i] != ' ' && input[i] != '\n')
                            file_name[i - (index + 3)] = input[i];
                        else
                            break;
                    } //Get File Name
                } else if (input[index] == '-' && input[index + 1] == 'n') {
                    for (int i = index + 3; i < length; i++) {
                        if (input[i] != '\0') {
                            if (input[i] == ' ' && input[i + 1] == '-')
                                break;
                            else {
                                std_name[i - (index + 3)] = input[i];
                            }

                        } else
                            break;

                    } //Get student name

                    subcmd |= 16;                                              //Specific student option available: 0x10
                } else if (input[index] == '-' && input[index + 1] == 'u') {
                    subcmd |= 8;
                }                                                                              //List All Students: 0x08

                else if (input[index] == '-' && input[index + 1] == 'e') {
                    subcmd |= 4;
                }                                                           //List all English Grades in Dec Order: 0x04

                else if (input[index] == '-' && input[index + 1] == 'l') {
                    subcmd |= 2;
                }                                                          //List all language Grades in Dec Order: 0x02

                else if (input[index] == '-' && input[index + 1] == 'm') {
                    subcmd |= 1;
                }                                                              //List all Math Grades in Dec Order: 0x01
            }

            if (subcmd == 0)
                statistics_module(pstd_count, pstd_info, pstats_data, 1,
                                  file_name);//Load Statistics Module with file output
            else
                output_generator(f_flag, file_name, std_name, pstd_count, pstd_info, subcmd);//Initiating output
        } else {
            statistics_module(pstd_count, pstd_info, pstats_data, 0, NULL);
        }//Load Statistics Module without file output

    }
    printf(" \n");
}

int db_saver(int *pstd_count, std *pstd_info) {
    FILE *fp;
    if ((fp = fopen(DB_NAME, "w+")) == NULL) {
        printf("DB writable Error (Permission problem maybe?)");
        return 9990;
    }

    for (int i = 0; i < *pstd_count; i++) {
        fprintf(fp, "%s,%d,%d,%d\n", pstd_info[i].name, pstd_info[i].eng_grade, pstd_info[i].lan_grade,
                pstd_info[i].math_grade);
    }
    fclose(fp);
    printf("Data saved");
}

int main() {
    int std_count = 0;
    float stats_data[4][4];//4X4 Statistical Data Array: AVG, MAX, MIN, STDEV
    std std_info[MAX_STD_NUM];
    if (csv_reader(DB_NAME, &std_count, &std_info) == 1) {
        printf("%d students data successfully loaded\n", std_count);
        system("clear");
    }
    printf("q: 終了\nh: ヘルプ\n\n");
    while (1) {
        if (input_parser(&std_count, &std_info, &stats_data))
            break;
    }
    if (db_saver(&std_count, &std_info) == 9990)
        printf("DB save error\n");

    return 0;
}