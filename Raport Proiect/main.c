#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50

// Structura pentru un angajat
struct Employee
{
    int id;
    char name[MAX_NAME_LENGTH];
    char role[MAX_NAME_LENGTH];
};

// Functie pentru afisarea meniului
void printMenu()
{
    printf("\n===== Meniu =====\n");
    printf("1. Afisati tabelul cu angajati\n");
    printf("2. Adaugati o noua inregistrare\n");
    printf("3. Stergeti o inregistrare\n");
    printf("4. Cautati o inregistrare\n");
    printf("5. Iesiti\n");
    printf("==================\n");
}

// Functie pentru afisarea unui angajat
void printEmployee(struct Employee emp)
{
    printf("ID: %d | Nume: %s | Rol: %s\n", emp.id, emp.name, emp.role);
}

// Functie pentru afisarea intregului tabel de angajati
void displayEmployees(struct Employee employees[], int count)
{
    printf("\n===== Tabelul cu angajati =====\n");
    for (int i = 0; i < count; ++i)
    {
        printEmployee(employees[i]);
    }
    printf("==============================\n");
}

// Functie pentru adaugarea unui nou angajat
void addEmployee(struct Employee employees[], int *count)
{
    if (*count < MAX_EMPLOYEES)
    {
        printf("\nIntroduceti datele noului angajat:\n");

        printf("ID: ");
        scanf("%d", &employees[*count].id);

        printf("Nume: ");
        scanf("%s", employees[*count].name);

        printf("Rol: ");
        scanf("%s", employees[*count].role);

        (*count)++;
        printf("Angajat adaugat cu succes!\n");
    }
    else
    {
        printf("Numarul maxim de angajati a fost atins!\n");
    }
}

// Functie pentru stergerea unui angajat dupa ID
void deleteEmployee(struct Employee employees[], int *count, int id)
{
    int index = -1;
    for (int i = 0; i < *count; ++i)
    {
        if (employees[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < *count - 1; ++i)
        {
            employees[i] = employees[i + 1];
        }
        (*count)--;
        printf("Angajat sters cu succes!\n");
    }
    else
    {
        printf("Angajatul cu ID-ul %d nu a fost gasit!\n", id);
    }
}

// Functie pentru cautarea unui angajat dupa ID
void searchEmployee(struct Employee employees[], int count, int id)
{
    int found = 0;
    for (int i = 0; i < count; ++i)
    {
        if (employees[i].id == id)
        {
            printEmployee(employees[i]);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Angajatul cu ID-ul %d nu a fost gasit!\n", id);
    }
}

// Functie pentru salvarea datelor intr-un fisier
void saveToFile(struct Employee employees[], int count)
{
    FILE *file = fopen("employee_data.txt", "w");
    if (file == NULL)
    {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }

    for (int i = 0; i < count; ++i)
    {
        fprintf(file, "%d %s %s\n", employees[i].id, employees[i].name, employees[i].role);
    }

    fclose(file);
    printf("Datele au fost salvate cu succes in fisier!\n");
}

// Functie pentru incarcarea datelor dintr-un fisier
void loadFromFile(struct Employee employees[], int *count)
{
    FILE *file = fopen("employee_data.txt", "r");
    if (file == NULL)
    {
        printf("Fisierul nu exista sau nu poate fi deschis!\n");
        return;
    }

    while (fscanf(file, "%d %s %s", &employees[*count].id, employees[*count].name, employees[*count].role) != EOF)
    {
        (*count)++;
        if (*count >= MAX_EMPLOYEES)
        {
            printf("Ati atins numarul maxim de angajati. Incarcarea s-a oprit.\n");
            break;
        }
    }

    fclose(file);
    printf("Datele au fost incarcate cu succes din fisier!\n");
}

int main()
{
    struct Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    int choice;

    loadFromFile(employees, &employeeCount);

    do
    {
        printMenu();
        printf("Alegeti o optiune: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayEmployees(employees, employeeCount);
            break;
        case 2:
            addEmployee(employees, &employeeCount);
            break;
        case 3:
            if (employeeCount > 0)
            {
                int deleteId;
                printf("Introduceti ID-ul angajatului de sters: ");
                scanf("%d", &deleteId);
                deleteEmployee(employees, &employeeCount, deleteId);
            }
            else
            {
                printf("Nu exista angajati de sters!\n");
            }
            break;
        case 4:
            if (employeeCount > 0)
            {
                int searchId;
                printf("Introduceti ID-ul angajatului de cautat: ");
                scanf("%d", &searchId);
                searchEmployee(employees, employeeCount, searchId);
            }
            else
            {
                printf("Nu există angajati de cautat!\n");
            }
            break;
        case 5:
            saveToFile(employees, employeeCount);
            printf("La revedere!\n");
            break;
        default:
            printf("Optiune invalida! Alegeti din nou.\n");
        }
    }
    while (choice != 5);

    return 0;
}
