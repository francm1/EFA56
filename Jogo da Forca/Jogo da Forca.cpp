// Jogo da Forca.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
// Uma alteração para enviar novamente ao git na branch novaAlteracao

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

const int MAX_TENTATIVAS = 6; // Tentativas de acerto das letras

// Protótipos para o jogo
void desenhaForca(int erros);
bool verificaLetra(char letra, const string& palavra, string& progresso);
string palavraAleatoria();
void armazenaPontuacao(const string& jogador, int pontos);
void jogarSozinho();
void jogarDoisJogadores();

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int opcao;
    cout << "\n\tBem-vindo ao Jogo da Forca!" << endl;
    cout << "\n\tEscolha uma opção:" << endl;
    cout << "\n\t1. Jogar Sozinho" << endl;
    cout << "\n\t2. Jogar com Dois Jogadores" << endl;
    cout << "\n\tEscolha: ";
    cin >> opcao;

    if (opcao == 1) {
        jogarSozinho();
    }
    else if (opcao == 2) {
        jogarDoisJogadores();
    }
    else {
        cout << "\n\tOpção inválida!" << endl;
    }

    return 0;
}

// Função para jogar sozinho
void jogarSozinho() {
    string jogador;
    cout << "\n\tDigite seu nome: ";
    cin >> jogador;

    string palavra = palavraAleatoria();
    string progresso(palavra.length(), '_');
    int erros = 0;
    char letra;
    bool acertou = false;

    while (erros < MAX_TENTATIVAS && progresso != palavra) {
        cout << "\nPalavra: " << progresso << endl;
        cout << "\nTentativas restantes: " << MAX_TENTATIVAS - erros << endl;
        cout << "\nDigite uma letra: ";
        cin >> letra;

        if (!verificaLetra(letra, palavra, progresso)) {
            erros++;
        }

        desenhaForca(erros);
    }

    if (progresso == palavra) {
        cout << "\n\tParabéns, " << jogador << "! Você acertou a palavra: " << palavra << endl;
        armazenaPontuacao(jogador, 10);
    }
    else {
        cout << "\nVocê perdeu! A palavra era: " << palavra << endl;
    }
}

// Função para jogar com dois jogadores
void jogarDoisJogadores() {
    string jogador1, jogador2;
    cout << "\n\tDigite o nome do jogador 1: ";
    cin >> jogador1;
    cout << "\n\tDigite o nome do jogador 2: ";
    cin >> jogador2;

    string palavra, progresso;
    int erros = 0;
    char letra;
    bool acertou = false;

    // Jogador 1 escolhe a palavra
    cout << jogador1 << ", escolha a palavra (sem que " << jogador2 << " veja): ";
    cin >> palavra;
    system("cls"); // Limpa a tela após a escolha

    progresso = string(palavra.length(), '_');

    while (erros < MAX_TENTATIVAS && progresso != palavra) {
        cout << "\n" << jogador2 << ", adivinhe a palavra: " << progresso << endl;
        cout << "Tentativas restantes: " << MAX_TENTATIVAS - erros << endl;
        cout << "\nDigite uma letra: ";
        cin >> letra;

        if (!verificaLetra(letra, palavra, progresso)) {
            erros++;
        }

        desenhaForca(erros);
    }

    if (progresso == palavra) {
        cout << "\n\tParabéns, " << jogador2 << "! Você acertou a palavra: " << palavra << endl;
        armazenaPontuacao(jogador2, 10);
    }
    else {
        cout << "\n\tVocê perdeu! A palavra era: " << palavra << endl;
    }
}

// Função para verificar se a letra está na palavra
bool verificaLetra(char letra, const string& palavra, string& progresso) {
    bool acertou = false;
    for (size_t i = 0; i < palavra.length(); ++i) {
        if (palavra[i] == letra) {
            progresso[i] = letra;
            acertou = true;
        }
    }
    return acertou;
}

// Função para desenhar a forca com base no número de erros
void desenhaForca(int erros) {
    cout << "\n +----+" << endl;
    cout << " |    |" << endl;
    cout << " |    " << (erros > 0 ? "O" : " ") << endl;
    cout << " |   " << (erros > 2 ? "/" : " ") << (erros > 1 ? "|" : "") << (erros > 3 ? "\\" : "") << endl;
    cout << " |   " << (erros > 4 ? "/" : " ") << (erros > 5 ? " \\" : "") << endl;
    cout << " |" << endl;
    cout << "=====" << endl;
}

// Função para escolher uma palavra aleatória de um ficheiro
string palavraAleatoria() {
    
    srand(time(0)); 
    ifstream palav;
    vector<string> palavras;
    string palavra;

    palav.open("palav.txt"); // Para abrir o ficheiro
    if (palav.fail())
    {
        cout << "\n\tErro na abertura do ficheiro para leitura!" << endl;
        exit(1);
    }
    else
    {
        cout << "\n\tAbertura do ficheiro com sucesso!" << endl;
        // Loop para ler linha a linha
        while (palav >> palavra) {
            palavras.push_back(palavra);
        }

        palav.close();
        return palavras[rand() % palavras.size()];
    }
}

// Função para armazenar a pontuação no ficheiro
void armazenaPontuacao(const string& jogador, int pontos) {
    
    ofstream arquivo; // Cria um objeto da classe ofstream para criar e escrever no ficheiro de texto
    
    arquivo.open("pontuacao.txt"); // Abre o stream para escrita, se não existir o ficheiro irá criá-lo
    // Verifica se conseguiu abrir o ficheiro
    if (!arquivo)
    {
        cout << "\n\tErro na criação do ficheiro!" << endl;
        exit(1);
    }
    else
    {
        cout << "\n\tFicheiro criado com sucesso!" << endl;
        arquivo << jogador << " ganhou " << pontos << " pontos." << endl;
        arquivo.close(); // Fecha o ficheiro, para libertar a memória
        return;
    }

}



// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
