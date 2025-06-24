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

//criacao da lista de tarefas
vector<Tarefa> tarefas; //vetor dinamico
int proximoId = 1;

//funcao de adicionar tarefas
void adicionarTarefa(const string& descricao) {
    tarefas.push_back({proximoId++, descricao, false});
    cout << "tarefa adicionada!\n";
}

//funcao de listar tarefas
void listarTarefas() {
    for (const auto& t : tarefas) {
        cout << t.id << " - " << t.descricao << (t.concluida ? "[concluida]" : "pendente") << "\n";
    }
}

int main() {
    adicionarTarefa("estudar c++");
    listarTarefas();
    return 0;
}