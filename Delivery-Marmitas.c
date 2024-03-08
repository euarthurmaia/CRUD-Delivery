#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct de Pedidos
typedef struct ST_Pedidos {
  char nome[50];
  char endereco[50];
  int ID;
  char hora[7];
  char tamanho[5];
  struct ST_Pedidos *Prox;
} Pedidos;

typedef struct ST_Descritor {
  Pedidos *Prim;
} Descritor;

Pedidos *PrimeiroP = NULL;
Descritor Lista;

// Função para adicionar os pedidos
void FazerPedido(Pedidos *Novo, int Pos) {
  if (Pos == 1) {
    Novo->Prox = Lista.Prim;
    Lista.Prim = Novo;
    return;
  }
  if (Lista.Prim == NULL) {
    Novo->Prox = Lista.Prim;
    Lista.Prim = Novo;
    printf("\n\nNenhum pedido encontrado. Pedido inserido na posição 1!\n");
    return;
  }
  Pedidos *Aux = Lista.Prim;
  int cont = 0;
  while (cont < Pos - 2) {
    if (Aux->Prox == NULL) {
      break;
    }
    Aux = Aux->Prox;
    cont++;
  }
  Novo->Prox = Aux->Prox;
  Aux->Prox = Novo;
}

// Função para liberar os pedidos
Pedidos *Entregar(int Pos) {
  Pedidos *Ret, *Aux;
  Aux = Lista.Prim;
  if (Lista.Prim == NULL) {
    printf("Lista vazia!\n");
    return NULL;
  }
  if (Pos == 1) {
    Ret = Lista.Prim;
    Lista.Prim = Ret->Prox;
  } else {
    int cont = 0;
    while (cont < Pos - 2) {
      if (Aux->Prox == NULL) {
        return NULL;
      }
      Aux = Aux->Prox;
      cont++;
    }
    if (Aux->Prox == NULL) {
      return NULL;
    }
    Ret = Aux->Prox;
    Aux->Prox = Ret->Prox;
  }
  return Ret;
}

