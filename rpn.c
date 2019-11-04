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
_link* make_link(int val, _link* next){
  _link* link = (_link*)malloc(sizeof(_link));

  if(link == NULL)
  {
    fprintf(stderr, "Out of memory\n");
    exit(1);
  }

  link->value = val;
  link->next = next;

  return link;
}
//Affiche la liste
void display_link(_link* list){
    printf("%d\n", list->value);
  if (list->next != NULL)
   display_link(list->next);
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
  if (isdigit(value[0]))
  {
    int n;
    n = (int) strtol(value, NULL, 10);

    return make_link(n, list);
  }else{
    fprintf(stderr, "Value is not allowed\n");
    exit(3);
  }
}

//Recupère la n valeur
int get_link_n_last_value(int n, _link* list){
  if (list == NULL)
  {
    fprintf(stderr, "Empty list\n");
    exit(3);
  }
  if(n <= 0)
    return list->value;
  if (list->next != NULL)
    return get_link_n_last_value(n-1, list->next);
  return n;
}

//Execute les instructions
_link* do_instruction(_link* list, char* instruction){
  char op[9][4] = {"ADD", "SUB", "MUL", "DIV", "MOD", "POP", "DUP", "SWP", "ROL"};
  int result = 0;
  _link* newlink = NULL;

  if (strcmp(instruction, op[0]) == 0)
  {
    result = get_link_n_last_value(1,list) + list->value;
    for (int i = 0; i < 2; ++i)
    {
      list = pop_link(list);
    }
    newlink = make_link(result,list);
  }else if (strcmp(instruction, op[1]) == 0)
  {
    result = get_link_n_last_value(1,list) - list->value;
    for (int i = 0; i < 2; ++i)
    {
      list = pop_link(list);
    }
    newlink = make_link(result,list);
  }else if (strcmp(instruction, op[2]) == 0)
  {
    result = get_link_n_last_value(1,list) * list->value;
    for (int i = 0; i < 2; ++i)
    {
      list = pop_link(list);
    }
    newlink = make_link(result,list);
  }else if (strcmp(instruction, op[3]) == 0)
  {


  }else if (strcmp(instruction, op[4]) == 0)
  {

  }else if (strcmp(instruction, op[5]) == 0)
  {

  }else if (strcmp(instruction, op[6]) == 0)
  {

  }else if (strcmp(instruction, op[7]) == 0)
  {

  }else if (strcmp(instruction, op[8]) == 0)
  {

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


  display_link(list);



  free_link(list);

  return 0;
}
