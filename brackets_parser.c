#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000

// int count = 0; // == stk->top + 1

typedef struct stack{
    char data[SIZE];
    int top; // index of the top item. If stack is full then; top == SIZE - 1
}stack;

typedef struct{
    char* key;
    char* value;
}hash_table;

hash_table* linear_search(hash_table* items, size_t size, char *key){
    for (size_t i=0; i < size; i++){
        if (strcmp(items[i].key, key) == 0)
            return &items[i];
    }
    return NULL;
}

char *arr_char_by_char(FILE *filep, char *, int *len_elements);
FILE *read(char *file_name);
void create_stack(stack *stk);
int is_full(stack *stk);
int is_empty(stack *stk);
void push(stack *stk, char item);
void pop(stack *stk);
void print_stack(stack *stk);
void print_arr(char *arr, int len_elements);
int is_balanced(stack *stk, char *elemets, int len_elements, hash_table *items);




int main(){
    char *file_name = "text";
    char *elements;
    int len_elements = 0;
    FILE *filep = read(file_name);
    elements = arr_char_by_char(filep, elements, &len_elements);
    print_arr(elements, len_elements);

    hash_table items[] = {{"(", ")"}, {"{", "}"}, {"[", "]"}};

    stack *stk = (stack *) malloc(sizeof(stack));
    printf("a"); // this line interestingly prevents segmentation fault! :O
    create_stack(stk);

    int is_;
    is_ = is_balanced(stk, elements, len_elements, items);
    printf("\nis_balanced: %d\n", is_);

    

    free(elements);
    free(stk);

    return 0;
}


FILE *read(char *file_name){

    FILE *filep;
    filep = fopen(file_name, "r");
    if (filep == NULL)
    {
        printf("File is not available \n");
        return NULL;
    }
    else
    {
        return filep;
    }

    // fclose(filePointer);

}

char *arr_char_by_char(FILE *filep, char *elements, int *len_elements){
    int ctr = 0;
    int ch;
    *len_elements = 0;
    elements = (char *) malloc(sizeof(char));
    while ((ch = fgetc(filep)) != EOF){
        elements[ctr] = ch;
        elements = (char *) realloc(elements, (ctr + 2) * sizeof(char));
        ctr++;
        *len_elements += 1;
    }
    printf("\nlen: %d\n", *len_elements);

    return elements;
}


void create_stack(stack *stk){
  stk->top = -1;
}

int is_empty(stack *stk){
    if (stk->top == -1)
        return 1;
    else
        return 0;
}
int is_full(stack *stk){
    if (stk->top == SIZE - 1)
        return 1;
    else
        return 0;
}

void push(stack *stk, char item){
    if (is_full(stk))
        printf("\nStack Overflow.\n");
    else{
        // stk->top++;
        stk->data[++stk->top] = item;
    }
}


void pop(stack *stk){
    if (is_empty(stk))
        printf("\nStack Underflow.\n");
    else{
        printf("\nItem popped = %c", stk->data[stk->top--]);
        // stk->top--;
    }
}


void print_stack(stack *stk){
  printf("Stack: ");
  for (int i = 0; i < stk->top + 1; i++) {
    printf("%c ", stk->data[i]);
  }
  printf("\n");
}

void print_arr(char *arr, int len_items){
    printf("\n");
    for (int i=0; i < len_items; i++)
        printf("%c ", arr[i]);

}

int is_balanced(stack *stk, char *elements, int len_elements, hash_table *items){
    char *item;
    for (int i=0; i < len_elements; i++){
        item[0] = elements[i];
        printf("\nitem: %c", item[0]);
        hash_table* found = linear_search(items, stk->top + 1, item);
        
        if (item[0] == '(' || item[0] == '{' || item[0] == '['){
            push(stk, item[0]);
        }
        else if (item[0] == ')' || item[0] == '}' || item[0] == ']'){
            if (is_empty(stk))
                return 0;
            pop(stk);

            if (found != NULL && found->value != item)
                return 0;
        }
        else
            continue;
    }
    printf("\nnum_items: %d", stk->top + 1);

    return is_empty(stk);
}