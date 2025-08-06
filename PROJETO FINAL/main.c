
// projeto de floyd-warshall - prazo de entrega 10/08.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100
#define infinito 999999

int n = 0;
char cidades[max][100];
int matriz_predecessores[max][max];
int matriz_distancias_minimas[max][max];
int matriz_de_adjacencia[max][max];
int Dados_carregados = 0;
int algorimtmoExecutado = 0;

// todos os procedimentos das funções:
void inicializar_matrizes();                                   // implementada
void floyd_warshall();                                         // implementada
void imprimirmatriz(int matriz[max][max], const char *titulo); // implementada
void salvardados();
void carregardados(const char *arquivo);
void salvar_resultados(const char *arquivo);
void mostrarocaminho(const int origem, int destino);

// menus do programa em formato de procedimento:

void menu_entrada_dados();
void menu_ver_matrizes();
void ver_caminho();

//inicio do programa principal:
int main()
{
    int opcao;
    do
    {
        printf("\n-- SEJA BEM VINDO AO NOSSO PROGRAMA PRINCIPAL --");
        printf("\n1 - INSERIR OU CARREGAR DADOS");
        printf("\n2 - EXECUTAR O ALGORITMO FLOYD-WARSHALL");
        printf("\n3 - VER TODAS AS MATRIZES DISPONIVEIS");
        printf("\n4 - CONSULTAR O MENOR CAMINHO");
        printf("\n5 - SALVAR TODOS OS DADOS EM UM ARQUIVO");
        printf("\n0 - SAIR DO PROGRAMA");
        printf("\nSUA ESCOLHA EH: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menu_entrada_dados();
            break;
        case 2:
            if (!Dados_carregados)
            {
                printf("CARREGUE TODOS OS DADOS PRIMEIRO!");
            }
            else
                floyd_warshall();
            break;

        case 3:
            menu_ver_matrizes();
            break;

        case 4:
            ver_caminho();
            break;

        case 5:
            if (!algorimtmoExecutado)
            {
                puts("POR FAVOR, FAÇA O ALGORITMO PRIMEIRO!");
            }
            else
            {
                salvar_resultados("resultados.txt");
            }

        case 0:
            puts("FINALIZANDO O PROGRAMA...");
            return 0;

        default:
            printf("\nESTA OPCAO EH INVALIDA DENTRO DO PROGRAMA");
        }
    } while (opcao != 0);

    return 0;
}


/*
FUNCAO DE INICIALIZAR MATRIZES:
usada para preparar a matriz de distancias minimas e a de predecessores - todos vindos do grafo.
Todos os laços for vão percorrer todos as posições i e j do grafo.
Em resumo, esta função serve para carregar inicialmente o algoritmo de floyd warshall - onde há carregamento das distancias diretas e os predecessores sao definidos com base nas conexões diretas ou ausencia
*/
void inicializar_matrizes()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz_distancias_minimas[i][j] = matriz_de_adjacencia[i][j];
            if (i == j)
            {
                matriz_predecessores[i][j] = i;
            }
            else if (matriz_de_adjacencia[i][j] != infinito)
            {
                matriz_predecessores[i][j] = i;
            }
            else
            {
                matriz_predecessores[i][j] = -1;
            }
        }
    }
}

/*
Função para o algoritmo de floys-warshall:
OBS: os três for aninhados irão percorrer todos os possiveis pares de vertices - i e j ; na qual usa um vertice intermediario
*/

void floyd_warshall()
{
    inicializar_matrizes();
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matriz_distancias_minimas[i][k] + matriz_distancias_minimas[k][j] < matriz_distancias_minimas[i][j])
                {
                    matriz_distancias_minimas[i][j] = matriz_distancias_minimas[i][k] + matriz_distancias_minimas[k][j];
                    matriz_predecessores[i][j] = matriz_predecessores[k][j];
                }
                // essa parte do if vai testar se a distancia de i para j via k é menor do que a distancia de i para j , caso seja, ele atualiza a matriz de predecessores.
                algorimtmoExecutado = 1;
            }
        }
    }
    puts("O ALGORITMO FOI EXECUTADO!");
}

/*
Esta função irá servir para imprimir a matriz de numeros inteiros na tela, ou seja, as cidades que passarem por qualquer outra das 15 cidades escolhidas, serão ditas como 9999 - de modo geral, infinito.
elementos principais:
const char *titulo = neste caso o titulo será o nome dado a matriz a ser impressa.
*/
void imprimirmatriz(int matriz[max][max], const char *titulo)
{
    printf("\n%s: ", titulo);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matriz[i][j] == infinito)
            {
                printf("INFINITO ");
            }
            else
            {
                printf("%3d", matriz[i][j]);
            }
        }
        printf("\n");
    }
}
/*


*/

