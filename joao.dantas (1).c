/**************************************************
*
* Joao Paulo da Silva Dantas e Arthur Cabral da Silva
* Trabalho 2
* Professor(a): Diego Padilha
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEICULOS 5
#define NUM_PILHAS 3

/* Armazena informacoes de um veiculo estacionado em uma pilha */
typedef struct cel {
  char placa[9];
  struct cel *prox;
} veiculo;
/* Armazena informacoes de uma pilha */
typedef struct {
  int veiculos; /* Quantidade de veiculos estacionados */
  veiculo *topo; /* Topo da pilha */
} pilha;

/* Armazena informacoes do estacionamento */
typedef struct {
  char data[11];
  pilha P[NUM_PILHAS]; /* Armazena as pilhas P0, P1, ..., NUM_PILHAS-1 */
} estacionamento;

estacionamento *ESTACIONAMENTO_TEMP;
veiculo *VEICULO_TEMP;
char *PLACA_TEMP;

int obterData(estacionamento *estac){

  scanf("%10s", estac->data);

  return 0;
}

void imprimirData(estacionamento *estac){
  printf("%s\n", estac->data);
}

void iniciarPilhas(estacionamento *estac){

  for(int i=0; i<3; i++){

    estac->P[i].veiculos = 0;
    estac->P[i].topo = NULL;

  }
}

int obterPilhaMaisVazia(estacionamento *estac){
  int minI = 0;
  int minVeiculos = estac->P[0].veiculos;

  for (int i = 1; i < 3; i++){
    if (estac->P[i].veiculos < minVeiculos){
      minI = i;
      minVeiculos = estac->P[i].veiculos;
    }
    
  }
  if(minVeiculos == MAX_VEICULOS){
    return -1;
  }
  return minI;
}

int buscarPlacaNaPilha(int indicePilha, char* placaProcurada){

  veiculo *veicAtual = ESTACIONAMENTO_TEMP->P[indicePilha].topo;

  if(veicAtual == NULL){
    return -1;
  }

  if(strcmp(placaProcurada, veicAtual->placa) == 0){
    return indicePilha;
  }
  
  veicAtual = veicAtual->prox;
  while (veicAtual != NULL){
    if(strcmp(placaProcurada, veicAtual->placa) == 0){
      return indicePilha;
    }
    veicAtual = veicAtual->prox;
  }


  return -1;
}

int buscarPlacaNoEstacionamento(char* placaProcurada){
  int resultadoDaBusca;

  for (int indicePilha = 0; indicePilha < 3; indicePilha++){
    resultadoDaBusca = buscarPlacaNaPilha(indicePilha, placaProcurada);
    if(resultadoDaBusca != -1){
        return indicePilha;
    }
  }
  return -1;
  
}

void inserirVeiculo(veiculo *veic, int indicePilha){

  veic->prox = ESTACIONAMENTO_TEMP->P[indicePilha].topo;
  ESTACIONAMENTO_TEMP->P[indicePilha].topo = veic;
  ESTACIONAMENTO_TEMP->P[indicePilha].veiculos++;

}

void retirarVeiculo(char* placaProcurada, int indicePilha){
  veiculo *veicAtual = ESTACIONAMENTO_TEMP->P[indicePilha].topo;

  if(strcmp(placaProcurada, veicAtual->placa) == 0){
    ESTACIONAMENTO_TEMP->P[indicePilha].topo = veicAtual->prox;
    ESTACIONAMENTO_TEMP->P[indicePilha].veiculos--;
    free(veicAtual);
    veicAtual = NULL;
    return;
  }
  
  veiculo *primeiroDaFila = NULL; // facilita a operacao com a fila
  veiculo *ultimoDaFila = NULL;  // controle da fila

  /*controle da fila*/
  primeiroDaFila = veicAtual; // primeiro e unico elemento da fila
  ultimoDaFila = veicAtual; // primeiro e ultimo da fila, porque e unico
  veicAtual = veicAtual->prox; // evita perder a referencia da pilha
  primeiroDaFila->prox = NULL; // controle da cabeca da fila

  veiculo *veicAux = NULL;
  while(veicAtual != NULL){
    if(strcmp(placaProcurada, veicAtual->placa) == 0){
      primeiroDaFila->prox = veicAtual->prox; // aponta a cabeca da fila para o topo da pilha
      ESTACIONAMENTO_TEMP->P[indicePilha].topo = ultimoDaFila;
      ESTACIONAMENTO_TEMP->P[indicePilha].veiculos--;
      free(veicAtual); 
      veicAtual = NULL;
      return;
    }
    veicAux = veicAtual->prox; // guarda o proximo elemento da pilha (1)
    veicAtual->prox = ultimoDaFila; // aumenta a fila (2.1)
    ultimoDaFila = veicAtual; // fecha a fila (2.2)
    veicAtual = veicAux; // incremento da iteracao (3)
  }
}

