#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>

#define MAX_LEN 256
#define TABLE_LEN 10

typedef struct 
{
    char name[MAX_LEN];
    int age;
}person;

person *hash_table[TABLE_LEN];

void init_hash_table(){
    for(int i=0; i<TABLE_LEN; i++){
        hash_table[i] = NULL;
    }
}

unsigned int hashfn(char *name){
    unsigned int sum = 0;
    int len = strnlen(name, MAX_LEN);
    for (int i=0; i<len; i++){
        sum += name[i];
        sum *= i;
    }
    sum = sum%TABLE_LEN;
    
    return sum;
}

void print_hash_table(){
    for(int i=0; i<TABLE_LEN; i++){
        if(hash_table[i] == NULL){
            printf("\t%i\t------\n", i);
        }
        else{
            printf("\t%i\t%s\n",i, hash_table[i]->name);
        }
    }
}

bool insert_into_hash_table(person *p){
    unsigned int pos = hashfn(p->name);
    if(hash_table[pos] !=  NULL){
        return false;
    }
    hash_table[pos] = p;
    return true;
}

person *lookup_hash_table(person *p){
    char *name = p->name;
    unsigned int pos = hashfn(name);
    if(hash_table[pos] == NULL){
        return NULL;
    }
    else{
        return hash_table[pos];
    }
}

void delete_from_hash_table(person *p){
    char *name = p->name;
    unsigned int pos = hashfn(name);
    if(hash_table[pos] != NULL){
        hash_table[pos] = NULL;
    }
}


int main(){
    
    init_hash_table();
    person anirudh = {.name = "Anirudh", .age = 12};
    insert_into_hash_table(&anirudh);
    print_hash_table();
    person *found = lookup_hash_table(&anirudh);
    if(found == NULL){
        printf("Person not found\n");
    }
    else{
        printf("Person %s found\n", found->name);
    }
    delete_from_hash_table(&anirudh);
    print_hash_table();
    return 0;
}