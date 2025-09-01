#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
};

struct List {
    int quant;
    struct Node* data;
    struct Node* top;
};

struct List* criarLista(int value){ // ------ FUNCIONA ------

    struct List* list = (struct List*)malloc(sizeof(struct List));
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node -> value = value;
    list -> data = node;
    list -> top = node;
    list -> quant = 1;
    
    printf("lista criada! valor inicial: %d\n", value);
    
    return list;
};

void push_end(struct List* list, int value){// ------ FUNCIONA ------

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node -> value = value;
    new_node -> prev = list -> top;
    list -> top -> next = new_node;
    list -> top = new_node;
    list -> quant += 1;
    
    printf("\nnovo nó criado! valor do nó: %d\n\n", value);
};

void push_start(struct List* list, int value){// ------ FUNCIONA ------

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node -> value = value;
    new_node -> next = list -> data;
    list -> data -> prev = new_node;
    list -> data = new_node;
    list -> quant += 1;
    
    printf("\nnovo nó criado no início! valor do nó: %d\n\n", value);
}

void push_any(struct Node* obj_list, int index, struct List* list, int value) {
    if (index > list->quant || index < 0) {
        printf("Índice inválido.\n");
        return;
    }

    if (index > 0) {
        // Continua buscando o nó da posição desejada
        push_any(obj_list->next, index - 1, list, value);
    } else {
        // Inserir ANTES de obj_list

        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->value = value;

        new_node->next = obj_list;
        new_node->prev = obj_list->prev;

        if (obj_list->prev != NULL) {
            obj_list->prev->next = new_node;
        } else {
            // Está inserindo no início da lista
            list->data = new_node;
        }

        obj_list->prev = new_node;

        list->quant += 1;
    }
}

void forward(struct Node* obj_list, int item_index){// ------ FUNCIONA ------
    
    if (obj_list -> next == NULL){//se não tiver mais valor, devolve apenas o último
        printf("%d\tindice: %d\n", obj_list -> value, item_index);//
    }
    else{
        printf("%d\tindice: %d\n", obj_list -> value, item_index);
        return(forward(obj_list = obj_list -> next, item_index += 1));
    }
}

void backward(struct Node* obj_list, int item_index){ // ------ FUNCIONA ------

    if (obj_list -> prev == NULL){//se não tiver mais valor, devolve apenas o último
        printf("%d\tindice: %d\n", obj_list -> value, item_index - 1);//
    }
    else{
        printf("%d\tindice: %d\n", obj_list -> value, item_index - 1);
        return(backward(obj_list = obj_list -> prev, item_index -= 1));
    }
}
//                                data     indice      lista          numero
void access_posi(struct Node* obj_list, int index, struct List* list, int edit){
    // ------ FUNCIONA ------
    if(list -> quant < index){
        printf("\ninsira um índice válido\n");
    }
    else{
        if (index > 0){
            return(access_posi(obj_list = obj_list -> next, index - 1, list, edit));
        }
        else {
            obj_list -> value = edit;
            printf("\no valor da posição agora é: %d\n", obj_list -> value);
        }
    }
}

void remove_end(struct List* list){// ------ FUNCIONA ------
    
    list -> top = list -> top -> prev;
    free(list -> top -> next);
    list -> top -> next = NULL;
    list -> quant -= 1;
}

void remove_start(struct List* list){
    
    if (list->quant == 1) {
        printf("\nNão pode remover pois a lista só tem um item\n");
        return;
    }
    
    struct Node* temp = list->data;
    list->data = list->data->next;  // Atualiza o ponteiro 'data' para o próximo nó

    if (list->data != NULL) {
        list->data->prev = NULL;  // O novo primeiro nó não tem anterior
    }

    free(temp);  // Libera a memória do nó removido
    
    list -> quant -= 1;

    printf("O primeiro nó foi removido.\n");
}

//                                data     indice      lista
void remove_any(struct Node* obj_list, int index, struct List* list){
    
    if(list -> quant <= 1){
        printf("\nNão pode remover pois a lista só tem um item\n\n");
        return;
    }
    
    if(index > list -> quant){
        printf("\nPosição inexistente\n\n");
        return;
    }
    
    // ------ FUNCIONA ------
    if(list -> quant < index){
        printf("\ninsira um índice válido\n");
    }
    else{
        if (index > 0){
            return(remove_any(obj_list = obj_list -> next, index - 1, list));
        }
        else {
            //é aqui onde eu devo alterar. Armazenar o nó para que ele possa passar seus valores e depois ser dealocado com "free(temp)"
            
            struct Node* temp = obj_list; //nó a ser eliminado
            struct Node* next_node = obj_list -> next; //nó depois dele
            struct Node* prev_node = obj_list -> prev; // nó antes dele
            
            next_node -> prev = temp -> prev;
            prev_node -> next = temp -> next;
            
            list -> quant -= 1;
            
            temp -> next = NULL;
            temp -> prev = NULL;
            free(temp);
            
        }
    }
}

int main(){
    int numero;
    int escolha;
    int index;
    
    printf("qual valor deseja que a lista inicie?\nvalor: ");
    scanf("%d", &numero);
    
    struct List* list = criarLista(numero);
    
    printf("\nperfeito! Agora, o que deseja fazer com a sua lista?\n\n");
    
    while(true){
        printf("digite \"1\", para inserir um novo valor no fim\n");
        printf("digite \"2\", para inserir um novo valor no começo\n");
        printf("digite \"3\", para inserir um novo valor entre outros valores\n");
        printf("digite \"4\", para ver a lista do começo ao fim\n");
        printf("digite \"5\", para ver a lista do fim ao começo\n");
        printf("digite \"6\", para remover um elemento no fim\n");
        printf("digite \"7\", para remover um elemento no começo\n");
        printf("digite \"8\", para remover um elemento de alguma posição\n");
        printf("digite \"9\", para editar um elemento\n");
        
        scanf("%d", &escolha);
        
        switch (escolha) {
            case 1:
                printf("qual valor deseja inserir?\nValor: ");
                scanf("%d", &numero);
                push_end(list, numero);
                break;
            case 2:
                printf("qual valor deseja inserir?\nValor: ");
                scanf("%d", &numero);
                push_start(list, numero);
                break;
            case 3:
                printf("\ndigite a posição que quer, e seu valor será inserido entre este valor e o anterior\nposição: ");
                scanf("%d", &index);
                printf("valor: ");
                scanf("%d", &numero);
                push_any(list -> data, index, list, numero);
                printf("\n");
                break;
            case 4:
                printf("\n");
                forward(list -> data, 0);
                printf("\n");
                break;
            case 5:
                printf("\n");
                backward(list -> top, list -> quant);
                printf("\n");
                break;
            case 6:
                remove_end(list);
                break;
            case 7:
                remove_start(list);
                break;
            case 8:
                printf("digite a posição que quer remover\nposição: ");
                scanf("%d", &index);
                remove_any(list -> data, index, list);
                break;
            case 9:
                //                                data     indice      lista          numero
                printf("\ndigite a posição que quer editar\nPosição: ");
                scanf("%d", &index);
                printf("Valor: ");
                scanf("%d", &numero);
                access_posi(list -> data, index, list, numero);
                break;
            default:
                printf("favor inserir um valor válido\n");
        }
        //system("cls");

    }
    
    return 0;
}