#include <stdio.h>

void inicializa(char [3][3]);
void jogador1(char [3][3]);
void jogador2(char [3][3]);
int transf(char);
void desenhar(char [3][3]);
int vasculhar(char [3][3], int, int);
int verificar_total(char [3][3]);
int verificar_linha(char [3][3]);
int verificar_coluna(char [3][3]);
int verificar_diagonal(char [3][3]);
int play_again();
int turno=0;

int main()
{
    printf("_____________________________________________________________\n\n");
    printf("Digite as coordenadas da casa que quer jogar. (Exemplo: '3B').\n");
    printf("_____________________________________________________________\n\n");
    char matriz[3][3];
    inicializa(matriz);
    desenhar(matriz);
repeat:
    while(verificar_total(matriz)==0)
    {
        jogador1(matriz);
        printf("\n\n");
        desenhar(matriz);
        if(verificar_total(matriz)==1)
            break;
        jogador2(matriz);
        printf("\n\n");
        desenhar(matriz);
    }
    if(turno%2==0)
        printf("\nPARABENS, JOGADOR 2!!");
    else
        printf("\nPARABENS, JOGADOR 1!!");
    printf("\n\nJogar novamente?\n(Digite 'S' para jogar novamente ou 'N' para finalizar)");
    if(play_again()==1)
        goto repeat;
    return 0;
}

void inicializa(char matriz[3][3])
{
    int i, j;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            matriz[i][j]=' ';
}

void jogador1(char matriz[3][3])
{
    int l, c;
    char coord[3];
again:
    printf("Jogador 1: \n");
    gets(coord);
    c=transf(coord[0]);
    l=transf(coord[1]);
    if(vasculhar(matriz, l, c)==1)
    {
        printf("\nEssa casa ja foi preechida.\n");
        goto again;
    }
    matriz[l][c]='X';
    turno++;
}

void jogador2(char matriz[3][3])
{
    int l, c;
    char coord[3];
again:
    printf("Jogador 2: \n");
    gets(coord);
    c=transf(coord[0]);
    l=transf(coord[1]);
    if(vasculhar(matriz, l, c)==1)
    {
        printf("\nEssa casa ja foi preechida.\n");
        goto again;
    }
    matriz[l][c]='O';
    turno++;
}

int transf(char c)
{
    int r;
    if((int)c>=(int)48 && (int)c<=(int)57)
        r=(int)c-48-1;
    else if((int)c>=(int)65 && (int)c<=(int)90)
        r=(int)c-65;
    else if((int)c>=(int)97 && (int)c<=(int)122)
        r=(int)c-97;
    else
        r=5;
    return r;
}

void desenhar(char matriz[3][3])
{
    int i, j;
    printf("    A   B   C\n\n");
    for(j=0; j<3; j++)
    {
        printf("%d) ", j+1);
        for(i=0; i<3; i++)
            printf("|%c| ", matriz[i][j]);
        printf("\n\n");
    }
}

int vasculhar(char matriz[3][3], int l, int c)
{
    if((int)matriz[l][c]==(int)79 || (int)matriz[l][c]==(int)88)
        return 1;
    return 0;
}

int verificar_total(char matriz[3][3])
{
    if(verificar_linha(matriz)==1)
        return 1;
    if(verificar_coluna(matriz)==1)
        return 1;
    if(verificar_diagonal(matriz)==1)
        return 1;
    if(turno>=9)
        return 1;
    return 0;
}

int verificar_linha(char matriz[3][3])
{
    int soma, i, j;
    for(j=0; j<3; j++)
    {
        soma=0;
        for(i=0; i<3; i++)
        {
            soma+=(int)matriz[i][j];
            if(soma==(88*3) || soma==(79*3))
                return 1;
        }
    }
    return 0;
}

int verificar_coluna(char matriz[3][3])
{
    int soma, i, j;
    for(j=0; j<3; j++)
    {
        soma=0;
        for(i=0; i<3; i++)
        {
            soma+=(int)matriz[j][i];
            if(soma==(88*3) || soma==(79*3))
                return 1;
        }
    }
    return 0;
}

int verificar_diagonal(char matriz[3][3])
{
    int i, j=0, soma;
    for(i=0; i<3; i++)
    {
        soma+=(int)matriz[i][i];
        if(soma==(88*3) || soma==(79*3))
            return 1;
    }
    soma=0;
    for(i=2; i>=0; i--)
    {
        soma+=(int)matriz[i][j];
        j++;
        if(soma==(88*3) || soma==(79*3))
            return 1;
    }
    return 0;
}

int play_again()
{
    char c;
    scanf("%c", &c);
    if((int)c==(int)83 || (int)c==(int)115)
        return 1;
    else
        return 0;
}
