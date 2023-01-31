#include <stdio.h>
#include <stdlib.h>
//Autor: Pedro Augusto Borges Assis
//GitHUB: YoPeterChill
/**Neste código está proposto uma implementação de Arvore AVL.
Onde o usuario insere os elementos de uma arvore até digitar "-1".
Em seguida é printado na tela o numero de rotações feitas para o Balanciamento.

OBS: para testar o código (o numero de rotações) foi utilizado o simulador de arvore AVL: "https://www.inf.ufsc.br/~aldo.vw/estruturas/simulador/AVL.html"

**/



struct Noh
{
    int dados;
    int altura;
    struct Noh *esquerda;
    struct Noh *direita;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int altura(struct Noh *Noh)
{
    if (Noh == NULL)
        return 0;
    return Noh->altura;
}

struct Noh *novoNoh(int dados)
{
    struct Noh *Noh = (struct Noh *)malloc(sizeof(struct Noh));
    Noh->dados = dados;
    Noh->esquerda = NULL;
    Noh->direita = NULL;
    Noh->altura = 1;
    return Noh;
}

int Getbalanciamento(struct Noh *Noh)
{
    if (Noh == NULL)
        return 0;
    return altura(Noh->esquerda) - altura(Noh->direita);
}

struct Noh *rotacaoDireita(struct Noh *y)
{
    struct Noh *x = y->esquerda;
    struct Noh *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

struct Noh *rotacaoEsquerda(struct Noh *x)
{
    struct Noh *y = x->direita;
    struct Noh *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

struct Noh *rotacaoEsquerdaDireita(struct Noh *z)
{
    z->esquerda = rotacaoEsquerda(z->esquerda);
    return rotacaoDireita(z);
}

struct Noh *direitarotacaoEsquerda(struct Noh *z)
{
    z->direita = rotacaoDireita(z->direita);
    return rotacaoEsquerda(z);
}

struct Noh *Inserir(struct Noh *Noh, int dados, int *rotacoes)
{
    if (Noh == NULL)
        return novoNoh(dados);

    if (dados < Noh->dados)
        Noh->esquerda = Inserir(Noh->esquerda, dados, rotacoes);
    else if (dados > Noh->dados)
        Noh->direita = Inserir(Noh->direita, dados, rotacoes);
    else
        return Noh;

    Noh->altura = max(altura(Noh->esquerda), altura(Noh->direita)) + 1;

    int balanciamento = Getbalanciamento(Noh);

    if (balanciamento > 1 && dados < Noh->esquerda->dados)
    {
        (*rotacoes)++;
        return rotacaoDireita(Noh);
    }

    if (balanciamento < -1 && dados > Noh->direita->dados)
    {
        (*rotacoes)++;
        return rotacaoEsquerda(Noh);
    }

    if (balanciamento > 1 && dados > Noh->esquerda->dados)
    {
        (*rotacoes)++;
        return rotacaoEsquerdaDireita(Noh);
    }

    if (balanciamento < -1 && dados < Noh->direita->dados)
    {
        (*rotacoes)++;
        return direitarotacaoEsquerda(Noh);
    }

    return Noh;
}

int main()
{
    struct Noh *raiz = NULL;
    int rotacoes = 0, dados;

    printf("Insira os elementos da Arvore AVL, ao terminar digite -1: \n");
    scanf("%d", &dados);

    while (dados != -1)
    {
        raiz = Inserir(raiz, dados, &rotacoes);
        scanf("%d", &dados);
    }

    printf("Numero de Rotacoes:  %d\n", rotacoes);

    return 0;
}
