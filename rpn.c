/**-Auteur : Thomas ABREU DIAS aka BOYA-**/
/*-Dépot GIT : https://github.com/ThomasAbreuDias/RPNhttps://github.com/ThomasAbreuDias/RPN
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct _link
{
  char* operation;
  int  value;
  struct _link* next;
}_link;

//Verifie si la chaine de char est une instruction
char* is_instruction(char* instruction){
  char op[9][4] = {"ADD\0", "SUB\0", "MUL\0", "DIV\0", "MOD\0", "POP\0", "DUP\0", "SWP\0", "ROL\0"};

  for (int i = 0; i < 9; ++i){
    if (strcmp(instruction, op[i]) == 0)
      return instruction;
  }
  return NULL;
}
//Crée la liste
_link* make_link(int val, _link* list){
  _link* link = (_link*)malloc(sizeof(_link));

  if(link == NULL)
  {
    fprintf(stderr, "Out of memory\n");
    exit(1);
  }
  link->value = val;
  link->next = list;

  return link;
}
//Ajoute un élement au debut de la pile
_link* push_link(int value, _link* list){
    _link* current;

    if(list == NULL){
      list = make_link(value, NULL);
    }else{
      current = list;
        while(current->next != NULL){
          current = current->next;
        }
        current->next = make_link(value, NULL);
    }
    return list;
}


//Affiche la liste
void display_link(int i, _link* list){
  if (i == 0)
    printf("%d", list->value);
  if (i== 1 )
    printf(" %d", list->value);
  if (list->next != NULL)
   display_link(1, list->next);
}
//Libère l'espace memoire utilisé par la liste
void free_link(_link* list)
{
  if (list != NULL)
  {
    free_link(list->next);
    free(list);
  }
}
//Retire le premier element de la liste
_link* pop_link(_link* list){
   if (list == NULL)
   {
    fprintf(stderr, "Empty list\n");
    exit(3);
  }
  _link* tmp = list->next;
  free(list);
  return tmp;
}

//Convertie les valeur en int
_link* init_link(_link* list, char* value){
  if ( isdigit(value[0]) || (value[0] == '-' && isdigit(value[1])) )
  {
    int n;
    n = (int) strtol(value, NULL, 10);

    return push_link(n, list);
  }else{
    fprintf(stderr, "Value is not allowed\n");
    exit(3);
  }
}
//Revois la longeur de la pile
int get_last_link_indice(int i, _link* list){
  if(list->next != NULL)
    return get_last_link_indice(++i, list->next);
  return i;
}

//Recupère le n maillion
_link* get_n_link(int n, _link* list){
  if (list == NULL)
  {
    fprintf(stderr, "Empty list\n");
    exit(3);
  }
  if(n <= 0)
    return list;
  if (list->next != NULL)
    return get_n_link(n-1, list->next);
  return list;
}
//Affiche les erreur
void display_error(_link* list){

  if(list != NULL){
    display_link(0,list);
    printf(" ERROR");
  }
  else
    printf("ERROR");
  exit(1);
}

//Execute les instructions
_link* do_instruction(_link* list, char* instruction){
  char op[9][4] = {"ADD", "SUB", "MUL", "DIV", "MOD", "POP", "DUP", "SWP", "ROL"};
  int result = 0;
  int lenght = get_last_link_indice(0, list);
  _link* newlink = NULL;

  if (strcmp(instruction, op[0]) == 0)//ADD
  {
    if(list->next == NULL){
      list = pop_link(list);
      display_error(list);
    }
    result = list->value + get_n_link(1,list)->value;
    for (int i = 0; i < 2; ++i)
    {
      list = pop_link(list);
    }
    newlink = push_link(result,list);
  }else if (strcmp(instruction, op[1]) == 0)//SUB
  {
    if(list->next == NULL){
      list = pop_link(list);
      display_error(list);
    }
    result = list->value - get_n_link(1,list)->value;
    for (int i = 0; i < 2; ++i)
    {
      list = pop_link(list);
    }
    newlink = push_link(result,list);
  }else if (strcmp(instruction, op[2]) == 0)//MUL
  {
    if(list->next == NULL){
      list = pop_link(list);
      display_error(list);
    }
    result = list->value * get_n_link(1,list)->value;
    for (int i = 0; i < 2; ++i)
    {
      list = pop_link(list);
    }
    newlink = push_link(result,list);
  }else if (strcmp(instruction, op[3]) == 0)//DIV
  {
    if(list->next == NULL){
      list = pop_link(list);
      display_error(list);
    }
    int dividend = list->value;
    int diviser = get_n_link(1,list)->value;

    for (int i = 0; i < 2; ++i)
    {
      list = pop_link(list);
    }

    if(diviser != 0){
      result = dividend / diviser;
    }else{
      display_error(list);
    }
    newlink = push_link(result,list);

  }else if (strcmp(instruction, op[4]) == 0)//MOD
  {
    if(list->next == NULL){
      list = pop_link(list);
      display_error(list);
    }
    int dividend = list->value;
    int diviser = get_n_link(1,list)->value;

    for (int i = 0; i < 2; ++i)
    {
      list = pop_link(list);
    }

    if(diviser != 0){
      result = dividend % diviser;
    }else{
      display_error(list);
    }
    newlink = push_link(result,list);
  }else if (strcmp(instruction, op[5]) == 0)//POP
  {
    newlink = pop_link(list);
  }else if (strcmp(instruction, op[6]) == 0)//DUP
  {
    newlink = push_link(list->value, list);
  }else if (strcmp(instruction, op[7]) == 0)//SWP
  {
    if(list->next == NULL){
      list = pop_link(list);
      display_error(list);
    }
    result = get_n_link(lenght,list)->value;
    get_n_link(lenght,list)->value = get_n_link((lenght-1),list)->value;
    get_n_link(lenght-1,list)->value = result;
    newlink = list;
  }else if (strcmp(instruction, op[8]) == 0)//ROL
  {
    _link* lastlink = get_n_link(lenght,list);
    _link* currentlink;
    int n = lastlink->value; //L'indice commence a 0 d'où le -1
    int tmp;
    get_n_link((lenght+1)-n,list);
    get_n_link(lenght-1,list)->next = NULL;
    free(lastlink);
    lenght = get_last_link_indice(0,list);
    currentlink = get_n_link((lenght+1)-n,list);
    tmp = currentlink->value;
    get_n_link((lenght)-n,list)->next = currentlink->next ;
    free(currentlink);
    push_link(tmp, list);

    newlink = list;
  }
  return newlink;
}

int main(){
  _link* list;
  int N;

  list = NULL;

  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    char instruction[11];
    scanf("%s", instruction);
    if(is_instruction(instruction) == NULL){
      list = init_link(list, instruction);
    }
    else{
      list = do_instruction(list, instruction);
    }
  }
  display_link(0, list);
  free_link(list);
  return 0;
}
