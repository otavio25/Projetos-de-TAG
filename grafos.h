/* 	Universidade de Brasília
	Instituto de Ciências Exatas
	Departamento de Ciência da Computação
	Teoria e Aplicação de Grafos - 1/2018
	Aluno: Otávio Souza de Oliveira ; Matrícula : 15/0143401
	Versão do compilador: gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.10)
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

    public:
        Grafo(int v); //construtor
        void addAresta (int v1 , int v2);
        int GrauSaida(int v); //verifica o número de arestas ligadas a cada vértice
        bool VerificaVizinho(int v1 , int v2); //Verifica se v2 é vizinho de v1
};

Grafo::Grafo(int v){
    this -> num_vertices = v;
    adj = new list<int>[v]; //cria as listas
}

void Grafo::addAresta(int v1 , int v2){

    adj[v1].push_back(v2); // adiciona vertice v2 a lista de vizinhovertices adjacentes de v1
}

int Grafo::GrauSaida(int v){
    return adj[v].size(); // Basta retornar o tamanho da lista que é a qtd de vizinhos
}

bool Grafo::VerificaVizinho(int v1 , int v2){

    if(find(adj[v1].begin(), adj[v1].end() , v2) != adj[v1].end())
        return true;
    return false;    

}