#include <iostream>
#include <vector>
using namespace std;

struct tPolinomio
{ 
	int grado;                /* Grado del polinomio */
    vector<double> coef;      /* Coeficientes */
};

tPolinomio str_to_tpol(string);

int main () {
    vector<string> str_polinomios;
    vector<tPolinomio> tpol_polinomios;
    int n_polinomios;
    string temp;

    cout<<"Introduzca la cantidad de polinomios a sumar: ";
    cin>>n_polinomios;
    
    //////////////Transformar en una funcion
    cin.ignore();
    for (int i{0}; i<n_polinomios; i++){
        cout<<"Polinomio " << i+1 <<": ";
        getline(cin,temp);
        str_polinomios.push_back(temp);
    }
    /////////////////////////////////
    
    for (int k = 0 ; k < n_polinomios; k++)
    {
        for (int i{}; i <= size(str_polinomios.at(k))-1; i++)
        {
            if (str_polinomios.at(k).at(i) == ' ')
            {
                str_polinomios.at(k).erase(str_polinomios.at(k).begin()+i);
            }   
        }
    }

    ///////////////////////////////////////////////////////////////////////////// Hasta aqui funciona perfectamente

    for (string polinomio : str_polinomios)
    {
        tpol_polinomios.push_back(str_to_tpol(polinomio));
    }

    for(tPolinomio polinomio : tpol_polinomios)
    {
        cout<<"------------------"<<endl;
        cout<<polinomio.grado<<endl;
        for (float coeficiente: polinomio.coef)
            cout<<coeficiente<<endl;
        cout<<"------------------"<<endl;
    }

    
}

tPolinomio str_to_tpol(string str_polinomio){   //Si se esta recibiendo str_polinomio correctamente
    tPolinomio tpol_polinomio{};
    string temp_coef{}, temp_grado{"0"};
    bool coef = true;
    
    for (int i = 0 ; i < str_polinomio.length() ; i++) // Correcto
    {
        if (i==0)
            temp_coef.push_back(str_polinomio.at(i));
        else if (str_polinomio.length()-1 == i)
        {
            if (coef)
            {
                temp_coef.push_back(str_polinomio.at(i));
                temp_grado = "0";
            }
            else
                temp_grado.push_back(str_polinomio.at(i));
            if (stoi(temp_grado) >= tpol_polinomio.grado)
            {
                tpol_polinomio.coef.resize(stoi(temp_grado)+1);
                tpol_polinomio.grado = stoi(temp_grado);
            }
            tpol_polinomio.coef.at(stoi(temp_grado)) = stof(temp_coef);
        }
        else if (str_polinomio.at(i) == '+' or str_polinomio.at(i) == '-')
        {
            if (coef)
            {
                temp_coef.push_back(str_polinomio.at(i));
                temp_grado = "0";
            }
            else
                temp_grado.push_back(str_polinomio.at(i));

            if (stoi(temp_grado) >= tpol_polinomio.grado)     
            {
                tpol_polinomio.coef.resize(stoi(temp_grado)+1);
                tpol_polinomio.grado = stoi(temp_grado);
            }
            tpol_polinomio.coef.at(stoi(temp_grado)) = stof(temp_coef);
            coef = true;
            temp_coef = "";
            temp_grado = "";
        }
        else if ((str_polinomio.at(i) >= 48 and str_polinomio.at(i) <= 57 or str_polinomio.at(i) == '.') and coef == true)
            temp_coef.push_back(str_polinomio.at(i));
        else if (str_polinomio.at(i) == '*')
            coef = false;
        else if ((str_polinomio.at(i) >= 48 and str_polinomio.at(i) <= 57) and coef == false)
            temp_grado.push_back(str_polinomio.at(i));
    }
    return tpol_polinomio;
}