#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void inicializa(char [3][3]);
void jogador1(char [3][3]);
void jogador2(char [3][3]);
int transf(char);
void desenhar(char [3][3]);
int vasculhar(char [3][3], int, int);
int verificar_parcial(char [3][3]);
int verificar_total(char [3][3]);
int verificar_linha(char [3][3]);
int verificar_coluna(char [3][3]);
int verificar_diagonal(char [3][3]);
int verificar_linha_d(char [3][3]);
int verificar_coluna_d(char [3][3]);
int verificar_diagonal_d(char [3][3]);
int verificar_linha_p(char [3][3]);
int verificar_coluna_p(char [3][3]);
int verificar_diagonal_u(char [3][3]);
int verificar_diagonal_u_s(char [3][3]);
int verificar_linha_u(char [3][3]);
int verificar_coluna_u(char [3][3]);
int verificar_diagonal_p(char [3][3]);
int turno=0, camp[2];
char hist[9][3];

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int main()
{
    system("color A");
    int rodada=1;
    printf("_____________________________________________________________\n\n");
    printf("Digite as coordenadas da casa que quer jogar. (Exemplo: '3B').\n");
    printf("_____________________________________________________________\n\n");
    char matriz[3][3];
    setbuf(stdin, '\0');
    inicializa(matriz);
    desenhar(matriz);
    while(verificar_total(matriz)==0)
    {
        srand(time(NULL));
        jogador1(matriz);
        printf("\n\n");
        desenhar(matriz);
        if(verificar_total(matriz)==1)
            break;
        jogador2(matriz);
        printf("\n\n");
        desenhar(matriz);
    }
    if(turno!=9)
    {
        if(turno%2==0)
            printf("\nVoce perdeu :(");
        else
            printf("\nPARABENS, JOGADOR!!");
    }
    else
        printf("\nDeu velha :p");
    turno=0;
    printf("\n\n\n");
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
    printf("Jogador: \n");
    gets(coord);
    c=transf(coord[0]);
    l=transf(coord[1]);
    if(c==5 || l==5)
        goto again;
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
again:
    if(verificar_parcial(matriz)==1)
    {
        if(camp[0]==1)
        {
            l=rand()%3;
            c=camp[1];
        }
        if(camp[0]==2)
        {
            l=camp[1];
            c=rand()%3;
        }
        if(camp[0]==3)
        {
            l=rand()%3;
            c=l;
        }
        if(camp[0]==4)
        {
            l=rand()%3;
            if(l==0)
                c=2;
            if(l==1)
                c=l;
            if(l==2)
                c=0;
        }
        if(camp[0]==5)
        {
            l=1;
            c=1;
        }

    }
    else
    {
        l=rand()%3;
        c=rand()%3;
    }
    if(vasculhar(matriz, l, c)==1)
        goto again;
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
    int i, j=0, soma=0;
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

int verificar_parcial(char matriz[3][3])
{
    if(verificar_linha_d(matriz)==1)
        return 1;
    if(verificar_coluna_d(matriz)==1)
        return 1;
    if(verificar_diagonal_d(matriz)==1)
        return 1;
    if(verificar_linha_p(matriz)==1)
        return 1;
    if(verificar_coluna_p(matriz)==1)
        return 1;
    if(verificar_diagonal_p(matriz)==1)
        return 1;
    if(verificar_linha_u(matriz)==1)
        return 1;
    if(verificar_coluna_u(matriz)==1)
        return 1;
    if(verificar_diagonal_u(matriz)==1)
        return 1;
    if(verificar_diagonal_u_s(matriz)==1)
        return 1;
    if((int)matriz[1][1]==(int)32)

        return 0;
}

int verificar_linha_p(char matriz[3][3])
{
    int soma, i, j=0, ret=0;
    for(j=0; j<3; j++)
    {
        soma=0;
        ret=0;
        for(i=0; i<3; i++)
        {
            if((int)matriz[i][j]!=(int)32)
                soma+=(int)matriz[i][j];
            if(soma==(88*2) || soma==(79*2) )
            {
                camp[0]=1;
                camp[1]=j;
                ret=1;
            }
        }
        if(ret==1 && (soma==(88*2) || soma==(79*2)))
            return 1;
    }
    return 0;
}

int verificar_coluna_p(char matriz[3][3])
{
    int soma, i, j=0, ret=0;
    for(j=0; j<3; j++)
    {
        soma=0;
        ret=0;
        for(i=0; i<3; i++)
        {
            if((int)matriz[j][i]!=(int)32)
                soma+=(int)matriz[j][i];
            if(soma==(88*2) || soma==(79*2) )
            {
                camp[0]=2;
                camp[1]=j;
                ret=1;
            }
        }
        if(ret==1 && (soma==(88*2) || soma==(79*2)))
            return 1;
    }
    return 0;
}

int verificar_diagonal_p(char matriz[3][3])
{
    int i, j=0, soma=0, ret=0;
    for(i=0; i<3; i++)
    {
        if((int)matriz[i][i]!=(int)32)
            soma+=(int)matriz[i][i];
        if(soma==(88*2) || soma==(79*2))
        {
            camp[0]=3;
            camp[1]=10;
            ret=1;
        }
    }
    if(ret==1 && (soma==(88*2) || soma==(79*2)))
        return 1;

    ret=0;
    soma=0;
    for(i=2; i>=0; i--)
    {
        if((int)matriz[i][j]!=(int)32)
            soma+=(int)matriz[i][j];
        j++;
        if(soma==(88*2) || soma==(79*2))
        {
            camp[0]=4;
            camp[1]=10;
            ret=1;
        }
    }
    if(ret==1 && (soma==(88*2) || soma==(79*2)))
        return 1;
    return 0;
}

int verificar_linha_d(char matriz[3][3])
{
    int soma, i, j=0, ret=0;
    for(j=0; j<3; j++)
    {
        soma=0;
        ret=0;
        for(i=0; i<3; i++)
        {
            if((int)matriz[i][j]!=(int)32)
                soma+=(int)matriz[i][j];
            if(soma==79*2)
            {
                camp[0]=1;
                camp[1]=j;
                ret=1;
            }
        }
        if(ret==1 && soma==(79*2))
            return 1;
    }
    return 0;
}

int verificar_coluna_d(char matriz[3][3])
{
    int soma, i, j=0, ret=0;
    for(j=0; j<3; j++)
    {
        soma=0;
        ret=0;
        for(i=0; i<3; i++)
        {
            if((int)matriz[j][i]!=(int)32)
                soma+=(int)matriz[j][i];
            if(soma==(79*2))
            {
                camp[0]=2;
                camp[1]=j;
                ret=1;
            }
        }
        if(ret==1 && soma==(79*2))
            return 1;
    }
    return 0;
}

int verificar_diagonal_d(char matriz[3][3])
{
    int i, j=0, soma=0, ret=0;
    for(i=0; i<3; i++)
    {
        if((int)matriz[i][i]!=(int)32)
            soma+=(int)matriz[i][i];
        if(soma==(79*2))
        {
            camp[0]=3;
            camp[1]=10;
            ret=1;
        }
    }
    if(ret==1 && soma==(79*2))
        return 1;

    ret=0;
    soma=0;
    for(i=2; i>=0; i--)
    {
        if((int)matriz[i][j]!=(int)32)
            soma+=(int)matriz[i][j];
        j++;
        if(soma==(79*2))
        {
            camp[0]=4;
            camp[1]=10;
            ret=1;
        }
    }
    if(ret==1 && soma==(79*2))
        return 1;
    return 0;
}

int verificar_linha_u(char matriz[3][3])
{
    int soma, i, j=0, ret=0;
    for(j=0; j<3; j++)
    {
        soma=0;
        ret=0;
        for(i=0; i<3; i++)
        {
            if((int)matriz[i][j]!=(int)32)
                soma+=(int)matriz[i][j];
            if(soma==79)
            {
                camp[0]=1;
                camp[1]=j;
                ret=1;
            }
        }
        if(ret==1 && soma==79)
            return 1;
    }
    return 0;
}

int verificar_coluna_u(char matriz[3][3])
{
    int soma, i, j=0, ret=0;
    for(j=0; j<3; j++)
    {
        soma=0;
        ret=0;
        for(i=0; i<3; i++)
        {
            if((int)matriz[j][i]!=(int)32)
                soma+=(int)matriz[j][i];
            if(soma==79)
            {
                camp[0]=2;
                camp[1]=j;
                ret=1;
            }
        }
        if(ret==1 && soma==79)
            return 1;
    }
    return 0;
}

int verificar_diagonal_u(char matriz[3][3])
{
    int i, j=0, soma=0, ret=0;
    for(i=0; i<3; i++)
    {
        if((int)matriz[i][i]!=(int)32)
            soma+=(int)matriz[i][i];
        if(soma==79)
        {
            camp[0]=3;
            camp[1]=10;
            ret=1;
        }
    }
    if(ret==1 && soma==79)
        return 1;

    ret=0;
    soma=0;
    for(i=2; i>=0; i--)
    {
        if((int)matriz[i][j]!=(int)32)
            soma+=(int)matriz[i][j];
        j++;
        if(soma==79)
        {
            camp[0]=4;
            camp[1]=10;
            ret=1;
        }
    }
    if(ret==1 && soma==79)
        return 1;
    return 0;
}

int verificar_diagonal_u_s(char matriz[3][3])
{
    int i, j=0, soma=0, ret=0;
    for(i=0; i<3; i++)
    {
        if((int)matriz[i][i]!=(int)32)
            soma+=(int)matriz[i][i];
        if(soma==0)
        {
            camp[0]=5;
            camp[1]=10;
            ret=1;
        }
    }
    if(ret==1 && soma==0)
        return 1;

    ret=0;
    soma=0;
    for(i=2; i>=0; i--)
    {
        if((int)matriz[i][j]!=(int)32)
            soma+=(int)matriz[i][j];
        j++;
        if(soma==0)
        {
            camp[0]=5;
            camp[1]=10;
            ret=1;
        }
    }
    if(ret==1 && soma==0)
        return 1;
    return 0;
}
