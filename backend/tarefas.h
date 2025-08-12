#ifndef TAREFAS_H
#define TAREFAS_H

#include <string>
#include <vector>

struct Tarefa {
    int id;
    std::string descricao;
    bool concluida;
};

extern std::vector<Tarefa> tarefas;
extern int proximoId;

void adicionarTarefas(const std::string &descricao);
void listarTarefas();
void concluirTarefas(int id);
void removerTarefas(int id);
void salvarTarefasEmArquivo(const std::string &arquivoTxt);
void carregarTarefas(const std::string &arquivoTxt);

#endif