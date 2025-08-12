#include <iostream>
#include <limits>
#include "tarefas.h"
using namespace std;

// Função para ler inteiro de forma segura
int lerInteiroSeguro(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        string entrada;
        getline(std::cin, entrada);
        try {
            valor = stoi(entrada);
            break;
        } catch (...) {
            cout << "Entrada inválida! Digite um número.\n";
        }
    }
    return valor;
}

int main() {
    carregarTarefas("tarefas.txt");

    int opcao;
    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Adicionar tarefa\n";
        cout << "2. Listar tarefas\n";
        cout << "3. Concluir tarefa\n";
        cout << "4. Editar tarefa\n";
        cout << "5. Remover tarefa\n";
        cout << "6. Sair\n";
        cout << "Escolha uma opcao: ";
        opcao = lerInteiroSeguro("");
        switch (opcao) {
        case 1: {
            cin.ignore();
            string descricao;
            cout << "Digite a descricao da tarefa: ";
            getline(cin, descricao);
            adicionarTarefas(descricao);
            salvarTarefasEmArquivo("tarefas.txt");
            break;
        }
        case 2:
            listarTarefas();
            break;
        case 3: {
            int id = lerInteiroSeguro("Digite o ID da tarefa: ");
            concluirTarefas(id);
            salvarTarefasEmArquivo("tarefas.txt");
            break;
        }
        case 4: {
            int id = lerInteiroSeguro("Digite o ID da tarefa: ");
            cin.ignore();
            string novaDescricao;
            cout << "Edite a sua tarefa: ";
            getline(cin, novaDescricao);
            // Implemente a lógica de edição aqui ou crie uma função editarTarefas
            break;
        }
        case 5: {
            int id = lerInteiroSeguro("Digite o ID da tarefa: ");
            removerTarefas(id);
            salvarTarefasEmArquivo("tarefas.txt");
            break;
        }
        case 6:
            cout << "Saindo do programa...\n";
            return 0;
        default:
            cout << "Opcao invalida, tente novamente.\n";
        }
    }
    return 0;
}