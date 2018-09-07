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

#include "grafos.h"

int main(){

    ifstream file;
    file.open("karate.gml", ios::in);

    //O número de vértices deve ser 35 , para evitar falha de segmentção
    //Porém o vértice 35 não possui ligação alguma com os outros vértices
    Grafo grafo(35); // Número de vértices do grafo
    string line , word;
    int tam , num , op = 0;
    vector <int> source , target; 

    //Leitura do arquivo para construir o grafo
    while(getline (file,line)){
        tam = line.length(); //Tamanho de cada linha do arquivo
        if(tam > 4)
            word = line.substr(4,6);

        if(word == "source"){
            num = 0;
            for(int i = 0 ; i < tam ; i++){
                if(isdigit(line[i])){ //verífico o digito depois de source  
                    if (num == 0) 
						num = (line[i] - 48 ); //Converto o primeiro dígito para inteiro
					else
						num = (num*10) + (line[i] - 48 ); //Transformo o primeiro dígito numa dezena e somo com o outro número
                }
            }
            source.push_back(num); //Armazeno os números encontrados no vetor source
        }
        else if(word == "target"){
            num = 0;
            for(int i = 0 ; i < tam ; i++){
                if(isdigit(line[i])){ //verífico o digito depois de target
                    if (num == 0)
						num = (line[i] - 48 ); //Converto o primeiro dígito para inteiro               
					else    
						num = (num*10) + (line[i] - 48 ); //Transformo o primeiro dígito numa dezena e somo com o outro número                      
                }    
            }
            if(num != 0) 
                target.push_back(num); //Armazeno os números encontrados no vetor target
        }   
    }

    //Aqui passamos os valores dos vetores source e target
    //para construir a lista de adjacência de cada vértice
    //sendo que target é adicionado a lista de vizinhos de source
    for(int i = 0 ; i < source.size() ; i++)
        grafo.addAresta(source[i] , target[i]); 
     
    do{
        system("clear");

        cout << "*************************************************" << endl;
        cout << "******               MENU                  ******" << endl;
        cout << "Informe a opcao desejada : " << endl;
        cout << "1 - Grau de saida do vertice" << endl;
        cout << "2 - Todos os cliques maximais" << endl;
        cout << "3 - O Coeficiente de Aglomeracao de cada vertice" << endl;
        cout << "4 - O Coeficiente medio de Aglomeracao do Grafo" << endl;
        cin >> op;

        switch(op){
            case 1:
                for(int i = 1 ; i <= 34 ; i++){
                    cout << "Grau de saida do vertice  " << i << ": " << grafo.GrauSaida(i) << endl;
                    cout << "*********************************** "<< endl;
                }

                break;
            case 2: break;
            case 3: break;
            case 4: break;
            default: cout << "Informe o valor correto" << endl;            
        };

    }while(op >= 1 && op <= 4);  
    
    file.close();

    return 0;
}