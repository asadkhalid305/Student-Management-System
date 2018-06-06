/* 
 * File:   main.c
 * Author: HC
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//roll number for all search purpose
int rollNumber;

//defining linkedlist (struct)
struct list {
    char firstName[20];
    char lastName[20];
    int rollNumber;
    char semester[10];
    struct list *link;
} *start = NULL;

//************************************************OUT OF MENU FUNCTIONS START**********************************************************************//
//transfer data from linkedlist to file
int LoadLinkedlistToFile() {
    FILE *fp;
    fp = fopen("file.txt", "w");
    struct list *newNode;

    newNode = start;
    if (start == NULL) {
        return 0;
    } else {
        while (newNode != NULL) {
            fprintf(fp, "%s\n", newNode->firstName);
            fprintf(fp, "%s\n", newNode->lastName);
            fprintf(fp, "%d\n", newNode->rollNumber);
            fprintf(fp, "%s\n", newNode->semester);

            newNode = newNode->link;
        }
    }
    fclose(fp);
}

//transfer data from file to linkedlist
int LoadLinkedlistFromFile() {
    FILE *fp;
    fp = fopen("file.txt", "r");
    
    while (!feof(fp)) {
        struct list *new_Node, *current;
        new_Node = (struct list *) malloc(sizeof (struct list));
        if (fscanf(fp, "%s", new_Node->firstName) != EOF) {
            fscanf(fp, "%s", new_Node->lastName);
            fscanf(fp, "%d", &new_Node->rollNumber);
            fscanf(fp, "%s", new_Node->semester);
            new_Node->link = NULL;

            if (start == NULL) {
                start = new_Node;
                current = new_Node;
            } else {
                current->link = new_Node;
                current = new_Node;
            }
        }
    }
    free(fp);
    fclose(fp);
}

//display all data which is present in linkedlist currently
int LinkedlistDisplay() {
    struct list *new_Node;
    printf("All Record : \n");
    new_Node = start;
    if (start == NULL) {
        printf("There is no record!\n");
    } else {
        while (new_Node != NULL) {
            printf("======================================================================================\n");
            printf("Name:     %s %s\n", new_Node->firstName, new_Node->firstName);
            printf("Roll-No:  %d\n", new_Node->rollNumber);
            printf("semester:    %s\n", new_Node->semester);

            new_Node = new_Node->link;
        }
    }
}

//**********************************************OUT OF MENU FUNCTIONS END**********************************************************//

//***********************************************MAIN PROGRAM STARTS*********************************************************//

//display home menu
int DisplayHomeMenu() {
    printf("*********************HOME*********************\n");
    printf("Enter Data 	- Press n\n");
    printf("Search Data  	- Press s\n");
    printf("Replace Data  	- Press r\n");
    printf("Delete Data  	- Press d\n");
    printf("Edit Data  	- Press e\n");
    printf("Load All Data  	- Press l\n");
    printf("Exit     	- Press x\n");
}

//this is the function for checking roll number if it is already exists in database (file)
int SearchEntryConditionInNewEntry(int roll_Num) {
    struct list *new_Node;
    new_Node = start;
    if (new_Node == NULL) {
        return 0;
    } else {
        while (new_Node != NULL) {
            if (new_Node->rollNumber == roll_Num) {
                if (new_Node == start) {
                    return 1;
                } else {
                    return 1;
                }
            } else {
                new_Node = new_Node->link;
            }
        }
    }
    return 0;
}

//to enter new entry in database. It can take multiple data at a time
int NewEntry() {
    LoadLinkedlistFromFile();
    int r_no;
    int a;
    printf("Enter Roll Number: ");
    scanf("%d", &r_no);
    a = SearchEntryConditionInNewEntry(r_no);
    
    if (a == 1) {
        printf("Roll Number already exist");
        return 0;
    } else {
        struct list *new_Node;
        if (start == NULL) {
            new_Node = (struct list *) malloc(sizeof (struct list));
            start = new_Node;

        } else {
            new_Node = start;
            while (new_Node->link != NULL)
                new_Node = new_Node->link;

            new_Node = (struct list *) malloc(sizeof (struct list));
            new_Node = new_Node->link;
        }
        
        //Asking input
        printf("First Name: ");
        scanf("%s", new_Node->firstName);
        printf("Last Name: ");
        scanf("%s", new_Node->lastName);
        new_Node->rollNumber = r_no;
        printf("Semester: ");
        scanf("%s", new_Node->semester);
        
        FILE *fp;
        fp = fopen("file.txt", "a+");
        
        fprintf(fp, "%s\n", new_Node->firstName);
        fprintf(fp, "%s\n", new_Node->lastName);
        fprintf(fp, "%d\n", new_Node->rollNumber);
        fprintf(fp, "%s\n", new_Node->semester);
        fclose(fp);

        new_Node->link = NULL;

        return 0;
    }
}

