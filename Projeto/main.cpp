#include <iostream>
#include <fstream>
#include <locale>
using namespace std;

struct Candidato {
    string nome;
    int numero;
    int votos;

    Candidato(string nome, int numero) : nome(nome), numero(numero), votos(0) {}
};

struct Eleitor {
    string nome;
    int titulo;

    Eleitor(string nome, int titulo) : nome(nome), titulo(titulo) {}
};

struct Voto {
    int eleitorTitulo;
    int candidatoNumero;
};

struct Relatorio {
    int totalVotos;
    int eleitoresFaltantes;
};

void adicionarCandidato(Candidato* candidatos[], int& numCandidatos) {
    string nome;
    int numero;
	
	cout << endl;
    cout << "Digite o nome do candidato: ";
    cin >> nome;
    cout << "Digite o número do candidato: ";
    cin >> numero;

    candidatos[numCandidatos] = new Candidato(nome, numero);
    numCandidatos++;
}

void removerCandidato(Candidato* candidatos[], int& numCandidatos) {
    int numero;

	cout << endl;
    cout << "Digite o número do candidato a ser removido: ";
    cin >> numero;

    for (int i=0; i<numCandidatos; i++) {
        if (candidatos[i]->numero == numero) {
            delete candidatos[i];
            for (int j=i; j<numCandidatos-1; j++) {
                candidatos[j] = candidatos[j + 1];
            }
            numCandidatos--;
            cout << endl;
            cout << "Candidato removido com sucesso" << endl;
            system("pause");
            return;
        }
    }
	
	cout << endl;
    cout << "Candidato não encontrado" << endl;
    system("pause");
}

void listarCandidatos(Candidato* candidatos[], int numCandidatos) {
	cout << endl;
    cout << "Candidatos:" << endl;
    for (int i=0; i<numCandidatos; i++) {
        cout << candidatos[i]->nome << " - Número: " << candidatos[i]->numero << endl;
    }
    system("pause");
}

void adicionarEleitor(Eleitor* eleitores[], int& numEleitores) {
    string nome;
    int titulo;
	
	cout << endl;
    cout << "Digite o nome do eleitor: ";
    cin >> nome;
    cout << "Digite o número do título do eleitor: ";
    cin >> titulo;

    eleitores[numEleitores] = new Eleitor(nome, titulo);
    numEleitores++;
}

bool verificarEleitor(Eleitor* eleitores[], int numEleitores, int titulo) {
    for (int i=0; i<numEleitores; i++) {
        if (eleitores[i]->titulo == titulo) {
            return true;
        }
    }
    return false;
}

void registrarVoto(Eleitor* eleitores[], int numEleitores, Candidato* candidatos[], int numCandidatos, Voto* votos[], int& numVotos) {
    int titulo, numero;
	
	cout << endl;
    cout << "Digite o número do título do eleitor: ";
    cin >> titulo;

    if (!verificarEleitor(eleitores, numEleitores, titulo)) {
        cout << "Eleitor não está apto para votar" << endl;
        system("pause");
        return;
    }
	
	cout << endl;
    cout << "Candidatos disponíveis:" << endl;
    listarCandidatos(candidatos, numCandidatos);
	
	cout << endl;
    cout << "Digite o número do candidato escolhido: ";
    cin >> numero;

    bool candidatoValido = false;
    for (int i=0; i<numCandidatos; i++) {
        if (candidatos[i]->numero == numero) {
            candidatoValido = true;
            break;
        }
    }

    if (!candidatoValido) {
        cout << "Candidato inválido" << endl;
        system("pause");
        return;
    }

    votos[numVotos] = new Voto{titulo, numero};
    numVotos++;
	
	cout << endl;
    cout << "Voto registrado com sucesso" << endl;
    system("pause");
}

void gerarRelatorio(Candidato* candidatos[], int numCandidatos, Voto* votos[], int numVotos, int numEleitores) {
	cout << endl;
    cout << "Relatório de votação:" << endl;
	
	cout << endl;
    cout << "Total de votos registrados: " << numVotos << endl;
	
	cout << endl;
    cout << "Votos por candidato:" << endl;
    for (int i=0; i<numCandidatos; i++) {
        int numVotosCandidato = 0;
        for (int j=0; j<numVotos; j++) {
            if (votos[j]->candidatoNumero == candidatos[i]->numero) {
                numVotosCandidato++;
            }
        }
        cout << candidatos[i]->nome << ": " << numVotosCandidato << " votos" << endl;
    }

    int eleitoresFaltantes = numEleitores - numVotos;
    cout << endl;
    cout << "Eleitores que faltaram: " << eleitoresFaltantes << endl;
    
    ofstream arquivo("relatorio.txt");
    if (arquivo.is_open()) {
        arquivo << "Relatório de votação:" << endl;
        arquivo << "Total de votos registrados: " << numVotos << endl;
        arquivo << "Votos por candidato:" << endl;
        for (int i=0; i<numCandidatos; i++) {
            int numVotosCandidato = 0;
            for (int j=0; j<numVotos; j++) {
                if (votos[j]->candidatoNumero == candidatos[i]->numero) {
                    numVotosCandidato++;
                }
            }
            arquivo << candidatos[i]->nome << ": " << numVotosCandidato << " votos" << endl;
        }
        arquivo << "Eleitores que faltaram: " << eleitoresFaltantes << endl;
        arquivo.close();
        cout << "Relatório salvo em 'relatorio.txt'" << endl;
    } else {
        cout << "Erro ao salvar o relatório" << endl;
    }
    system("pause");
}

