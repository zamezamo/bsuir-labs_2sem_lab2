/* 
* 24/02/21
* Artyom Zamoyskiy
*
* Task:
* RU: Структура содержит информацию о сотрудниках фирмы: шифр отдела (число), фамилию (указатель), 
*     вложенное объединение – дату приёма на работу (строка фиксированной длины) и сумму оклада. 
*     Найти сотрудников с минимальным окладом. Удалить сотрудников, принятых на работу в заданный день.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union salary
{
    char date[10];
    int sum_salary;
};

struct employees
{
    int code;
    char *surname;
    union salary empl;
};

//фунция ввода всех полей структуры
void input(struct employees *emp, int f)
{
    for (int i = 0; i < f; i++)
    {
        //запрос на ввод шифра
        printf("Enter a code of %d employee - ", i + 1);

        //проверка на ввод и ввод шифра
        while (1)
        {
            scanf("%d", &emp[i].code);
            fflush(stdin);
            if (emp[i].code > 9999 || emp[i].code < 0)
                printf("Enter only 4 digits! - ");
            else
                break;
        }

        //запрос на ввод фамилии
        printf("Enter a surname of %d employee - ", i + 1);
        emp[i].surname = (char *)malloc(20 * sizeof(char));

        //проверка на ввод и ввод фамилии
        while (1)
        {
            scanf("%s", emp[i].surname);
            fflush(stdin);
            if (emp[i].surname[0] > 'Z' || emp[i].surname[0] < 'A')
            {
                printf("Wrong text! Start with a capital English letter - ");
            }
            else
                break;
        }

        if (i % 2 != 0)
        {
            //запрос на ввод даты
            printf("Enter a date of employment of %d employee - ", i + 1);

            //проверка на ввод и ввод даты приема на работу
            while (1)
            {
                scanf("%s", emp[i].empl.date);
                fflush(stdin);
                if (emp[i].empl.date[0] < '0' || emp[i].empl.date[0] > '3' || emp[i].empl.date[3] < '0' || emp[i].empl.date[3] > '1' || emp[i].empl.date[2] != '.' || emp[i].empl.date[5] != '.')
                {
                    printf("Wrong date! Follow this example - xx.xx.xx (31.12.20) - ");
                }
                else
                    break;
            }
        }

        else
        {
            //запрос на ввод суммы оклада
            printf("Enter a sum of salary of %d employee - ", i + 1);

            //проверка на ввод и ввод суммы оклада
            while (1)
            {
                scanf("%d", &emp[i].empl.sum_salary);
                fflush(stdin);
                if (emp[i].empl.sum_salary > 5000 || emp[i].empl.sum_salary < 0)
                {
                    printf("Wrong number! 0<..<5000 - ");
                }
                else
                    break;
            }
        }
    }
}

//функция вывода полей структуры
void output(struct employees *emp, int c)
{
    int i = 0;
    printf("\n");
    while (i < c)
    {
        printf("Code of %d employee - %d\n", i + 1, emp[i].code);
        printf("Surname of %d employee - %s\n", i + 1, emp[i].surname);
        if (i % 2 != 0)
            printf("Date of employment of %d employee - %s\n", i + 1, emp[i].empl.date);
        else
            printf("Sum of salary of %d employee - %d\n", i + 1, emp[i].empl.sum_salary);
        printf("\n");
        i++;
    }
}

//функция поиска по минимальной сумме оклада
void search(struct employees *emp, int f)
{
    int tmp = emp[0].empl.sum_salary;
    for (int i = 0; i < f; i = i + 2)
    {
        if (emp[i].empl.sum_salary < tmp)
            tmp = emp[i].empl.sum_salary;
    }
    printf("Found: %d\n", tmp);
}

//функция удаления сотрудника принятого в данный день
void delete (struct employees *emp, int f)
{
    char date[10];
    printf("Enter a date - ");
    while (1)
    {
        scanf("%s", date);
        fflush(stdin);
        if (date[0] < '0' || date[0] > '3' || date[3] < '0' || date[3] > '1' || date[2] != '.' || date[5] != '.')
        {
            printf("Wrong date! Follow this example - xx.xx.xx (31.12.20) - ");
        }
        else
            break;
    }

    int p = 0;
    while (p < f)
    {
        if (emp[p].empl.date == date)
        {
            for (int k = p; k < f - 1; k++)
            {
                emp[k].surname = emp[k + 1].surname;
                emp[k].code = emp[k + 1].code;
            }
            f--;
        }
        else
            p=p+2;
    }
    
    for (int i = 0; i < f; i=i+2)
        printf("%d %s\n", emp[i].code, emp[i].surname);

}

int main()
{
    int n;

    //запрос на ввод кол-ва сотрудников
    printf("Enter number of employees - ");
    while (1)
    {
        scanf("%d", &n);
        fflush(stdin);
        if (n < 1 || n > 9)
        {
            printf("Enter only a number less than 9! - ");
        }
        else
            break;
    }
    struct employees *emp = (struct employees *)malloc(n * sizeof(struct employees));
    input(emp, n);
    fflush(stdin);
    int operation;
    do
    {
        printf("\n  ---\nWhat you want to do?\nEnter 1 to output all data\n");
        printf("Enter 2 to find employee with a minimum salary\nEnter 3 to delete the employee hired on the given day");
        printf("\nEnter 4 to exit\nEnter number: ");
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
        {
            output(emp, n);
            break;
        }
        case 2:
        {
            search(emp, n);
            break;
        }
        case 3:
        {
            delete (emp, n);
            break;
        }
        case 4:
        {
            free(emp);
            return 0;
        }
        default:
        {
            free(emp);
            return 0;
        }
        }
    } while (1);
}