//to search record in database via	
int SearchEntry(int roll_Num) {
    LoadLinkedlistFromFile();
    struct list *new_Node;
    new_Node = start;
    
    if (new_Node == NULL) {
        printf("Data is no record!\n");
        return 0;
    } else {
        while (new_Node != NULL) {
            if (new_Node->rollNumber == roll_Num) {
                if (new_Node == start) {
                    printf("Name: %s %s\n", new_Node->firstName, new_Node->lastName);
                    printf("Roll Number: %d\n", new_Node->rollNumber);
                    printf("Semester: %s\n", new_Node->semester);
                    return 0;
                } else {
                    printf("Name: %s %s\n", new_Node->firstName, new_Node->lastName);
                    printf("Roll Number: %d\n", new_Node->rollNumber);
                    printf("Semester: %s\n", new_Node->semester);
                    return 0;
                }
            } else {
                new_Node = new_Node->link;
            }
        }
        printf("Data has not found!\n");
    }
    return 0;
}

//to delete record from database
int DeleteEntry() {
    int roll_Num;
    printf("Enter Roll Number: ");
    scanf("%d", &roll_Num);
    LoadLinkedlistFromFile();
    struct list *new_Node, *old;
    new_Node = start;
    
    if (new_Node == NULL) {
        printf("Data is no record!\n");
        return 0;
    } else {
        while (new_Node != NULL) {
            if (new_Node->rollNumber == roll_Num) {
                if (new_Node == start) {
                    start = new_Node->link;
                    free(new_Node);
                } else {
                    old->link = new_Node->link;
                    free(new_Node);
                }
                LoadLinkedlistToFile();
                return 0;
            } else {
                old = new_Node;
                new_Node = new_Node->link;
            }
        }
        printf("Data has not found!\n");
    }
    return 0;
}

//replace existed record with newly given
int ReplaceEntry(int roll_Num) {
    LoadLinkedlistFromFile();
    struct list *new_Node;
    new_Node = start;
    
    if (new_Node == NULL) {
        printf("There is no record!\n");
        return 1;
    } else {
        while (new_Node != NULL) {
            if (new_Node->rollNumber == roll_Num) {
                if (new_Node = start) {
                    printf("Name: %s %s\n", new_Node->firstName, new_Node->lastName);
                    printf("Roll Number: %d\n", new_Node->rollNumber);
                    printf("Semester: %s\n", new_Node->semester);

                    printf("Data has found in record\nEnter data to be replaced\n");
                    printf("First Name: ");
                    scanf("%s", new_Node->firstName);
                    printf("Last Name: ");
                    scanf("%s", new_Node->lastName);

                    printf("Roll-No: ");
                    scanf("%d", &new_Node->rollNumber);
                    printf("Semester: ");
                    scanf("%s", new_Node->semester);
                } else {
                    printf("Name: %s %s\n", new_Node->firstName, new_Node->lastName);
                    printf("Roll Number: %d\n", new_Node->rollNumber);
                    printf("Semester: %s\n", new_Node->semester);

                    printf("Data has found in record\nEnter data to be replaced\n");
                    printf("First Name: ");
                    scanf("%s", new_Node->firstName);
                    printf("Last Name: ");
                    scanf("%s", new_Node->lastName);

                    printf("Roll-No: ");
                    scanf("%d", &new_Node->rollNumber);
                    printf("Semester: ");
                    scanf("%s", new_Node->semester);
                }
                LoadLinkedlistToFile();
                printf("Your data has replaced successfully!\n");
                return 0;
            } else {
                new_Node = new_Node->link;
            }
        }
        printf("Data has not found!\n");
    }
    return 0;
}

