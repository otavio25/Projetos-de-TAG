//Busca em profundidade DFS

#include <iostream>
#include <list>
#include <algorithm> //função find
#include <stack> //add pilha

using namespace std;

class Grafo{

    int num_vertices;
    list<int> *adj; //ponteiro para vetor contendo lista de adjacencias

    public:
        Grafo(int v); //construtor
        void addAresta (int v1 , int v2);
        void DFS(int v); //Faz DFS a partir de um vértice

};

Grafo::Grafo(int v){
    this -> num_vertices = v;
    adj = new list<int>[v]; //cria as listas
}

void Grafo::addAresta(int v1 , int v2){

    adj[v1].push_back(v2); // adiciona vertice v2 a lista de vizinhovertices adjacentes de v1
}

void Grafo::DFS(int v){

    stack<int> pilha;
    bool visitados[v]; //vetor de visitados

    for(int i = 0 ; i < v ; i++) //Marcar como não visitado
        visitados[i] = false;

    while(true){
        if(!visitados[v]){
            cout<<"Visitando vertice v : "<< v << endl;
            visitados[v] = true; //Marca como visitado
            pilha.push(v); //insere na pilha
        }
    

        //busca por um vizinho não visitado
        list<int>::iterator it;
        bool achou = false;

        for(it = adj[v].begin() ; it != adj[v].end() ; it++){
            if(!visitados[*it]){
                achou = true;
                break;
            }
        }

        if(achou)
            v = *it; //atualiza o v
        else{
            // se todos os vizinhos forem visitados ou não existem vizinhos
            //remove da pilha
            pilha.pop();
            //se a pilha ficar vazia então terminou a busca
            if(pilha.empty())
                break;
            
            v = pilha.top(); // se chegou até aqui , é pq pode pegar um elemento do topo   
        }    
    }

}

int main (){

    Grafo grafo(8);

    grafo.addAresta( 0 , 1);
    grafo.addAresta( 0 , 2);
    grafo.addAresta( 1 , 3);
    grafo.addAresta( 1 , 4);
    grafo.addAresta( 2 , 5);
    grafo.addAresta( 2 , 6);
    grafo.addAresta( 6 , 7);

    grafo.DFS(0);

    return 0;
}