/* 24/02/21
* Замойский Артем 8 вариант
* Структура содержит информацию о сотрудниках фирмы: шифр отдела (число), фамилию (указатель), 
* вложенное объединение – дату приёма на работу (строка фиксированной длины) и сумму оклада. 
* Найти сотрудников с минимальным окладом. Удалить сотрудников, принятых на работу в заданный день.
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

        //запрос на ввод даты
        printf("Enter a date of employment of %d employee - ", i + 1);

        //проверка на ввод и ввод даты приема на работу
        while (1)
        {
            scanf("%s", emp[i].empl.date);
            fflush(stdin);
            if ((emp[i].empl.date[0] < '0' || emp[i].empl.date[0] > '3') && (emp[i].empl.date[3] < '0' || (emp[i].empl.date[3]) > '1') && emp[i].empl.date[2] != '.' && emp[i].empl.date[5] != '.')
            {
                printf("Wrong date! Follow this example - xx.xx.xx (31.12.20)");
            }
            else
                break;
        }

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

//функция вывода полей структуры
void output(struct employees *emp, int c)
{
    int i = 0;
    while (i < c)
    {
        printf("Code of %d employee - %d\n", i + 1, emp[i].code);
        printf("Surname of %d employee - %s\n", i + 1, emp[i].surname);
        printf("Date of employment of %d employee - %s\n", i + 1, emp[i].empl.date);
        printf("Sum of salary of %d employee - %s\n", i + 1, emp[i].empl.sum_salary);
        i++;
    }
}
//функция поиска по фамилии
void search(struct employees *emp, int f)
{
    char tsurname[20];
    printf("Enter a surname of employee which you want to find - ");
    while (1)
    {
        scanf("%s", tsurname);
        fflush(stdin);
        if (tsurname[0] > 'Z' || tsurname[0] < 'A')
        {
            printf("Wrong text! Start with a capital English letter - ");
        }
        else
            break;
    }
    int tmp = 0;
    for (int i = 0; i < f; i++)
    {
        if (strcmp(tsurname, emp[i].surname) == 0)
        {
            printf("Found!\n%d %s %s %d\n", emp[i].code, emp[i].surname, emp[i].empl.date, emp[i].empl.sum_salary);
            tmp++;
        }
    }
    if (tmp == 0)
        printf("Not found!");
}

//функция удаления сотрудника с окладом, ниже заданного
void delete (struct employees *emp, int f)
{
    int salary;
    printf("Enter a sum of salary to delete sum of salaries, which are smaller - ");
    while (1)
    {
        scanf("%d", &salary);
        fflush(stdin);
        if (salary > 5000 || salary < 0)
        {
            printf("Wrong number! 0<..<5000 - ");
        }
        else
            break;
    }
    int p = 0;
    while (p < f)
    {
        if (emp[p].empl.sum_salary < salary)
        {
            for (int k = p; k < f - 1; k++)
            {
                emp[k].empl.sum_salary = emp[k + 1].empl.sum_salary;
                emp[k].surname = emp[k + 1].surname;
                emp[k].code = emp[k + 1].code;
                strcpy(emp[k].empl.date, emp[k + 1].empl.date);
            }
            f--;
        }
        else
            p++;
    }
    for (int i = 0; i < f; i++)
        printf("%s %d\n", emp[i].surname, emp[i].empl.sum_salary);
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
    output(emp, n);
    int operation;
    do
    {
        printf("What you want to do?\nEnter 1 to found surname of employee\n");
        printf("Enter 2 to delete employer with smaller sum of salary than the specified\nEnter 3 to exit\nEnter number: ");
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
        {
            search(emp, n);
            break;
        }
        case 2:
        {
            delete (emp, n);
            break;
        }
        case 3:
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