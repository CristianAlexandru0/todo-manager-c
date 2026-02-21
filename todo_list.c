#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char *todo; // dynamic string for task description
    int done;   // 0 for undone, 1 for done
}Task;

// validate string length and prevent empty inputs
void ver_str(char *string_task)
{

    while(strlen(string_task) <= 0 || strlen(string_task) >= 151 ) 
    {
        printf("Error: Input exceeded 150 characters.\n");
        printf("Enter task description (max 150 chars):");
        fgets(string_task, 150, stdin);
        // Clean the newline character
        string_task[strcspn(string_task, "\n")] = '\0';
    }
}

// adding a new task to the list, uses Task ** to modify the pointer in main if realloc moves
void add_todo(char *added_task, Task **todos,int * cap, int *lenght)
{
    if( (*lenght) == (*cap))
    {
        //if the lenght equals with the max capacity, realloc
        *cap = *cap + 3;
        Task *temp = (Task *)realloc(*todos, *cap * sizeof(Task));
        if(temp == NULL) {
            printf("Memory allocation failed!\n");
            return; 
        }
        *todos = temp;
    }
    // allocate memory for the description string
    (*todos)[*lenght].todo=(char *)malloc((strlen(added_task)+1)*sizeof(char));

    strcpy((*todos)[*lenght].todo,added_task);
    (*todos)[*lenght].done=0;

    (*lenght)++;
    printf("Your task was added.\n");
}

// display all tasks with their current status
void show_all_tasks(Task * todos, int *lenght)
{
    char status[10]; 
    int i;
    printf("\n=============================\n");
    for(i = 0; i < *lenght; i++)
    {
        if(todos[i].done)
        {
           strcpy(status,"done");
        }
        else
        {
           strcpy(status,"undone");
        }
         printf("%d. %s [%s]\n",i+1,todos[i].todo,status);
    }
    printf("\n=============================\n");
}

// marks a task completed
void completed_task(Task *todos, int position)
{
    todos[position -1].done=1;
    printf("The task was done.\n");
}

// deleting a task
void delete_task(Task **todos, int position, int *lenght)
{
    int i;
    position -= 1;
    free((*todos)[position].todo);
    for(i = position; i < *lenght - 1 ;i++)
    {
        // shift all tasks following the deleted one to the left
        (*todos)[i] = (*todos)[i + 1];
        
    }

    (*lenght)--;
    (*todos) = (Task *)realloc((*todos), *lenght * sizeof(Task));
    printf("The task was deleted.\n");
}

void edit_task(Task *todos, int position, char * edited_task)
{
    // convert 1-based user input to 0-based array index
    int i = position - 1;

    // creates a temporary string to avoid Memory Leak
    char *temp=(char *)realloc(todos[i].todo,(strlen(edited_task)+1)*sizeof(char ));
    if(temp==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    todos[i].todo=temp;

    strcpy(todos[i].todo, edited_task);
    printf("The task was updated");

}

int main()
{
    int cap=0,lenght=0; // dynamic capcaity and current count
    char string_task[151]; // the task description 
    int option=-1; // menu selection
    int index=0;   // the index for task selecition

    // the pointer to our list of tasks
    Task *todos;    
    todos=NULL;

    while(option!= 0)
    {
        printf("\n=============================\n");
        printf("    TODO LIST MANAGER\n");
        printf("=============================\n");
        printf("1. Add New Task\n");
        printf("2. Show All Tasks\n");
        printf("3. Edit a Task\n");
        printf("4. Delete a Task\n");
        printf("5. Mark as Completed\n");
        printf("0. Exit\n");
        printf("-----------------------------\n");
        printf("Select an option: ");

        scanf("%d",&option);
        // verify if the option is valid
        while((option < 1 || option > 5) && option != 0 ){
            printf("Error: Invalid option.\n");
            printf("Select a valid option: ");
            scanf("%d",&option);
        }
        getchar();
        // evaluate the 'option' selected by the user
        switch(option)
        {
            case 1:
                printf("Enter task description (max 150 chars):");
                fgets(string_task, 151, stdin);
                string_task[strcspn(string_task, "\n")] = '\0';

                ver_str(string_task);

                add_todo(string_task, &todos, &cap, &lenght);
                break;

            case 2:
                show_all_tasks(todos, &lenght);
                break;

            case 3:
                printf("Choose the task you want to edit:");
                scanf("%d",&index);
                // ensure index is within the existing list (1 to current length)
                while(index <= 0 || index > lenght)
                {
                    printf("Error: Invalid Task index.");
                    scanf("%d",&index);
                }

                // clear the input buffer after scanf so fgets can work correctly
                getchar();

                printf("Enter new task description (max 150 chars): ");

                fgets(string_task, 151, stdin);
                string_task[strcspn(string_task, "\n")] = '\0';

                ver_str(string_task);
                edit_task(todos, index, string_task);
                break;

            case 4:
                printf("Choose the task you want to delete:");
                scanf("%d", &index);
                while(index <= 0 || index > lenght)
                {
                    printf("Error: Invalid Task index.\n");
                    printf("Choose the task you want to delete:");
                    scanf("%d", &index);
                }
                // pass &todos because delete_task may resize the array via realloc
                delete_task(&todos, index, &lenght);
                break;

            case 5:

                printf("Choose the task you completed:");
                scanf("%d", &index);

                while(index <= 0 && index > lenght+1)
                {
                    printf("Error: Invalid Task index.\n");
                    printf("Choose the task you completed:");
                    scanf("%d", &index);
                }
                // flip the 'done' status in the structure
                completed_task(todos,index);
                break;

            case 0:
                option = 0;
                break;

        }


    }
    // free the memory
    int i;
    for (i = 0; i < lenght; i++) {
        if (todos[i].todo != NULL) {
            free(todos[i].todo);
        }
    }
    free(todos);

    return 0;
}