void imprimirPilha(int indicePilha){

  veiculo *veicAtual = ESTACIONAMENTO_TEMP->P[indicePilha].topo;

  if (veicAtual == NULL){
    printf("P%d:\n", indicePilha);
    return;
  }

  printf("P%d:%s", indicePilha, veicAtual->placa);

  veicAtual = veicAtual->prox;
  while (veicAtual != NULL){
    printf(",%s",veicAtual->placa);
    veicAtual = veicAtual->prox;
  }
  printf("\n");
  

}

estacionamento* criarEstacionamento(){

  estacionamento *estac = (estacionamento*)malloc(sizeof(estacionamento));

  iniciarPilhas(estac);

  obterData(estac);

  imprimirData(estac);

  return estac;

}

void destruirEstacionamento(estacionamento *estac){

    free(estac);
    estac = NULL;

}

char* obterPlaca(){

  char *placaTemp = (char* )malloc(9*sizeof(char));
  scanf("%9s", placaTemp);

  return placaTemp;
}

void imprimirPlaca(char* placaTemp){
  
  printf("%s\n", placaTemp);
}

veiculo* criarVeiculo(){

  veiculo *veic = (veiculo*)malloc(sizeof(veiculo));
  veic->prox = NULL;
  char *placaTemp = obterPlaca();
  strcpy(veic->placa,placaTemp);

  return veic;

}

void operacaoEntrada(){
  veiculo *veic = criarVeiculo();
  int pilhaMaisVazia = obterPilhaMaisVazia(ESTACIONAMENTO_TEMP);

  if (pilhaMaisVazia == -1){
    printf("C ");
  }else{
    inserirVeiculo(veic, pilhaMaisVazia);
    printf("E ");
  }
  
  imprimirPlaca(veic->placa);
  PLACA_TEMP = veic->placa;

}

void operacaoSaida(){
  char *placaTemp = obterPlaca();
  int pilhaEncontrada = buscarPlacaNoEstacionamento(placaTemp);

  if(pilhaEncontrada == -1){
    printf("N ");
  }else{
    retirarVeiculo(placaTemp, pilhaEncontrada);
    printf("S ");
  }
  imprimirPlaca(placaTemp);
}

void operacaoImprimir(){
  char nomePilha[2]; //0 = P, 1 = indice da pilha
  int indicePilha;

  scanf("%s", nomePilha);
  indicePilha = nomePilha[1] - 48; //conversao caractere para inteiro baseado na tabela ascii
  imprimirPilha(indicePilha);
}

void menu(){
  char opcao;

  do{
    scanf(" %c", &opcao);
    switch(opcao){  
      case 'I':
      operacaoImprimir();
      break;

      case 'E':
      operacaoEntrada();
      break;

      case 'S':
      operacaoSaida();
      break;

      default:
        break;
    }
  }while(opcao != 'F');
  printf("F\n\n");
}

int aplicacao(){
  char pularLinha;
  scanf("%c", &pularLinha);
  estacionamento *estac = criarEstacionamento();
  ESTACIONAMENTO_TEMP = estac;
  menu();
  destruirEstacionamento(estac);

  return 0;
}

int main(){
  int numIteracoes;

  scanf("%d", &numIteracoes);
  
  for (int i = 0; i < numIteracoes; i++){
    aplicacao();
  }

  return 0;
}