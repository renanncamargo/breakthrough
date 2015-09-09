#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/** Tamaho maximo de um nome
*/
#define MAX_NOME 52
/**
* Registro
*/
     typedef struct Registro {
     char * nome;
     int idade; 
     float altura;
     }Registro;
/**
* Lê uma linha do teclado e salva em no parametro linha.
2
* @param linha - string onde será lida a linha.
*/
void lelinha(char linha[]) {
    int top;
    char c;
    top = 0;
      while (getchar() != '\n'){
      linha[top++] = c;
     };
    linha[top] = '\0';
}
/**
* Construtor do registro
* @param nome - nome
* @param idade - idade
* @param altura - altura
* @return Registro criado.
*/
struct Registro * newReg(char nome[], int idade, float altura) {
    Registro * x = (Registro*)malloc(sizeof(Registro));
    strcpy(x->nome,nome);
    x->idade = idade;
    x->altura = altura;
    return x;
}
/**
* Converte o Registro para uma string.
* @param x - Registro
* @return registro convertido em string.
*/
char * toStringReg(char * buff, struct Registro * x) {
sprintf(buff, "[%s,%d,%.2f]", x->nome, x->idade, x->altura);
return buff;
}


struct Registro * readRegistro() {
char nome[MAX_NOME];
int idade;
float h;
lelinha(nome);
scanf("%d", &idade);
scanf("%f", &h);
struct Registro * o = newReg(nome, idade, h);
return o;
}
/**
* Registro que é o nó de uma árvore
*/
struct No {
char * nome;
     int idade; 
     float altura;
struct Registro * valor;
/** ramo de nós mais velhos e mais altos */
struct No * velhoAlto;
/** ramo de nós mais velhos e mais baixos (ou mesma altura) */
struct No * velhoBaixo;
/** ramo de nós mais novos (ou mesma idade) e mais altos */
struct No * novoAlto;
/** ramo de nós mais novos (ou mesma idade) e mais baixos (ou mesma altura) */
struct No * novoBaixo;
};
/**
* Construtor para a classe No.
* @param o - registro
* @return - nó criado
*/
struct No * newNo(struct Registro * o) {
No * x = (No*)malloc(sizeof(No));
    strcpy(x->nome,o->nome);
    x->idade = o->idade;
    x->altura = o->altura;
    return x;
}

int comparaTo(struct No * a, struct No * b) {
   if(a->idade>b->idade && a->altura>b->altura)
      return 1; //1 - (velho,alto) "a" mais velho e mais alto que "b"
   if(a->idade>b->idade && a->altura<b->altura) 
      return 2;//2 - (velho,baixo) "a" mais velho e -não- mais alto que "b".
   if(a->idade<b->idade && a->altura>b->altura)  
      return 3;//3 - (novo, alto) "a" -não- mais velho e mais alto que "b".
   if(a->idade<b->idade && a->altura<b->altura)
    return 4;//4 - (novo,baixo) "a" -não- mais velho e -não- mais alto que "b".      
}

      
/**
* Devolve 1 se a e b forem iguais, mesmo nome, idade e altura.
* Devolve 0 caso contrário.
* @param a
* @param b
* @return int - igual.
*/
int equals(struct Registro * a, struct Registro * b) {
	if(a->idade==b->idade && a->altura==b->altura && a->nome,b->nome)
      return 1;
    else
      return 0;
}
/**
* Insere um registro na árvore. Segue um dos quatro ramos descritos acima.
* @param x No
* @param obj registro a ser inserido.
*/
void insere(struct No ** T, struct No * x) {
    if((*T)==NULL){
        (*T)=x;
    }else{
    	if(comparaTo(*T,x)==1){
    	
       // arvore binaria de busca
         insere(&((*T)->velhoAlto),x);
     }
     if(comparaTo(*T,x)==2){
    	
       // arvore binaria de busca
         insere(&((*T)->velhoBaixo),x);
     }
     if(comparaTo(*T,x)==3){
    	
       // arvore binaria de busca
         insere(&((*T)->novoAlto),x);
     }
     if(comparaTo(*T,x)==4){
    	
       // arvore binaria de busca
         insere(&((*T)->novoAlto),x);
     }
        
}

}
/**
* Converte uma árvore para um xml, sem a tag inicial.
* @param x
*/
void imprime(struct No * x) {
     if (x != NULL){
       printf("%c", x->nome);
       printf("%d", x->idade);
       printf("%f", x->altura);
       
       
	   if(x->velhoAlto != NULL){
       printf("<R1>\n");
	   imprime(x->velhoAlto);
	   printf("<R1>\n");
       }
       if(x->velhoBaixo != NULL){
         printf("<R2>\n"); 
         imprime(x->velhoBaixo);
         printf("<R2>\n");
	   }
	   
       if(x->novoAlto != NULL){
         printf("<R3>\n");  
         imprime(x->novoAlto);
         printf("<R3>\n");
       }
       if(x->novoBaixo != NULL){
         printf("<R3>\n");    
         imprime(x->novoBaixo);
         printf("<R3>\n");  
     }
 }
}
/**
* Calcula o número de elementos de uma árvore.
* @param x
* @return tamanho
*/
int size(struct No * x) {
 if(x == NULL)
        return 0;
   else
        return 1 + size(&(*x->velhoAlto)) + size(&(*x->velhoBaixo) + size(&(*x->novoAlto) + size(&(*x->novoBaixo))));
}

