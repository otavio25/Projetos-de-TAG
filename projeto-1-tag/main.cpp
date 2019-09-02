#include "grafo.h"

int main(){

    ifstream file;
    file.open("soc-dolphins.txt", ios::in);

    Grafo grafo(63);
    vector <int> source , target;
    int tam, num, num2, op;
    string line;
    vector <int> R , P , X;
    vector<float> coefficients;

    while(getline (file,line)){
        tam = line.length();

        int i;
        num = 0;
        num2 = 0;
        for(i = 0; i < tam; i++){
            if(line[i] != ' ' && i <= 3){
                if(num == 0){
                    num = (line[i] - 48 );
                }
                else{
                    num = (num*10) + (line[i] - 48 );
                }
            }
            else{
                if(line[i] == ' '){
                    i++;
                }                
                if(num2 == 0){
                    num2 = (line[i] - 48 );
                }
                else{
                    num2 = (num2*10) + (line[i] - 48 );
                }
            }
        }
        source.push_back(num);
        target.push_back(num2);      
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
    coefficients = grafo.clusteringCoefficient();

    do{
        int i = 1;
        
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