void salvarCandidatos(Candidato* candidatos[], int numCandidatos) {
    ofstream arquivo("candidatos.txt");
    if (arquivo.is_open()) {
        arquivo << numCandidatos << endl;
        for (int i=0; i<numCandidatos; i++) {
            arquivo << candidatos[i]->nome << " " << candidatos[i]->numero << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro ao salvar os candidatos" << endl;
        system("pause");
    }
}

void salvarEleitores(Eleitor* eleitores[], int numEleitores) {
    ofstream arquivo("eleitores.txt");
    if (arquivo.is_open()) {
        arquivo << numEleitores << endl;
        for (int i=0; i<numEleitores; i++) {
            arquivo << eleitores[i]->nome << " " << eleitores[i]->titulo << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro ao salvar os eleitores" << endl;
        system("pause");
    }
}

void carregarCandidatos(Candidato* candidatos[], int& numCandidatos) {
    ifstream arquivo("candidatos.txt");
    if (arquivo.is_open()) {
        arquivo >> numCandidatos;
        for (int i=0; i<numCandidatos; i++) {
            string nome;
            int numero;
            arquivo >> nome >> numero;
            candidatos[i] = new Candidato(nome, numero);
        }
        arquivo.close();
    } else {
        cout << "Erro ao carregar os candidatos" << endl;
        system("pause");
    }
}

void carregarEleitores(Eleitor* eleitores[], int& numEleitores) {
    ifstream arquivo("eleitores.txt");
    if (arquivo.is_open()) {
        arquivo >> numEleitores;
        for (int i=0; i<numEleitores; i++) {
            string nome;
            int titulo;
            arquivo >> nome >> titulo;
            eleitores[i] = new Eleitor(nome, titulo);
        }
        arquivo.close();
    } else {
        cout << "Erro ao carregar os eleitores" << endl;
        system("pause");
    }
}

main() {
	setlocale(LC_ALL, "Portuguese");
		
    const int MAX_CANDIDATOS = 50;
    const int MAX_ELEITORES = 100;
    const int MAX_VOTOS = 100;

    Candidato* candidatos[MAX_CANDIDATOS];
    int numCandidatos = 0;

    Eleitor* eleitores[MAX_ELEITORES];
    int numEleitores = 0;

    Voto* votos[MAX_VOTOS];
    int numVotos = 0;

    carregarCandidatos(candidatos, numCandidatos);
    carregarEleitores(eleitores, numEleitores);

    int opcao;
    
    do {
    	system("cls");
        cout << "===== MENU DE ESCOLHAS =====" << endl;
        cout << "1 - Adicionar candidato" << endl;
        cout << "2 - Remover candidato" << endl;
        cout << "3 - Listar candidatos" << endl;
        cout << "4 - Adicionar eleitor" << endl;
        cout << "5 - Registrar voto" << endl;
        cout << "6 - Gerar relatório" << endl;
        cout << "7 - Sair" << endl;
        cout << "============================" << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarCandidato(candidatos, numCandidatos);
                break;
                
            case 2:
                removerCandidato(candidatos, numCandidatos);
                break;
                
            case 3:
                listarCandidatos(candidatos, numCandidatos);
                break;
                
            case 4:
                adicionarEleitor(eleitores, numEleitores);
                break;
                
            case 5:
                registrarVoto(eleitores, numEleitores, candidatos, numCandidatos, votos, numVotos);
                break;
                
            case 6:
                gerarRelatorio(candidatos, numCandidatos, votos, numVotos, numEleitores);
                break;
                
            case 7:
                salvarCandidatos(candidatos, numCandidatos);
                salvarEleitores(eleitores, numEleitores);
                break;
                
            default:
                cout << "Opção inválida. Digite novamente" << endl;
                system("pause");
                break;
        }
    } while (opcao != 7);

    for (int i= 0; i<numCandidatos; i++) {
        delete candidatos[i];
    }

    for (int i=0; i<numEleitores; i++) {
        delete eleitores[i];
    }

    for (int i=0; i<numVotos; i++) {
        delete votos[i];
    }
}

