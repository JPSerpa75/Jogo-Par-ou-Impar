#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct st_jogo{
  int Numero1, Numero2, Soma, OpC, OpU, Vitoria; 
}Jogo;

int main(void) {
  int cont=0, total=0, tam=1, Sair=1, VitUsuP=0, VitUsuI=0, Total=0;
  int VitPar=0, VitImpar=0;
  Jogo *Partida;
  FILE *Arquivo;
  Partida = malloc(tam*sizeof(Jogo));
  Arquivo = fopen("Dados.txt", "a");
  fclose(Arquivo);
  Arquivo = fopen("Dados.txt", "r");
  fscanf(Arquivo, "%d", &total);
  fscanf(Arquivo, "%d", &(Partida+cont)->OpU);
  while(total>cont && ((Partida+cont)->OpU==0 || (Partida+cont)->OpU==1) ){
    fscanf(Arquivo, "%d", &(Partida+cont)->Vitoria);
    fscanf(Arquivo, "%d", &VitUsuP);
    fscanf(Arquivo, "%d", &VitUsuI);
    cont++;
    Partida = realloc(Partida, (cont+1)*sizeof(Jogo));
    //printf("\nAqui");
    fscanf(Arquivo, "%d", &total);
    fscanf(Arquivo, "%d", &(Partida+cont)->OpU);
  }
  fclose(Arquivo);
  Sair=1;

  while(Sair==1){
    printf("\n\tJOGO DO PAR OU ÍMPAR\n\n");
    
    // A partir de 7 jogadas o computador passa a escolher a opcao com mais vitoria
    for(int i=0; i<cont; i++){
      if((Partida+i)->Vitoria==0){
        VitPar++;
      }else if((Partida+i)->Vitoria==1){
        VitImpar++;
      }
    }
    
    if(cont<7){
      srand(time(NULL));
      (Partida+cont)->OpC=rand()%2;   
    }else{
      if(VitPar>=VitImpar){
        (Partida+cont)->OpC=0;
      }else{
        (Partida+cont)->OpC=1;
      }
    }

    
    if((Partida+cont)->OpC==0){
      printf("\nO Computador escolheu par\n");
      printf("\nVoce é ímpar\n");
      (Partida+cont)->OpU=1;
    }else if((Partida+cont)->OpC==1){
      printf("\nO Computador escolheu ímpar\n");
      printf("\nVoce é par\n");
      (Partida+cont)->OpU=0;
    }
    
    (Partida+cont)->Numero1=rand()%11;
    (Partida+cont)->Numero2=-1;
    while((Partida+cont)->Numero2<0 || (Partida+cont)->Numero2>10){
      printf("Digite um numero entre 0 e 10: ");
      scanf("%d", &(Partida+cont)->Numero2);
    }
      
    (Partida+cont)->Soma=((Partida+cont)->Numero1+(Partida+cont)->Numero2);
    printf("\nComputador jogou %d", (Partida+cont)->Numero1);
    printf("\nUsuário jogou %d", (Partida+cont)->Numero2);
    printf("\nResultado %d", (Partida+cont)->Soma);
    
    if((Partida+cont)->Soma%2==0){
      (Partida+cont)->Vitoria=0;
      if((Partida+cont)->OpC==0){
        printf("\nVencedor foi o Computador\n");
      }else{
        printf("\nVencedor foi o Usuário\n");
        VitUsuP++;
      }
    }
    if((Partida+cont)->Soma%2==1){
      (Partida+cont)->Vitoria=1;
      if((Partida+cont)->OpC==1){
        printf("\nVencedor foi o Computador\n");
      }else{
        printf("\nVencedor foi o Usuário\n");
        VitUsuI++;
      }
    }  

    printf("\nVitórias do Usuário com PAR: %d", VitUsuP);
    printf("\nVitórias do Usuário com ÍMPAR: %d\n", VitUsuI);

    Arquivo=fopen("Dados.txt", "a");
    if(Arquivo==NULL){
      printf("ERRO!\nFalha ao abrir o arquivo\n");
      exit(0);
    }
    total=cont+1;
    fprintf(Arquivo, "\n%d", total);
    fprintf(Arquivo, "\n%d", (Partida+cont)->OpU);
    fprintf(Arquivo, "\n%d", (Partida+cont)->Vitoria);
    fprintf(Arquivo, "\n%d", VitUsuP);
    fprintf(Arquivo, "\n%d\n", VitUsuI);
    fclose(Arquivo);
    
    printf("\n- Digite 1 para continuar jogando");
    printf("\n- Digite qualquer outro valor para sair");
    printf("\n- Escolha: ");
    scanf("%d", &Sair);

 
    cont++;
    Partida = realloc(Partida, (cont+1)*sizeof(Jogo));
    
  }
  printf("\nPrograma Finalizado");
}