#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_old/lista_com_cabeca.h"
#include "registro_paciente.h"


No* criar_registro_pacientes(){
    return criar_lista();
}

//Input sendo o nome do Paciente
unsigned int criar_id(const char *x){
   unsigned int id = 0;
    while (*x) {
        id = id * 31 + (unsigned char)(*x);
        x++;
    }
    return id;
    //output é o id
    //todo e qualquer lugar que for preciso entrar com id nestas funções é só passar esta função com o nome
}

//input(Lista encadeada,nome do paciente,aqui entra o id mas é só passar a função criar_id(nome do paciente))
void adicionar_paciente(No* x, const char *y, int z){
    paciente novo = {0};
    novo.tipo = z;
    strncpy(novo.nome, y, sizeof(novo.nome) - 1);
    adicionar_final(x, novo, criar_id(y));
}

//input(Lista,criar_id(nome do paciente))
void excluir_paciente(No* L, unsigned int id){
    remover_valor(L,id);
}

//input(lista)
void imprimir_lista_paciente(No *x){
    No *p = x;
    if(p->prox != NULL)
        while(p->prox != NULL){
            p = p->prox;
            printf("Id do paciente: %u\nNome do Paciente: %s\nTipo de Atendimento %d\n\n",p->id,p->pessoa.nome,p->pessoa.tipo);
        }
    else{
        printf("Lista Vazia");
    }
}

//input(lista,criar_id(nome do paciente))
No *pesquisar_paciente(No *x, unsigned int y){
    No *q = (No*) malloc(sizeof(No));
    q = x->prox;
    if (buscar_valor(q,y) == 1){
        while(q->prox->id != y){
            q = q->prox;   
        }
    } else{
        return NULL;
    }
    return q;
    //retorna o indereço no qual esta o paciente em que foi pesquisado
    //função que menos testei, então da uma olhada se tiver meio zoada
}