/**
* Verifica o numero maior.
* @param a,b,c e d
* @return maior
*/

int maior(int a, int b, int c, int d){
    if(a > b && a > c && a > d)
        return a;
    if(b > a && b > c && b > d)
        return b;
    if(c > a && c > b && c > d)
        return c;
    if (d > a && d > b && d > c)
        return d;
}

/**
* Calcula altura de uma árvore.
* @param x
* @return altura
*/

int altura(struct No * x) {
if((x == NULL) || (x->velhoAlto == NULL && x->velhoBaixo == NULL && x->novoAlto == NULL && x->novoBaixo == NULL))
       return 0;
   else
       return 1 + maior(size(&(*x->velhoAlto)), size(&(*x->velhoBaixo)) , size(&(*x->novoAlto)) , size(&(*x->novoBaixo)));
}
/**
* Faz a busca do registro o na arvore T. Devolve o nó x mais alto dá árvore
* com x->valor=o. Caso não exista, devolve NULL.
*
* @param T - árvore de busca.
* @param o - registro a ser buscado.
* @return x, se x->valor=0, NULL caso contrário.
*/
struct No * buscar(struct No * T, struct Registro * o) {
    if (T==NULL || ((strcmp((T)->nome,o->nome)<0) && T->idade == o->idade && T->altura == o->altura))
      return T; /* árvore vazia: não encontrou */
    if(T->idade>o->idade && T->altura>o->altura)
    	 return buscar(T->velhoAlto, o);
    if(T->idade>o->idade && T->altura<o->altura)
    	 return buscar(T->velhoBaixo, o);
    if(T->idade<o->idade && T->altura>o->altura)
    	 return buscar(T->novoAlto, o);
    if(T->idade<o->idade && T->altura<o->altura)
    	 return buscar(T->novoBaixo, o);
    	 
    
}

/**
* libera nós.
* @param no
* @sem retorno
*/
void libera_Nodo( No *no)
{
	if(no==0)
	return
	libera_Nodo(no->velhoAlto);
	libera_Nodo(no->velhoAlto);
	libera_Nodo(no->novoAlto);
	libera_Nodo(no->novoBaixo);
	free(no);
	no=NULL;
}
/**
* libera arvore.
* @param raiz
* @sem retorno
*/
void libera_arv( No *raiz)
{
	if(raiz==NULL)
	return;
	libera_Nodo(raiz);
	free(raiz);
}


/**
*Funcao main
*/
int main() {
 struct No * T = NULL;
 struct No * x;
 struct Registro * o;
 char comando[200];
 lelinha(comando);
   while (strcmp(comando, "F") != 0) {
      if (strcmp(comando, "I") == 0) {
      o = readRegistro();
      insere(&T,newNo(o));
      }
   if (strcmp(comando, "A") == 0) {
      printf("a=%d\n", altura(T));
   }
   if (strcmp(comando, "N") == 0) {
      printf("n=%d\n", size(T));
   }
   if (strcmp(comando, "P") == 0) {
      printf("<XML>\n");
    imprime(T);
    printf("</XML>\n");
   }
if (strcmp(comando, "B") == 0) {
o = readRegistro();
if (buscar(T, o)) {
printf("B=true\n");
} else {
printf("B=false\n");
}
}
if (strcmp(comando, "R") == 0) {
o = readRegistro();
}
lelinha(comando);
}
libera_arv(T);
}
