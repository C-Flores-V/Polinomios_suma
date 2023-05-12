#include <iostream>
#include <vector>
using namespace std;

struct tPolinomio
{ 
	int grado;                /* Grado del polinomio */
    vector<double> coef;      /* Coeficientes */
};

///////////////////////////////         Prototipos de funciones
tPolinomio str_to_tpol(const string&);
void leer_str_pol(vector<string>&, int);
//////////////////////////////

int main () {
    vector<string> str_polinomios;
    vector<tPolinomio> tpol_polinomios;
    int n_polinomios;
    string temp;

    cout<<"Introduzca la cantidad de polinomios a sumar: ";
    cin>>n_polinomios;
    cin.ignore();
    leer_str_pol(str_polinomios, n_polinomios);                         //Se debe usar cin.ignore() antes de leer_str_pol() si se utiliza cin
    
    for (int k = 0 ; k < n_polinomios; k++)                             //No se si convertir o no este loop en funcion. Se encarga de retirar los espacios de los strings 
                                                                        //Modifica los strings dentro del vector para retirarle los espacios
    {
        for (int i{}; i <= str_polinomios.at(k).size() - 1; i++)
        {
            if (str_polinomios.at(k).at(i) == ' ')
            {
                str_polinomios.at(k).erase(str_polinomios.at(k).begin()+i);
            }   
        }
    }



                                ///Aqui hace falta el comprobante de la validez de los strings ingresados, en el psedocodigo hay unos buenos criterios de como programarlo


    for (const string &polinomio : str_polinomios)                      // Este es el loop que transforma strings a tpolinomio mediante la funcion str_to_tpol() (revisarla)
    {
        tpol_polinomios.push_back(str_to_tpol(polinomio));
    }


    int i = 0;
    for(tPolinomio polinomio : tpol_polinomios)                          // Esto es temporal, imprime los datos contenidos dentro de el vector tpol_polinomios
    {
        cout<<"------------------"<<endl;
        cout<<"Grado del polinomio: "<<polinomio.grado<<endl;
        for (float coeficiente: polinomio.coef){
            cout<<"Coeficiente elevado a la "<<i<<": " <<coeficiente<<endl;
            i++;
        }
        cout<<"------------------"<<endl;
    }


    //Lo que queda pendiente por hacer es 
    //la funcion que sume los polinomios
    //ver la forma de imprimir el resultado de la suma
    //Implementar la comprobaciòn de strings ingresados


}

tPolinomio str_to_tpol(const string &str_polinomio){                    //Anotaciones importantes de esta funcion:
    tPolinomio tpol_polinomio{};                                        //El input de la funcion tiene que estar validado
    string temp_coef{}, temp_grado{"0"};                                //La funcion tiene por output un tPolinomio con el grado mayor de la funcion y los coeficientes en orden
    bool coef = true;                                                   /*Los coeficientes estan ordenados segun el grado de su monomio, es decir si 2*x2 + 3*x5 entonces los
                                                                          coeficientes se ordenaran de forma (0,0,2,0,0,3)*/
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
void leer_str_pol(vector<string>& str_polinomios, int n_polinomios){
    string temp;
    for (int i{0}; i<n_polinomios; i++){
        cout<<"Polinomio " << i+1 <<": ";
        getline(cin,temp);
        str_polinomios.push_back(temp);
    }
}