//to make changes in existed record
int EditEntry() {
    int roll_Num;
    printf("Enter Roll Number: ");
    scanf("%d", &roll_Num);
    LoadLinkedlistFromFile();
    int a;
    struct list *new_Node;
    new_Node = start;
    
    if (new_Node == NULL) {
        printf("There is no record!\n");
    } else {
        while (new_Node != NULL) {
            if (new_Node->rollNumber == roll_Num) {
                if (new_Node = start) {
                    //MessageBox(0,"                 Data Has Found In Record!","Error",1);
                    printf("Data has found in record!\n");
                    printf("First Name: %s\n", new_Node->firstName);
                    printf("Last Name: %s\n", new_Node->lastName);
                    printf("Roll Number: %d\n", new_Node->rollNumber);
                    printf("Semester: %s\n\n", new_Node->semester);

                    printf("Edit First name -         Press 1\n");
                    printf("Edit Last name -          Press 2\n");
                    printf("Edit roll number -        Press 3\n");
                    printf("Edit semester -           Press 4\n");

                    scanf("%d", &a);

                    if (a == 1) {
                        printf("Enter First name: ");
                        scanf("%s", new_Node->firstName);
                    }
                    if (a == 2) {
                        printf("Enter Last name: ");
                        scanf("%s", new_Node->lastName);
                    }
                    if (a == 3) {
                        printf("Enter new roll number: ");
                        scanf("%d", &new_Node->rollNumber);
                    }

                    if (a == 4) {
                        printf("Enter new semester: ");
                        scanf("%s", new_Node->semester);
                    }
                    printf("Data has edited successfully!\n");
                    return 0;
                } else {
                    printf("Data has found in record!\n");
                    printf("First Name: %s\n", new_Node->firstName);
                    printf("Last Name: %s\n", new_Node->lastName);
                    printf("Roll Number: %d\n", new_Node->rollNumber);
                    printf("Semester: %s\n\n", new_Node->semester);

                    printf("Edit First name -         Press 1\n");
                    printf("Edit Last name -          Press 2\n");
                    printf("Edit roll number -        Press 3\n");
                    printf("Edit semester -           Press 4\n");

                    scanf("%d", &a);

                    if (a == 1) {
                        printf("Enter First name: ");
                        scanf("%s", new_Node->firstName);
                    }
                    if (a == 2) {
                        printf("Enter Last name: ");
                        scanf("%s", new_Node->lastName);
                    }
                    if (a == 3) {
                        printf("Enter new roll number: ");
                        scanf("%d", &new_Node->rollNumber);
                    }

                    if (a == 4) {
                        printf("Enter new semester: ");
                        scanf("%s", new_Node->semester);
                    }
                    //MessageBox(0,"                 Data Has Edited Successfully!","Error",1);
                    printf("Data has edited successfully!\n");
                    //system("cls");
                    return 0;
                }
                LoadLinkedlistToFile();
            } else {
                new_Node = new_Node->link;
            }
        }
        printf("Data has not found!\n");
    }
    return 0;
}

int main(int argc, char** argv) {
    while (1) {
        //Home menu
        DisplayHomeMenu();

        //Asking user's opting from home menu
        char ch_option;
        printf("Choose any\n");
        ch_option = getchar();

        switch (ch_option) {
                int a;
            case 'n':
                NewEntry();

                printf("Go to home menu   - Press 1\n");
                printf("Exit   - Press 2\n");

                scanf("%d", &a);

                if (a == 1)
                    continue;
                else
                    return 0;

            case 's':
                printf("Enter Roll Number: ");
                scanf("%d", &rollNumber);

                SearchEntry(rollNumber);

                printf("Go to home menu   - Press 1\n");
                printf("Exit   - Press 2\n");

                scanf("%d", &a);
                
                if (a == 1)
                    continue;
                else
                    return 0;
                
            case 'r':
                printf("Enter Roll Number: ");
                scanf("%d", &rollNumber);
                ReplaceEntry(rollNumber);

                printf("Go to home menu   - Press 1\n");
                printf("Exit   - Press 2\n");

                scanf("%d", &a);

                if (a == 1)
                    continue;
                else
                    return 0;

            case 'd':

                DeleteEntry();

                printf("Go to home menu   - Press 1\n");
                printf("Exit   - Press 2\n");

                scanf("%d", &a);

                if (a == 1)
                    continue;
                else
                    return 0;

            case 'e':
                EditEntry();

                printf("Go to home menu   - Press 1\n");
                printf("Exit   - Press 2\n");

                scanf("%d", &a);

                if (a == 1)
                    continue;
                else
                    return 0;

            case 'l':
                LoadLinkedlistFromFile();
                LinkedlistDisplay();

                printf("Go to home menu   - Press 1\n");
                printf("Exit   - Press 2\n");

                scanf("%d", &a);

                if (a == 1)
                    continue;
                else
                    return 0;

            case 'x':
                return 0;
        }
    }
    return (EXIT_SUCCESS);
}
//**********************************************MAIN PROGRAM ENDS**********************************************************//