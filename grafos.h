/* 	Universidade de Brasília
	Instituto de Ciências Exatas
	Departamento de Ciência da Computação
	Teoria e Aplicação de Grafos - 1/2018
	Aluno: Otávio Souza de Oliveira ; Matrícula : 15/0143401
	Versão do compilador: gcc version 7.3.0 (Ubuntu 7.3.0-16ubuntu3)
	Descricao: Este programa Cria um grafo usando lista de adjacência utilizando como entrada o arquivo "karate.gml",
	calcula o Coeficiente de Aglomeracao de cada vertice , assim como o do grafo ; e utiliza o algoritmo de Bron-Kerbosch
    para encontrar os cliques maximais.
	Execução : para executar utilize  g++ -Wall -ansi Projeto1.cpp -o projeto1 e depois utlize ./projeto1 lembrando que 
    para o funcionamento adequado do programa o arquivo "karate.gml" e "grafos.h" precisam estar no mesmo diretório do código fonte.
	 */

#include <iostream>
#include <list>
#include <algorithm> //função find
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

class Grafo{

    int num_vertices;
    list<int> *adj; //ponteiro para vetor contendo lista de adjacencias
    vector< vector<int> > maximal;

    public:
        Grafo(int v); //construtor
        void addAresta (int v1 , int v2);
        int GrauSaida(int v); //verifica o número de arestas ligadas a cada vértice
        bool VerificaVizinho(int v1 , int v2); //Verifica se v2 é vizinho de v1
        void Bronkerbosch(vector<int> R, vector<int> P, vector<int> X);
        void run_Bronkerbosch();
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

bool Grafo::VerificaVizinho(int v1 , int v2){

    if(find(adj[v1].begin(), adj[v1].end() , v2) != adj[v1].end())
        return true;
    return false;    

}

void Grafo::Bronkerbosch(vector<int> R, vector<int> P, vector<int> X){

    vector<int> Paux = P;

    if(P.empty() && X.empty())
        maximal.push_back(R);

    for (int i : Paux){
        vector<int> intersection = {} , intersectionX = {};
        //N(P)
        for (int j : adj[i]){
            for (int k : P){
                if (j == k){
                    intersection.push_back(j);
                }   
            }

            //N(X)
            for (int l : X){
                if (j == l){
                    intersectionX.push_back(j);
                }
            }
        }

        R.push_back(i);
        Bronkerbosch(R,intersection,intersectionX);
        P.erase(remove(P.begin(),P.end(),i),P.end());
        X.push_back(i);    
    }
        
}

void Grafo::run_Bronkerbosch(){

    /*vector<int> R,P,X;

    for (int i=1; i < adj->size(); i++) 
        P.push_back(i);
    
    Bronkerbosch(R,P,X);

    cout << "Numero de maximais: " << maximal.size() << endl;
    for (vector<int> i  : maximal){
        cout << "(";
        for (int j : i)
            cout << j  <<" ";
    
        cout << ")"<< endl;    
    }*/

    sort(maximal.begin(), maximal.end(), [](auto &a, auto &b) {
    	return a.size() > b.size();
	});
	cout << endl;
	cout << "Cliques Maximais: "<< endl<< endl;
	int max = maximal.size();
	for (int j=0;j<max;j++){
		cout << "Clique Maximal: "<< endl;
		int h=0;
		for(int i : maximal[j]) {
			cout << i << " ";
			h++;
		}
		cout << endl <<"numero de vertices:" << h << endl << endl;
	}
	cout << endl << endl;

}

