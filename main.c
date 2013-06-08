/***************************
Copyright (C) 2010-2013

filename: main.c
date: Thu Jun 06 21:44:36 2013
author: Kohn<3100102881@zju.edu.cn>
comment: Compiler Design Course Project

***************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "parser.tab.h"
extern int yylineno;
struct node{
     char name[128];
     int type;
     struct node* next;
};
struct node* hash_table[SIZE];
int main(int argc, char *argv[])
{
     int i;
     struct node* tmp = NULL;
     struct node* current = NULL;

     for(i=0;i<SIZE;i++)
          hash_table[i] = NULL;
     yylineno = 1;
     if(argc == 2)
     {
          FILE *fp = fopen(argv[1], "r");
          yyrestart(fp);
          yyparse();
          fclose(fp);
     }
     else
     {
          FILE *fp = fopen("code", "r");
          yyrestart(fp);
          yyparse();
          fclose(fp);
     }
     /* delete */
     for(i=0;i<SIZE;i++)
     {
          current = hash_table[i];
          while(current!=NULL)
          {
               tmp = current;
               current = current->next;
               free(tmp);
          }
     }
     return 0;
}
int hashcode(char *key)
{
     int temp = 0;
     int i = 0;
     while(key[i] != '\0')
     {
          temp = ((temp<<SHIFT) + key[i]) % SIZE;
          i++;
     }
     return temp;
}

struct node* new_node()
{
     struct node* newnode = (struct node*)malloc(sizeof(struct node));
     newnode->next = NULL;
     newnode->type = -1;
     return newnode;
}
void insert(char* name, int type)
{
     int key = hashcode(name);
     struct node* current = hash_table[key];
     struct node* newnode = new_node();
     int length = strlen(name);
     int i;
     /* newnode->name = strdup(name); */
     strcpy(newnode->name, name);
     newnode->type = type;
#ifdef DEBUG
     printf ("new node type: %d\n", newnode->type);
#endif
     if(hash_table[key]==NULL)
          hash_table[key] = newnode;
     else
     {
          newnode->next = hash_table[key]->next;
          hash_table[key]->next = newnode;
     }
}
int lookup(char* name)
{
#ifdef DEBUG
     printf ("lookingfor %s\n", name);
#endif
     int key = hashcode(name);
     struct node* current = hash_table[key];
     int i = 0;
     while(current != NULL)
     {
          i++;
          if(strcmp(current->name, name) == 0) /* right node contains the given name */
          {
#ifdef DEBUG
               printf ("find %s, type = %d\n", name, current->type);
#endif
               return current->type;
          }
          current = current->next;
     }
#ifdef DEBUG     
     printf ("cannot find %s\n", name);
#endif
     return -1;                 /* cannot find the ID */
}

int typeEqual(int type, int want)
{
     return type==want;
}

void type_error(int lineno)
{
     fprintf(stderr, "type error in line: %d\n", lineno);
}

int isArrayType(int type)
{
     return 0;
}

void makeTypeNode(int arraytype, int num, int type)
{
     
}