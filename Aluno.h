#ifndef Aluno
#define Aluno
#define MAX 100
#define SEX_MAX 10
#define NOTA_MAX 7

#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"

typedef struct address{
    char streat_name[MAX];//streat_name of the student
    int number;//number of the house
    char CEP[MAX];//cep of the student
    char cidade[MAX];//city of the student
    char state[4];//state of the student
} Address;

typedef struct nota{
    double grade;//grade of a test
    double weight;//his weight(of the test not the student lmao)
} Notas;

typedef struct Students{
    int enroll;//enrollment number
    char name[MAX];//name of the student
    int age;//age of the student
    char sex[SEX_MAX];//sex of the student
    char course[MAX];//course of the student
    Notas *notas[NOTA_MAX];//grades of the student
    Address *student_address;//address of the student
    int grade_count;//keeps the grade amount to logical control
} Student;

//Set the name of the student
void setName(Student * student, char name[MAX]){
    copiaString(student->name, name);
}

//Set the curso of the student
void setCourse(Student * student, char course[MAX]){
    copiaString(student->course, course);
}

//Set the age of the student
void setAge(Student * student, int age){
    student->age = age;
}

//Set the curso of the student
void setSex(Student * student, char sex[MAX]){
    copiaString(student->sex, sex);
}

//Set student's matricula
void setEnroll(Student * student, int enroll){
    student->enroll = enroll;
}

//Set the grade amount of the student.
void setGradeCount(Student * student, int grade_count){
    student->grade_count = grade_count;
}

//Allocate memory for a new grade and set his data. Also return the grade memory locations
Notas * newNota(double grades, double weight){
    Notas * nota = (Notas *) malloc(sizeof(Notas));
    nota->grade = grades;
    nota->weight = weight;
    return nota;
}

//Adds a new nota to the given student.
void addNota(Student * student, double grades, double weight, int index){
    student->notas[index] = newNota(grades, weight);
}

//Allocate memory for a new addres and set his data. Also return the addres memory locations
Address * newAddres(char streat_name[MAX], int number, char CEP[MAX]){
    Address * student_address = (Address *) malloc(sizeof(Address));
    copiaString(student_address->streat_name, streat_name);
    student_address->number = number;
    copiaString(student_address->CEP, CEP);
    copiaString(student_address->cidade, "Sao Borja");
    copiaString(student_address->state, "RS");
    return student_address;
}

//Set the student address
void setAddres(Student * student, char streat_name[MAX], int number, char CEP[MAX]){
    student->student_address = newAddres(streat_name, number, CEP);
}

//Allocate memory for a new student and set his data. Also return the student memory locations
Student * newStudent(int enroll, char name[MAX], int age, char sex[MAX], char course[MAX]){
    Student * aluno = (Student *) malloc(sizeof(Student));
    
    setEnroll(aluno, enroll);
    setName(aluno, name);
    setAge(aluno, age);
    setSex(aluno, sex);
    setCourse(aluno, course);
    return aluno;
}

//show on the terminal grades
void printNota(Notas * nota){
    printf("%lf ", nota->grade);
}

//show on the terminal the address data
void printAdress(Address address){
    printf("Streat: %s\n", address.streat_name);
    printf("Number: %d\n", address.number);
    printf("CEP: %s\n", address.CEP);
    printf("Cidade: %s\n", address.cidade);
    printf("State: %s\n", address.state);
}

//show on the terminal the student data
void printStudent(Student * student){

    printf("Student enrollment: %d\n", student->enroll);
    printf("Student name: %s\n", student->name);
    printf("Student age: %d\n", student->age);
    printf("Student sex: %s\n", student->sex);
    printf("Student course: %s\n", student->course);
    printf("Student grades: ");
    for (int i = 0; i < student->grade_count; i++)
    {
        printNota(student->notas[i]);
    }
    printf("\n");
    printAdress(*student->student_address);
    printf("====================\n");
}

//Make the menu to edit the grades
void editGrades(Student * student){
    int loop = 1;//variavel de controle do loop do programa
    int escolha = 0;//variavel que armazena qual função o usuario escolheu
    char input[MAX] = "";
    
    while(loop){
        int i = 0;
        double input = 0.0;
        system("cls");//clear the terminal
        printf("====GRADES EDIT MENU====\n");
        for (; i < student->grade_count; i++)
        {
            printf("%d. Edit grade number %d\n", (i*2)+1, i+1);
            printf("%d. Edit weight number %d\n", (i*2)+2, i+1);
        }
        printf("%d. Sair\n", (i*2)+1);//setta o valor da variavel loop para 0, saindo loop do menu
        scanf("%d", &escolha);//recebe um numero que o usuario escrever
        fflush(stdin);//cleans the input file

        if (escolha == (i*2)+1)
        {
            return;
        }
        
        if((escolha % 2) == 0){
            printf("Type weight:\n");
            scanf("%lf", &input);
            fflush(stdin);//cleans the input file
            student->notas[(escolha/2) - 1]->weight = input;
        }else{
            printf("Type grade:\n");
            scanf("%lf", &input);
            fflush(stdin);//cleans the input file
            student->notas[(escolha - 1) / 2]->grade = input;
        }
    }
}

