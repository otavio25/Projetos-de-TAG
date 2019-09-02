#include "grafo.h"

int main(){

    ifstream file;
    file.open("soc-dolphins.txt", ios::in);

    Grafo grafo(63);
    vector <int> source , target;
    int tam, num, op;
    string line, word;
    vector <int> R , P , X;
    vector<float> coefficients;

    while(getline (file,line)){
        tam = line.length();

        word = line.substr(0,6);

        if(word == "source"){
            num = 0;
            for(int i = 0; i < tam; i++){
                if(isdigit(line[i])){
                    if(num == 0){
                        num = (line[i] - 48 );
                    }
                    else{
                        num = (num*10) + (line[i] - 48 );
                    }
                }
            }
            source.push_back(num);
        }
        else if(word == "target"){
            num = 0;
            for(int i = 0; i < tam; i++){
                if(isdigit(line[i])){
                    if(num == 0){
                        num = (line[i] - 48 );
                    }
                    else{
                        num = (num*10) + (line[i] - 48 );
                    }
                }
            }
            target.push_back(num);
        }        
    }

    int size = source.size();

    for(int i = 0; i < size; i++){
        grafo.addAresta(source[i], target[i]);
    }

    for (int i=1; i <= 62 ; i++){
		P.push_back(i);
    }    
    grafo.Bronkerbosch(R,P,X);

    vector<float>::iterator it;
    int i = 1;
    coefficients = grafo.clusteringCoefficient();

    do{
        system("clear");

        cout << "****************************************************" << endl;
        cout << "******                 MENU                  *******" << endl;
        cout << "* Informe a opcao desejada :                       *" << endl;
        cout << "* 1 - Grau de saida do vertice                     *" << endl;
        cout << "* 2 - Todos os cliques maximais                    *" << endl;
        cout << "* 3 - O Coeficiente de Aglomeracao de cada vertice *" << endl;
        cout << "* 4 - O Coeficiente médio de Aglomeração do Grafo  *" << endl;
        cout << "****************************************************" << endl;
        cin >> op;

        switch (op){
            case 1:
                for(int i = 1; i <= 62; i++){
                    cout<< "Grau do vertice " << i << " :--> " << grafo.GrauSaida(i) << endl;
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
                for(it = coefficients.begin(); it != coefficients.end(); ++it){
                    cout << "vertice: " << i << " coeficiente: " << *it << " " << endl;
                    i++;
                }
                cout << endl;
                cout << "Aperte <enter> para voltar ao MENU" << endl;
                getchar();
                getchar();
            break;

            case 4:
                cout << "Coeficiente médio do grafo: " << grafo.graphCoefficient(coefficients, 62) << endl;
                cout << "Aperte <enter> para voltar ao MENU" << endl;
                getchar();
                getchar();
            break;
        }
    }while(op >= 1 && op <= 4); 
    
    file.close();

    return 0;
}