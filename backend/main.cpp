#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// estrutura da tarefa
struct Tarefa
{
    int id;
    std::string descricao;
    bool concluida;
};

// Lista dinâmica de tarefas
vector<Tarefa> tarefas; // vetor dinamico
int proximoId = 1;

// Função para adicionar uma nova tarefa
void adicionarTarefas(const string &descricao){
    tarefas.push_back({proximoId++, descricao, false});
    cout << "tarefa adicionada!\n";
}

// funcao para listar todas as tarefas
void listarTarefas(){
    if (tarefas.empty())
    {
        cout << "Nenhuma tarefa cadastrada.\n";
        return;
    }

    for (const auto &t : tarefas)
    {
        cout << left << setw(5) << "ID"
             << setw(30) << "Descricao"
             << setw(12) << "Status" << "\n";
        cout << left << setw(5) << t.id
             << setw(30) << t.descricao
             << setw(12) << (t.concluida ? "Concluida" : "Pendente") << "\n";

        cout << string(47, '-') << "\n";
    }
}

// funcao de marcar como concluida
void concluirTarefas(int id){
    for (auto &t : tarefas)
    {
        if (t.id == id)
        {
            t.concluida = true;
            cout << "terefa marcada como concluida! \n";
            return;
        }
    }
    cout << "tarefa com ID " << id << "não foi encontrada. \n";
}

// funcao para deletar uma tarefa
void removerTarefas(int id)
{
    for (auto it = tarefas.begin(); it != tarefas.end(); ++it)
    {
        if (it->id == id)
        {
            tarefas.erase(it);
            cout << "tarefa deletada!\n";
            return;
        }
    }
    cout << "tarefa com ID " << id << " não foi encontrada.\n";
}

// funcao para salvar tarefas em um arquivo
void salvarTarefasEmArquivo(const string &arquivoTxt){
    ofstream arquivo(arquivoTxt);
    for (const auto &t : tarefas)
    {
        arquivo << t.id << ";" << t.descricao << ";" << t.concluida << "\n";
    }
    arquivo.close();
}

// funcao para carregar tarefas
void carregarTarefas(const string &arquivoTxt){
    ifstream arquivo(arquivoTxt);
    if (!arquivo.is_open())
        return;
    tarefas.clear();
    proximoId = 1;
    string linha;
    while (getline(arquivo, linha))
    {
        int id;
        string descricao;
        bool concluida;
        size_t p1 = linha.find(';');
        size_t p2 = linha.rfind(';');
        if (p1 != string::npos && p2 != string::npos && p1 != p2)
        {
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

// funcao para editar uma tarefa
void editarTarefas(int id)
{
    cin.ignore();
    string novaDescricao;
    cout << "edite a sua tarefa: " << endl;
    getline(cin, novaDescricao);

    for (auto it = tarefas.begin(); it != tarefas.end(); ++it)
    {
        if (it->id == id)
        {
            it->descricao = novaDescricao;
            cout << "tarefa editada com sucesso! ";
            return;
        }
    }
}

// funcao principal
int main()
{
    carregarTarefas("tarefas.txt"); // carrega tarefas ao iniciar

    int opcao;
    while (true)
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Adicionar tarefa\n";
        cout << "2. Listar tarefas\n";
        cout << "3. Concluir tarefa\n";
        cout << "4. editar tarefa\n";
        cout << "5. Remover tarefa\n";
        cout << "6. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
        {
            cin.ignore();
            string descricao;
            cout << "Digite a descricao da tarefa: ";
            getline(cin, descricao);
            adicionarTarefas(descricao);
            salvarTarefasEmArquivo("tarefas.txt"); // salva imediatamente
            break;
        }
        case 2:
        {
            cout << "aqui esta a sua lista de tarefas: " << endl;
            cout << " " << endl;
            listarTarefas();
            break;
        }
        case 3:
        {
            int id;
            cout << "Digite o ID da tarefa que deseja concluir: ";
            cin >> id;
            cout << "voce tem certeza que deseja concluir essa tarefa? " << endl;
            cout << "digite S para concluir e N para nao concluir" << endl;

            string confirmacao;
            cin >> confirmacao;

            if (confirmacao == "s")
            {
                concluirTarefas(id);
                salvarTarefasEmArquivo("tarefas.txt"); // salva imediatamente
            }
            else
            {
                cout << "ok! entao vamos voltar para o menu inicial." << endl;
            }

            break;
        }
        case 4: {
            int id;
            cout << "Digite o ID da tarefa que deseja editar: ";
            cin >> id;

            // Procura a tarefa pelo ID
            auto it = tarefas.begin();
            for (; it != tarefas.end(); ++it) {
                if (it->id == id)
                    break;
            }

            if (it == tarefas.end()) {
                cout << "Tarefa com ID " << id << " não foi encontrada.\n";
                break;
            }

            if (it->concluida) {
             cout << "Não é possível editar uma tarefa já concluída!\n";
                break;
            }

         cin.ignore(); // Limpa o buffer antes do getline
         string novaDescricao;
         cout << "Edite a sua tarefa: ";
         getline(cin, novaDescricao);
         it->descricao = novaDescricao;
         cout << "Tarefa editada com sucesso!\n";
         salvarTarefasEmArquivo("tarefas.txt"); // salva imediatamente
         break;
        }
        case 5:
        {
            int id;
            cout << "Digite o ID da tarefa que deseja remover: ";
            cin >> id;
            cout << "voce tem certeza que deseja remover essa tarefa? " << endl;
            cout << "digite S para remover e N para nao remover" << endl;

            string confirmacao;
            cin >> confirmacao;

            if (confirmacao == "s")
            {
                removerTarefas(id);
                salvarTarefasEmArquivo("tarefas.txt"); // salva imediatamente
            }
            else
            {
                cout << "ok! entao vamos voltar para o menu inicial." << endl;
            }
            break;
        }
        case 6:
        {
            cout << "Saindo do programa...\n";
            return 0;
        }
        default:
            cout << "Opcao invalida, tente novamente.\n";
        }
    }

    return 0;
}