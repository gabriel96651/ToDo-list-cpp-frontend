#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//estrutura da tarefa
struct Tarefa {
    int id;
    std::string descricao;
    bool concluida;
};

// Lista dinâmica de tarefas
vector<Tarefa> tarefas; //vetor dinamico
int proximoId = 1;

// Função para adicionar uma nova tarefa
void adicionarTarefa(const string& descricao) {
    tarefas.push_back({proximoId++, descricao, false});
    cout << "tarefa adicionada!\n";
}

//funcao para listar todas as tarefas
void listarTarefas() {
    for (const auto& t : tarefas) {
        cout << t.id << " - " << t.descricao << (t.concluida ? "[concluida]" : "[pendente]") << "\n";
    }
}

//funcao de marcar como concluida
void concluirTarefa(int id) {
    for(auto& t: tarefas) {
        if (t.id == id) {
            t.concluida = true;
            cout << "terefa marcada como concluida! \n";
            return;
        }
    }
    cout << "tarefa com ID " << id << "não foi encontrada. \n" ;
}

//funcao para deletar uma tarefa
void removerTarefa(int id) {
    for (auto it = tarefas.begin(); it != tarefas.end(); ++it) {
        if (it->id == id) {
            tarefas.erase(it);
            cout << "tarefa deletada!\n";
            return;
        }
    }
    cout << "tarefa com ID " << id << " não foi encontrada.\n";
}

//funcao para salvar tarefas em um arquivo
void salvarTarefasEmArquivo(const string& arquivoTxt) {
    ofstream arquivo(arquivoTxt);
    for (const auto& t : tarefas) {
        arquivo << t.id << ";" << t.descricao << ";" << t.concluida << "\n";
    }
    arquivo.close();
}

//funcao para carregar tarefas
void carregarTarefas(const string& arquivoTxt) {
    ifstream arquivo(arquivoTxt);
    if (!arquivo.is_open()) return;
    tarefas.clear();
    proximoId = 1;
    string linha;
    while (getline(arquivo, linha)) {
        int id;
        string descricao;
        bool concluida;
        size_t p1 = linha.find(';');
        size_t p2 = linha.rfind(';');
        if (p1 != string::npos && p2 != string::npos && p1 != p2) {
            id = stoi(linha.substr(0, p1));
            descricao = linha.substr(p1 + 1, p2 - p1 - 1);
            concluida = stoi(linha.substr(p2 + 1));
            tarefas.push_back({id, descricao, concluida});
            if (id >= proximoId) proximoId = id + 1;
        }
    }
    arquivo.close();
}

//funcao principal
int main() {
    carregarTarefas("tarefas.txt");  // carrega tarefas ao iniciar

    int opcao;
    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Adicionar tarefa\n";
        cout << "2. Listar tarefas\n";
        cout << "3. Concluir tarefa\n";
        cout << "4. Remover tarefa\n";
        cout << "5. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                cin.ignore();
                string descricao;
                cout << "Digite a descricao da tarefa: ";
                getline(cin, descricao);
                adicionarTarefa(descricao);
                salvarTarefasEmArquivo("tarefas.txt"); // salva imediatamente
                break;
            }
            case 2: {
                listarTarefas();
                break;
            }
            case 3: {
                int id;
                cout << "Digite o ID da tarefa que deseja concluir: ";
                cin >> id;
                concluirTarefa(id);
                salvarTarefasEmArquivo("tarefas.txt"); // salva imediatamente
                break;
            }
            case 4: {
                int id;
                cout << "Digite o ID da tarefa que deseja remover: ";
                cin >> id;
                removerTarefa(id);
                salvarTarefasEmArquivo("tarefas.txt"); // salva imediatamente
                break;
            }
            case 5: {
                cout << "Saindo do programa...\n";
                return 0;
            }
            default:
                cout << "Opcao invalida, tente novamente.\n";
        }
    }

    return 0;
}