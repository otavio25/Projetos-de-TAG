/* 	Universidade de Brasília
	Departamento de Ciência da Computação
	Teoria e Aplicação de Grafos - 2/2018
	Aluno: Otávio Souza de Oliveira ; Matrícula : 15/0143401
	Versão do compilador: gcc version 7.3.0 (Ubuntu 7.3.0-16ubuntu3)
	Descricao: Este programa Cria um grafo usando lista de adjacência utilizando como entrada o arquivo "karate.gml",
	calcula o Coeficiente de Aglomeracao de cada vertice , assim como o do grafo ; e utiliza o algoritmo de Bron-Kerbosch
    para encontrar os cliques maximais.
	Execução : para executar utilize  g++ Projeto1.cpp -o projeto1 e depois utlize ./projeto1 lembrando que 
    para o funcionamento adequado do programa o arquivo "karate.gml" e "grafos.h" precisam estar no mesmo diretório do código fonte.
	 */

#include <iostream>
#include <list>
#include <algorithm> 
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stack>

using namespace std;

class Grafo{

    int num_vertices;
    list<int> *adj; //ponteiro para vetor contendo lista de adjacencias
    vector< vector<int> > maximal;

    public:
        Grafo(int v); //construtor
        void addAresta (int v1 , int v2);
        int GrauSaida(int v); //verifica o número de arestas ligadas a cada vértice
        int DFS(int v); //Verifica se grafo possui ciclos
        void Bronkerbosch(vector<int> R, vector<int> P, vector<int> X); //Verifica cliques maximais e armazema no vetor maximais 
        void run_Bronkerbosch();//Imprime na tela os cliques maximais
};

Grafo::Grafo(int v){
    this -> num_vertices = v;
    adj = new list<int>[v]; //cria as listas de adjacência
}

void Grafo::addAresta(int v1 , int v2){

    adj[v1].push_back(v2); // adiciona vertice v2 a lista de vizinhovertices adjacentes de v1
    adj[v2].push_back(v1); // adiciona vertice v1 a lista de vizinhovertices adjacentes de v2
    //Isso é realizado pois é um grafo não direcionado
}

int Grafo::GrauSaida(int v){
    return adj[v].size(); // Basta retornar o tamanho da lista que é a qtd de vizinhos
}

void Grafo::Bronkerbosch(vector<int> R, vector<int> P, vector<int> X){

    vector<int> Paux = P;

    if(P.empty() && X.empty())
        maximal.push_back(R);

    for (int i : Paux){
        vector<int> intersectionP = {} , intersectionX = {};
        //N(P)
        for (int j : adj[i]){
            for (int k : P){
                if (j == k){
                    intersectionP.push_back(j);
                }   
            }

            //N(X)
            for (int l : X){
                if (j == l){
                    intersectionX.push_back(j);
                }
            }
        }

        vector<int> Raux = R;
        Raux.push_back(i);
        Bronkerbosch(Raux,intersectionP,intersectionX);
        P.erase(remove(P.begin(),P.end(),i),P.end());
        X.push_back(i);    
    }
        
}

void Grafo::run_Bronkerbosch(){

    vector<int> R,P,X;

    for (int i=1; i < adj->size(); i++) 
        P.push_back(i);
    
    Bronkerbosch(R,P,X);

    for (vector<int> i : maximal){
        cout << "Clique maximal : --> (";
        for (int j : i)
            cout << j  <<" ";    
    
        cout << ")"<< endl;    
    }
      
}


int Grafo::DFS(int v){

    stack<int> pilha;
	bool visitados[v], pilha_rec[v];
    int qtd_vertice = 0;

	// inicializa visitados e pilha_rec com false
	for(int i = 0; i < v; i++)
		visitados[i] = pilha_rec[i] = false;

	// faz uma DFS
	while(true){

		bool achou_vizinho = false;
		list<int>::iterator it;

		if(!visitados[v]){

			pilha.push(v);
			visitados[v] = pilha_rec[v] = true;
            qtd_vertice++; //conta a qtd de vértices que estam sendo analisados
		}

		for(it = adj[v].begin(); it != adj[v].end(); it++){
			// se o vizinho já está na pilha é porque existe ciclo e retorna a quantidade de vértices
			if(pilha_rec[*it])
				return qtd_vertice;
			else if(!visitados[*it]){
				// se não está na pilha e não foi visitado, indica que achou
				achou_vizinho = true;
				break;
			}
		}

		if(!achou_vizinho){

			pilha_rec[pilha.top()] = false; // marca que saiu da pilha
			pilha.pop(); // remove da pilha
			if(pilha.empty())
				break;
			v = pilha.top();
		}
		else{
			v = *it;
        }    
	}

	return 0;   

}




