/**-Auteur : Thomas ABREU DIAS aka BOYA-**/
/*-Dépot GIT :
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
_link* make_link(char* ope, int val, _link* next){

  if(val  != 0 && ope != NULL )
  {
    fprintf(stderr, "Only one of the attribut need to don't be NULL\n");
    exit(2);
  }

  _link* link = (_link*)malloc(sizeof(_link));
  if(link == NULL)
  {
    fprintf(stderr, "Out of memory\n");
    exit(1);
  }

  if(ope != NULL){
    link->operation = (char*) malloc(sizeof(char)*4);
    if(link->operation == NULL)
    {
      fprintf(stderr, "Out of memory\n");
      exit(1);
    }
    strcpy(link->operation, ope);
  }

  link->operation = NULL;
  link->value = val;
  link->next = next;

  return link;
}
//Affiche la liste
void display_link(_link* list){
  if (list->operation == NULL)
    printf("%d\n", list->value);
  else
    printf("%s\n", list->operation );
  if (list->next != NULL)
   display_link(list->next);
}
//Libère l'espace memoire utilisé par la liste
void free_link(_link* list)
{
  if (list != NULL)
  {
    if (list->operation !=NULL)
    {

      free(list->operation); // pb de free un char non free !!??
    }


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
_link* init_link(_link* list, char* instruction){
  if (is_instruction(instruction) != NULL)
  {
   return make_link(instruction, 0, list);
 }else
 {
  int n;
  n = (int) strtol(instruction, NULL, 10);

  return make_link(NULL, n, list);
}
}
//Recupère la n valeur
int get_link_n_last_value(int n, _link* list){
  if (list == NULL)
  {
    fprintf(stderr, "Empty list\n");
    exit(3);
  }
  if(n <= 0){
    if (list->operation == NULL)
    {
      return list->value;
    }
  }
  if (list->next != NULL)
    return get_link_n_last_value(n-1, list->next);
  return n;
}

//Execute les instructions
_link* do_instruction(_link* list){
  char op[9][4] = {"ADD", "SUB", "MUL", "DIV", "MOD", "POP", "DUP", "SWP", "ROL"};
  int result;
  _link* newlink;
  if (strcmp(list->operation, op[0]) == 0)
  {
    list = pop_link(list);
    result = get_link_n_last_value(0, list);
    list = pop_link(list);
    result += get_link_n_last_value(0, list);
    list = pop_link(list);
    newlink = make_link(NULL, result, list);

  }else if (strcmp(list->operation, op[1]) == 0)
  {
    list = pop_link(list);
    result = get_link_n_last_value(0, list);
    list = pop_link(list);
    result -= get_link_n_last_value(0, list);
    list = pop_link(list);
    newlink = make_link(NULL, result, list);
  }else if (strcmp(list->operation, op[2]) == 0)
  {
    int tmp;
    list = pop_link(list);
    result = get_link_n_last_value(0, list);
    list = pop_link(list);
    tmp = get_link_n_last_value(0, list);
    if (tmp == 0)
    {
      fprintf(stderr, "Division by 0 not allowed\n");
      exit(4);
    }
    result = result / tmp;
    list = pop_link(list);
    newlink = make_link(NULL, result, list);
  }else if (strcmp(list->operation, op[3]) == 0)
  {
   int tmp;
   list = pop_link(list);
   result = get_link_n_last_value(0, list);
   list = pop_link(list);
   tmp = get_link_n_last_value(0, list);
   if (tmp == 0)
   {
    fprintf(stderr, "Division by 0 not allowed\n");
    exit(4);
  }
  result = result % tmp;
  list = pop_link(list);
  newlink = make_link(NULL, result, list);
}else if (strcmp(list->operation, op[4]) == 0)
{

}else if (strcmp(list->operation, op[5]) == 0)
{

}else if (strcmp(list->operation, op[6]) == 0)
{

}else if (strcmp(list->operation, op[7]) == 0)
{

}else if (strcmp(list->operation, op[8]) == 0)
{

}else
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
    list = init_link(list, instruction);
  }


  //list = do_instruction(list);
  display_link(list);



  free_link(list);

  return 0;
}
