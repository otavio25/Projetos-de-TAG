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
    vector <int> R , P , X; 

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
    int tam_vector = source.size();
    for(int i = 0 ; i < tam_vector ; i++)
        grafo.addAresta(source[i] , target[i]);   
    
    for (int i=1; i <= 34 ; i++)
		P.push_back(i);
    grafo.Bronkerbosch(R,P,X);

    for(int i = 1 ; i <= 34 ; i++){
        int tam = grafo.DFS(i);

        if(tam != 0)
            cout <<"Id = (" << i <<")"<<"--> contem ciclo"<< "---> qts vertices : " <<tam<<endl;
    }

    do{

        system("clear");

        cout << "***************************************************" << endl;
        cout << "******                 MENU                  ******" << endl;
        cout << "* Informe a opcao desejada :                      *" << endl;
        cout << "* 1 - Grau de saida do vertice                    *" << endl;
        cout << "* 2 - Todos os cliques maximais                   *" << endl;
        cout << "* 3 - O Coeficiente de Aglomeracao de cada vertice*" << endl;
        cout << "***************************************************" << endl;
        cin >> op;

        switch(op){
            case 1: 
                for(int i = 1 ; i <= 34 ; i++){
                    cout << "Grau de saida do vertice  " << i << ": " << grafo.GrauSaida(i) << endl;
                    cout << "*********************************** "<< endl;
                }
                cout << "Aperte <enter> para voltar ao MENU" << endl;
                getchar();
                getchar();
            break;    

            case 2:  
                grafo.run_Bronkerbosch();
                cout << "Aperte <enter> para voltar ao MENU" << endl;
                getchar();
                getchar();
            break;

            case 3: 
                vector<long int> TriExistentes , TriPossiveis;

                for(int i = 1 ; i <= 34 ; i++){
                    TriExistentes.push_back(grafo.DFS(i));
                    TriPossiveis.push_back((grafo.GrauSaida(i) * (grafo.GrauSaida(i) - 1))/2);
                }

                for(int i = 1 ; i <= 34 ; i++){
                    cout <<"vertice : "<< i <<" coef. aglomeracao "<< TriExistentes[i]<< "/" << TriPossiveis[i] << endl;   
                }

                cout << "Aperte <enter> para voltar ao MENU" << endl;
                getchar();
                getchar();
            break;
                    
        };

    }while(op >= 1 && op <= 4);
    
    file.close();

    return 0;
}