//Make the menu to edit the address data
void editAdress(Address * address){
    int loop = 1;//variavel de controle do loop do programa
    int escolha = 0;//variavel que armazena qual função o usuario escolheu
    int result = 0;
    char input[MAX] = "";
    
    while(loop){
        // char name[MAX] = "";
        //Menu para escolha de funções do programa
        system("cls");//clear the terminal
        printf("====EDIT ADRESS====\n");
        printf("1. Edit streat name\n");//
        printf("2. Edit number\n");//
        printf("3. Edit CEP\n");//
        printf("4. Edit Cidade\n");//
        printf("5. Edit State\n");//
        printf("6. Sair\n");//setta o valor da variavel loop para 0, saindo loop do menu
        
        scanf("%d", &escolha);//recebe um numero que o usuario escrever
        fflush(stdin);//cleans the input file
        //laço switch para contorle do menu
        switch(escolha){
            case 1:
                printf("Type the new streat name:\n");
                scanf("%[^\n]", input);
                fflush(stdin);//cleans the input file
                copiaString(address->streat_name, input);
                break;//stop the switch statement :0

            case 2:
                printf("Type the new number:\n");
                scanf("%d", result);
                fflush(stdin);//cleans the input file
                address->number = result;
                break;//stop the switch statement :0

            case 3:
                printf("Type the new CEP:\n");
                scanf("%[^\n]", input);
                fflush(stdin);//cleans the input file
                copiaString(address->CEP, input);
                break;//stop the switch statement :0

            case 4:
                printf("Type the new Cidade:\n");
                scanf("%[^\n]", input);
                fflush(stdin);//cleans the input file
                copiaString(address->cidade, input);
                break;//stop the switch statement :0

            case 5:
                printf("Type the new State:\n");
                scanf("%[^\n]", input);
                fflush(stdin);//cleans the input file
                copiaString(address->state, input);
                break;//stop the switch statement :0
            
            case 6:
                loop = 0;
                break;//stop the switch statement :0

            default:
                printf("Algo de errado nao esta certo...\n");
        }
    }
}

//Make the menu to edit the student data
void editStudent(Student * student){
    if (student == NULL)
    {
        printf("Can't find this student\n");
        return;
    }
    
    int loop = 1;//variavel de controle do loop do programa
    int escolha = 0;//variavel que armazena qual função o usuario escolheu
    int result = 0;
    char input[MAX] = "";
    
    while(loop){
        // char name[MAX] = "";
        //Menu para escolha de funções do programa
        system("cls");//clear the terminal
        printf("====EDIT====\n");
        printf("1. Edit Student Name\n");//
        printf("2. Edit Student Age\n");//
        printf("3. Edit Student Sex\n");//
        printf("4. Edit Student Course\n");//
        printf("5. Edit Student Grades\n");//
        printf("6. Edit Student Adress\n");//
        printf("7. Sair\n");//setta o valor da variavel loop para 0, saindo loop do menu
        
        scanf("%d", &escolha);//recebe um numero que o usuario escrever
        fflush(stdin);//cleans the input file
        //laço switch para contorle do menu
        switch(escolha){
            case 1:
                printf("Type the new name:\n");
                scanf("%[^\n]", input);
                fflush(stdin);//cleans the input file
                setName(student, input);
                break;//stop the switch statement :0

            case 2:
                printf("Type the new age:\n");
                scanf("%d", result);
                fflush(stdin);//cleans the input file
                setAge(student, result);
                break;//stop the switch statement :0

            case 3:
                printf("Type the new sex:\n");
                scanf("%[^\n]", input);
                fflush(stdin);//cleans the input file
                setSex(student, input);
                break;//stop the switch statement :0

            case 4:
                printf("Type the new course:\n");
                scanf("%[^\n]", input);
                fflush(stdin);//cleans the input file
                setCourse(student, input);
                break;//stop the switch statement :0

            case 5:
                editGrades(student);
                break;//stop the switch statement :0

            case 6:
                editAdress(student->student_address);
                break;//stop the switch statement :0
            
            case 7:
                loop = 0;
                break;//stop the switch statement :0

            default:
                printf("Algo de errado nao esta certo...\n");
        }
    }
}

//Free the memory previously allocated
void freeStudentData(Student *student){
    free(student->student_address);
    for (int i = 0; i < student->grade_count; i++)
    {
        free(student->notas[i]);
    }
}

//return the avarage grade of the given student
double studentApproved(Student *student){
    double grade_total = 0, weight_total = 0;
    for (int i = 0; i < student->grade_count; i++)
    {
        grade_total += student->notas[i]->grade;
        weight_total += student->notas[i]->weight;
    }
    return grade_total / weight_total;
}
#endif