#include "tarefas.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

vector<Tarefa> tarefas;
int proximoId = 1;

void adicionarTarefas(const string &descricao) {
    tarefas.push_back({proximoId++, descricao, false});
    cout << "tarefa adicionada!\n";
}

void listarTarefas() {
    if (tarefas.empty()) {
        cout << "Nenhuma tarefa cadastrada.\n";
        return;
    }
    cout << left << setw(5) << "ID"
         << setw(30) << "Descricao"
         << setw(12) << "Status" << "\n";
    cout << string(47, '-') << "\n";
    for (const auto &t : tarefas) {
        cout << left << setw(5) << t.id
             << setw(30) << t.descricao
             << setw(12) << (t.concluida ? "Concluida" : "Pendente") << "\n";
    }
}

void concluirTarefas(int id) {
    for (auto &t : tarefas) {
        if (t.id == id) {
            t.concluida = true;
            cout << "terefa marcada como concluida! \n";
            return;
        }
    }
    cout << "tarefa com ID " << id << "não foi encontrada. \n";
}

void removerTarefas(int id) {
    for (auto it = tarefas.begin(); it != tarefas.end(); ++it) {
        if (it->id == id) {
            tarefas.erase(it);
            cout << "tarefa deletada!\n";
            return;
        }
    }
    cout << "tarefa com ID " << id << " não foi encontrada.\n";
}

void salvarTarefasEmArquivo(const string &arquivoTxt) {
    ofstream arquivo(arquivoTxt);
    for (const auto &t : tarefas) {
        arquivo << t.id << ";" << t.descricao << ";" << t.concluida << "\n";
    }
    arquivo.close();
}

void carregarTarefas(const string &arquivoTxt) {
    ifstream arquivo(arquivoTxt);
    if (!arquivo.is_open())
        return;
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
            if (id >= proximoId)
                proximoId = id + 1;
        }
    }
    arquivo.close();
}