#include <iostream>
#include <list>
#include <algorithm> 
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
        void Bronkerbosch(vector<int> R, vector<int> P, vector<int> X); //Verifica cliques maximais e armazema no vetor maximais 
        void run_Bronkerbosch();//Imprime na tela os cliques maximais
        bool exists(int value, vector<int> v);
        vector<vector<int>> getTriplets();
        vector<float> clusteringCoefficient();
        float graphCoefficient(vector<float> coefficients,int size);
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

bool Grafo::exists(int value, vector<int> v) {
    vector<int>::iterator it;
    for(it = v.begin(); it != v.end(); ++it) {
        if(value == *it) {
            return true;
        }
    }
    return false;
}

// ======= Coeficiente de Aglomeração ====== //

// Retorna um vetor com todos os cliques que são triangulos (triplets)
vector<vector<int>> Grafo::getTriplets(){
    vector<vector<int>>::iterator it = maximal.begin();
    vector<vector<int>> triplets;
    for(it = maximal.begin(); it != maximal.end(); ++it){
        if(it->size() >= 3) {
            triplets.push_back(*it);
        }
    }
    return triplets;
}

// Retorna um vetor com os coeficientes de aglomeração de cada nó
vector<float> Grafo::clusteringCoefficient() {
    vector<vector<int>> triplets = getTriplets();
    vector<float> coefficient_vector = {};

    int adj_size;
    float possible;  // numero de triplets possiveis daquele nó
    float real = 0;  // numero de triplets existentes daquele nó
    float coefficient;

    for(int i = 1; i <= num_vertices; i++) {
        if(adj[i].size() == 0){
            continue;
        }
        possible = adj[i].size() * (adj[i].size() - 1);
        if(possible > 0) {
            real = 0;
            for(int j = 0; j < triplets.size();j++) {
                if(exists(i, triplets[j])){
                    if(triplets[j].size() == 5){
                        real += 4;
                    }
                    else if(triplets[j].size() == 4){
                        real += 3;
                    }
                    else {
                        real++;
                    }
                }
            }
            coefficient = (2*real)/possible;
            coefficient_vector.push_back(coefficient);
        }
        else{
            coefficient_vector.push_back(0);
        }
    }
    return coefficient_vector;
}

// Retorna coeficiente médio do grafo
float Grafo::graphCoefficient(vector<float> coefficients,int size) {
    vector<float>::iterator it;
    float sum = 0;
    for(it = coefficients.begin(); it !=  coefficients.end(); ++it) {
        sum += *it;
    }
    return sum/num_vertices;
}