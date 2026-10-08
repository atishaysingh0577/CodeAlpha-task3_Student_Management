#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student
{
    int rollNumber;
    char name[50];
    int age;
    char course[50];
    float marks;
};

/* Function declarations */
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

/* Add a new student */
void addStudent()
{
    struct Student student;
    FILE *file;

    file = fopen(FILE_NAME, "ab");

    if (file == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    printf("\n========== ADD STUDENT ==========\n");

    printf("Enter Roll Number: ");
    scanf("%d", &student.rollNumber);

    printf("Enter Name: ");
    scanf(" %[^\n]", student.name);

    printf("Enter Age: ");
    scanf("%d", &student.age);

    printf("Enter Course: ");
    scanf(" %[^\n]", student.course);

    printf("Enter Marks: ");
    scanf("%f", &student.marks);

    fwrite(&student, sizeof(struct Student), 1, file);

    fclose(file);

    printf("\nStudent added successfully!\n");
}

/* Display all students */
void displayStudents()
{
    struct Student student;
    FILE *file;
    int found = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n========== ALL STUDENTS ==========\n");

    while (fread(&student, sizeof(struct Student), 1, file))
    {
        printf("\nRoll Number : %d\n", student.rollNumber);
        printf("Name        : %s\n", student.name);
        printf("Age         : %d\n", student.age);
        printf("Course      : %s\n", student.course);
        printf("Marks       : %.2f\n", student.marks);
        printf("----------------------------------\n");

        found = 1;
    }

    fclose(file);

    if (!found)
    {
        printf("\nNo student records found.\n");
    }
}

/* Search student */
void searchStudent()
{
    struct Student student;
    FILE *file;

    int rollNumber;
    int found = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n========== SEARCH STUDENT ==========\n");

    printf("Enter Roll Number to search: ");
    scanf("%d", &rollNumber);

    while (fread(&student, sizeof(struct Student), 1, file))
    {
        if (student.rollNumber == rollNumber)
        {
            printf("\n========== STUDENT FOUND ==========\n");

            printf("Roll Number : %d\n", student.rollNumber);
            printf("Name        : %s\n", student.name);
            printf("Age         : %d\n", student.age);
            printf("Course      : %s\n", student.course);
            printf("Marks       : %.2f\n", student.marks);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nStudent not found.\n");
    }
}

/* Update student */
void updateStudent()
{
    struct Student student;
    FILE *file;

    int rollNumber;
    int found = 0;

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n========== UPDATE STUDENT ==========\n");

    printf("Enter Roll Number to update: ");
    scanf("%d", &rollNumber);

    while (fread(&student, sizeof(struct Student), 1, file))
    {
        if (student.rollNumber == rollNumber)
        {
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", student.name);

            printf("Enter New Age: ");
            scanf("%d", &student.age);

            printf("Enter New Course: ");
            scanf(" %[^\n]", student.course);

            printf("Enter New Marks: ");
            scanf("%f", &student.marks);

            fseek(file, -(long)sizeof(struct Student), SEEK_CUR);

            fwrite(&student, sizeof(struct Student), 1, file);

            found = 1;

            printf("\nStudent updated successfully!\n");
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nStudent not found.\n");
    }
}

/* Delete student */
void deleteStudent()
{
    struct Student student;
    FILE *file;
    FILE *tempFile;

    int rollNumber;
    int found = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    tempFile = fopen("temp.dat", "wb");

    if (tempFile == NULL)
    {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    printf("\n========== DELETE STUDENT ==========\n");

    printf("Enter Roll Number to delete: ");
    scanf("%d", &rollNumber);

    while (fread(&student, sizeof(struct Student), 1, file))
    {
        if (student.rollNumber == rollNumber)
        {
            found = 1;
        }
        else
        {
            fwrite(&student, sizeof(struct Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
    {
        printf("\nStudent deleted successfully!\n");
    }
    else
    {
        printf("\nStudent not found.\n");
    }
}

/* Main function */
int main()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using Student Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please enter 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}