// Função para exibir os pedidos
void ExibirPedidos() {
  Pedidos *Aux = Lista.Prim;

  if (Aux == NULL) {
    printf("\n\t\t\t------------------------\n");
    printf("\t\t\tNenhum pedido foi feito!");
    printf("\n\t\t\t------------------------\n");
    return;
  }
  printf("----------------------PEDIDOS------------------------\n");
  while (Aux != NULL) {
    printf("\nNome: %s \t Endereço: %s\nID: %d\n\nHora: %s \t Tamanho: %s\n",
           Aux->nome, Aux->endereco, Aux->ID, Aux->hora, Aux->tamanho);
    printf("\n*****************************************************\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
    Aux = Aux->Prox;
  }
}

// Função para passagem de parametro
int Parametro(int Criterio, Pedidos *Elem) {
  // 1 - Ordenar por Hora
  // 2 - Ordenar por Tamanho

  if (Criterio == 1) {
    if (strcmp(Elem->hora, Elem->Prox->hora) > 0) {
      return 1;
    }
    return 0;
  }
  if (Criterio == 2) {

    if (strcmp(Elem->tamanho, Elem->Prox->tamanho) < 0) {
      return 1;
    }
    return 0;
  }
}

// Função para ordenação
void BubbleSort(int Criterio) {
  // 1 - Ordenar por Hora
  // 2 - Ordenar por Tamanho
  int Troca = 1;
  Pedidos *Ant, *Aux;

  if (Lista.Prim == NULL) {
    return;
  }
  Aux = Lista.Prim;
  if (Aux->Prox == NULL) {
    return;
  }
  while (Troca == 1) {
    Aux = Lista.Prim;
    Troca = 0;
    if (Parametro(Criterio, Aux)) {
      Pedidos *Temp2 = Aux->Prox;
      Aux->Prox = Temp2->Prox;
      Temp2->Prox = Aux;
      Lista.Prim = Temp2;
      Troca = 1;
    } else {
      Aux = Aux->Prox;
    }
    Ant = Lista.Prim;
    while (Aux->Prox != NULL) {
      if (Parametro(Criterio, Aux)) {
        Pedidos *Temp2 = Aux->Prox;
        Aux->Prox = Temp2->Prox;
        Temp2->Prox = Aux;
        Ant->Prox = Temp2;
        Troca = 1;
      } else {
        Aux = Aux->Prox;
      }
      Ant = Ant->Prox;
    }
  }
}

int main(void) {
  setlocale(LC_ALL, "portuguese");
  int i = 0;
  int j = 0;
  int p;
  int criterio;
  Pedidos *P1;
  printf("=====================================================\n");
  printf("-------------------TELA DE PEDIDO--------------------\n");
  printf("\nFazer pedido? (1 - SIM \t 2 - NÃO)\n");
  printf("\n");
  scanf("%d", &i);
  printf("-----------------------------------------------------\n");
  printf("=====================================================\n");

  if (i == 2) {
    printf("-----------------------------------------------------\n");
    printf("\nProcedimento encerrado. Tenha um bom dia!\n");
    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("=====================================================\n");
    return 0;
  }
  while (i != 5) {
    printf("\n\n");
    printf("=====================================================\n");
    printf("----------------------PEDIDOS------------------------\n");
    printf("\n1 - Fazer Pedido \t 2 - Entregar \t 3 - Exibir\n \n4 - Ordenar "
           "\t \t 5 - Sair\n\n");
    scanf("%d", &i);
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");

    if (i == 5) {
      printf("-----------------------------------------------------\n");
      printf("\nProcedimento encerrado. Tenha um bom dia!\n");
      printf("\n");
      printf("-----------------------------------------------------\n");
      printf("=====================================================\n");
      return 0;
    }

    switch (i) {
    case 1:
      P1 = (Pedidos *)malloc(sizeof(Pedidos));
      P1->Prox = NULL;

      printf("\n\n");
      printf("=====================================================\n");
      printf("----------------------PEDIDOS------------------------\n");
      printf("\nNome: ");
      scanf("%s", P1->nome);
      printf("\nEndereço: ");
      getchar();
      fgets(P1->endereco, sizeof(P1->endereco), stdin);
      printf("\nID: ");
      scanf("%d", &P1->ID);
      printf("\nHora(hh:mm): ");
      scanf("%s", P1->hora);
      printf("\nDigite o tamanho da sua fome (P, M ou G): ");
      scanf("%s", P1->tamanho);
      printf("\nDigite o número do pedido: ");
      scanf("%d", &p);
      FazerPedido(P1, p);
      printf("\n-----------------------------------------------------\n");
      printf("=====================================================\n");
      break;

    case 2:
      if (Lista.Prim == NULL) {
        printf("\n\t\tNão há pedidos para serem entregues!\n");
      } else {
        printf("\n\n");
        printf("=====================================================\n");
        printf("------------------TELA DE ENTREGAS-------------------\n");
        printf("\nDigite o número do pedido que deseja liberar: \n\n");
        scanf("%d", &p);
        P1 = Entregar(p);

        if (P1 != NULL) {
          printf("\n*****************PEDIDO LIBERADO*********************\n");
          printf("\nNome: %s\n\nEndereço: %s\nID: %d\n\n"
                 "Hora: %s \n\n"
                 "Tamanho: %s\n\n",
                 P1->nome, P1->endereco, P1->ID, P1->hora, P1->tamanho);
          printf("\n*****************************************************\n");
          printf("\n-----------------------------------------------------\n");
          printf("=====================================================\n");

          free(P1);
        }
        break;
      }

    case 3:
      ExibirPedidos();
      if (Lista.Prim != NULL) {
        printf("\n=====================================================\n");
        printf("--------------------NÃO ORDENADO---------------------\n");
        ExibirPedidos();
      }
    if (criterio == 1) {
      printf("\n=====================================================\n");
      printf("----------------ORDENADO POR HORÁRIO-----------------\n");
      ExibirPedidos();
  }
  if (criterio == 2) {
    printf("\n=====================================================\n");
    printf("----------------ORDENADO POR TAMANHO-----------------\n");
    ExibirPedidos();
}
break;

case 4:
if (Lista.Prim == NULL) {
  printf("\n\t\tNão há pedidos para serem ordenados!\n");
  printf("\n\t\t\t------------------------\n");
  printf("\t\t\tNenhum pedido foi feito!");
  printf("\n\t\t\t------------------------\n");
} else {
  printf("\n\n");
  printf("=====================================================\n");
  printf("------------------TELA DE ORDENAÇÃO------------------\n");
  printf("\nDeseja ordenar por:\n\n1 - Horario\t\t2 - Tamanho\n\n");
  scanf("%d", &criterio);
  BubbleSort(criterio);
  if (criterio == 1) {
    printf("\nOrdenado por horário!");
    printf("\nDigite 3 para exibir a alteração\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
  }
  if (criterio == 2) {
    printf("\nOrdenado por tamanho!");
    printf("\nDigite 3 para exibir a alteração\n");
    printf("\n-----------------------------------------------------\n");
    printf("=====================================================\n");
  }
  break;
}
}
}
return 0;
}