void salvardados()
{
    FILE *f = fopen("dados.txt", "w");
    if (f == NULL)
    {
        puts("ERRO AO ABRIR ESTE ARQUIVO...");
        return;
    }
    fprintf(f, "%i\n", n);
    for (int i = 0; i < n; i++)
        fprintf(f, "%s\n", cidades[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fprintf(f, "%i\n", matriz_de_adjacencia[i][j]);
    fclose(f);
    printf("O ARQUIVO FOI SALVO EM: dados.txt\n");
}
/*


*/
int carregarDados(const char *arquivo)
{
    FILE *f = fopen(arquivo, "r"); // este "r" serve para o modo de leitura do arquivo.
    if (!f)
    {
        puts("ERRO AO ABRIR ESTE ARQUIVO");
        return 0;
    }
    fscanf(f, "%d\n", &n);
    for (int i = 0; i < n; i++)
    {
        fgets(cidades[i], 100, f);
        cidades[i][strcspn(cidades[i], "\n")] = 0;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(f, "%d", &matriz_de_adjacencia[i][j]);
    fclose(f);

    Dados_carregados = 1;
    printf("Os dados foram carregados com sucesso!\n");
    return 1;
}
/*


*/
void salvar_resultados(const char *dados)
{
    FILE *f = fopen(dados, "w");
    if (!f)
    {
        printf("Erro ao salvar resultados.\n");
        return;
    }
    fprintf(f, "MATRIZ DE DISTANCIAS:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fprintf(f, "%d ", matriz_distancias_minimas[i][j]);
        fprintf(f, "\n");
    }

    fprintf(f, "\n MATRIZ DE PREDECESSORES:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fprintf(f, "%d ", matriz_predecessores[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);
    printf("OS RESULTADOS FORAM SALVOS NO ARQUIVO:  %s\n", dados);
}
/*


*/
void mostrarCaminho(int origem, int destino)
{
    if (matriz_predecessores[origem][destino] == -1)
    {
        printf("EITA, NAO EXISTE CAMINHO PARA ESSE LUGAR.\n");
        return;
    }
    int caminho[max], tam = 0, atual = destino;
    while (atual != origem)
    {
        caminho[tam++] = atual;
        atual = matriz_predecessores[origem][atual];
    }
    caminho[tam++] = origem;

    printf("CAMINHO GERAL: ");
    for (int i = tam - 1; i >= 0; i--)
    {
        printf("%s", cidades[caminho[i]]);
        if (i > 0)
            printf(" --> ");
    }
    printf("\n");
}
/*

*/
void menu_entrada_dados()
{
    int opcao;
    printf("\n--- MENU DE DADOS ---\n");
    printf("1 - PREFIRO INSERIR TODOS OS DADOS MANUALMENTE\n");
    printf("2 - PREFIRO CARREGAR TODOS OS DADOS DO ARQUIVO(dados.txt)\n");
    printf("SUA ESCOLHA: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao == 1)
    {
        printf("Digite o numero de cidades: ");
        scanf("%d", &n);
        getchar();
        for (int i = 0; i < n; i++)
        {
            printf("O Nome da cidade %d: ", i);
            fgets(cidades[i], 100, stdin);
            cidades[i][strcspn(cidades[i], "\n")] = 0;
        }
        printf("Digite a matriz de adjacencia:\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                printf("De %s para %s: ", cidades[i], cidades[j]);
                scanf("%d", &matriz_de_adjacencia[i][j]);
            }
        Dados_carregados = 0;
        Dados_carregados = 0;
        salvardados();
    }
    else if (opcao == 2)
    {
        carregarDados("dados.txt");
    }
    else
    {
        printf("Opcao invalida.\n");
    }
}
/*


*/
void menu_ver_matrizes()
{
    if (!algorimtmoExecutado)
    {
        printf("POR FAVOR, FACA O ALGORITMO DE FLOYD-WARSHALL PRIMEIRO.\n");
        return;
    }
    int opcao;
    printf("\n--- TODAS AS MATRIZES DISPONÍVEIS ---\n");
    printf("1 - Visualizar a Matriz de Adjacencia\n");
    printf("2 - Visualizar a Matriz de Distancias Minimas\n");
    printf("3 - Visualizar a Matriz de Predecessores\n");
    printf("Sua Escolha: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        imprimirmatriz(matriz_de_adjacencia, "Matriz de Adjacencia");
        break;
    case 2:
        imprimirmatriz(matriz_distancias_minimas, "Matriz de Distancias Minimas");
        break;
    case 3:
        imprimirmatriz(matriz_predecessores, "Matriz de Predecessores");
        break;
    default:
        printf("Opcao invalida.\n");
    }
}
/*

*/
void ver_caminho()
{
    if (!algorimtmoExecutado)
    {
        printf("POR FAVOR, FACA O ALGORITMO DE FLOYD-WARSHALL PRIMEIRO\n");
        return;
    }
    printf("TODAS AS CIDADES DISPONIVEIS:\n");
    for (int i = 0; i < n; i++)
        printf("%d - %s\n", i, cidades[i]);

    int origem, destino;
    printf("ESCOLHA O NUMERO DA CIDADE DE PARTIDA: ");
    scanf("%d", &origem);
    printf("ESCOLHA O NUMERO DA CIDADE DE DESTINO: ");
    scanf("%d", &destino);

    if (origem < 0 || origem >= n || destino < 0 || destino >= n)
    {
        printf("ESTES INDICES SAO INVALIDOS.\n");
        return;
    }

    if (matriz_distancias_minimas[origem][destino] == infinito)
        printf("NAO EXISTE UM CAMINHO PARA ESTE LUGAR.\n");
    else
    {
        printf("O CUSTO TOTAL EH %d\n QUILOMETROS", matriz_distancias_minimas[origem][destino]);
        mostrarCaminho(origem, destino);
    }
}
