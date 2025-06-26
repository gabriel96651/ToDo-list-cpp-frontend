#include <iostream>
#include <vector>
#include <string>
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
        cout << t.id << " - " << t.descricao << (t.concluida ? "[concluida]" : "pendente") << "\n";
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

//funcao principal
int main() {
    adicionarTarefa("estudar c++");
    listarTarefas();

    std::cout << "\nConcluindo tarefa 1...\n";
    concluirTarefa(1);
    listarTarefas();

    std::cout << "\nRemovendo tarefa 2...\n";
    removerTarefa(2);
    listarTarefas();
    return 0;
}