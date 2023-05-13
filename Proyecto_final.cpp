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
bool comprobacion(string);
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
        {
            temp_coef.push_back(str_polinomio.at(i));
            if (str_polinomio.length()-1 == i)
            {
                tpol_polinomio.coef.resize(1);
                tpol_polinomio.coef.at(stoi(temp_grado)) = stof(temp_coef);
            }
                
        }
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
        while (true)
        {
            if(comprobacion(temp))
            {                                                    //Comprobacion
                str_polinomios.push_back(temp);
                break;
            }
            else
                cout<<"Error, ingrese nuevamente el polinomio: ";
                getline(cin,temp);
        }
    }
}
bool comprobacion(string temp){
    string lugar_monomio = {"entero"};                      // Variable que guarda la ubicacion en la que se encuentra i dentro de la string, puede ser entero, decimal o grado
    bool primer_espacio = true;
    char p_caracter_entre_espacios{};

    if (temp.empty())
        return false;
    for (int i = 0 ; i <= temp.size()-1 ; i++)
    {
        if (!(temp.at(i) <= 57 and temp.at(i) >= 48 or temp.at(i) == '*' or temp.at(i) == '-' or temp.at(i) == '+' or temp.at(i) == '.' or temp.at(i) == 'x' or temp.at(i) == ' '))                     //Se comprueba si los caracteres ingresados estan dentro del rango valido
            return false;
    }
    
    if (!(temp[0]=='-' or temp[0]=='+' or temp[0]==' ' or (temp.at(0) <= 57 and temp.at(0) >= 48)))     //Comprueba si la string comienza con un caracter valido
    {
        return false;
    }
    
    for (int i = 1 ; i <= temp.size()-1 ; i++)                      //Revision letra por letra de los strings a partuir del indice 1
    {                                                               //La verificacion esta planificada por caracteres (Que pasa si temp.at(i) == 'x' por ejemplo)                
        if (temp[i] == ' ')
        {
            if(i == 1)                                   //Aqui se revisan los casos que existen cuando el caracter es un espacio y esta en la segunda posicion
            {
                while (i <= temp.size()-1 and temp.at(i) == ' ')
                    i++;
                if (i == temp.size())
                    return false;
                if (!(temp.at(i) <= 57 and temp.at(i) >= 48))
                    return false;
            }
            else
            {
                if (primer_espacio == true)
                    p_caracter_entre_espacios = temp.at(i-1);
                    primer_espacio = false;
                if (i <= temp.size()-2 and !(temp.at(i+1) == '+' or temp.at(i+1) == '-' or (temp.at(i+1) <= 57 and temp.at(i+1) >= 48) or temp.at(i+1) == ' '))
                    return false;
                else if (!(temp.at(i-1) == '+' or temp.at(i-1) == '-' or (temp.at(i-1) <= 57 and temp.at(i-1) >= 48) or temp.at(i-1) == ' '))
                    return false;
                else
                {
                    while (i <= temp.size()-2 and (i <= temp.size()-1 and temp.at(i+1) == ' '))
                        i++;
                    if (i <= temp.size()-2 and ((p_caracter_entre_espacios == '+' and temp.at(i+1) == '+') 
                        or (p_caracter_entre_espacios == '-' and temp.at(i+1) == '-') 
                        or (p_caracter_entre_espacios == '+' and temp.at(i+1) == '-') 
                        or (p_caracter_entre_espacios == '-' and temp.at(i+1) == '+') 
                        or ((temp.at(i+1) <= 57 and temp.at(i+1) >= 48) and (p_caracter_entre_espacios <= 57 and p_caracter_entre_espacios >= 48))))
                        return false;
                }
                primer_espacio = true;
            }    
        }
        else if (temp.at(i) <= 57 and temp.at(i) >= 48)
        {
            if ((i < (temp.size()-1)) and lugar_monomio == "entero" and !((temp.at(i+1) <= 57 and temp.at(i+1) >= 48) or temp.at(i+1) == '.' or temp.at(i+1) == '*' or temp.at(i+1) == ' '))
                return false;
            else if ((i < (temp.size()-1)) and lugar_monomio == "decimal" and !((temp.at(i+1) <= 57 and temp.at(i+1) >= 48) or temp.at(i+1) == '*' or temp.at(i+1) == ' '))
                return false;
            else if ((i < (temp.size()-1)) and lugar_monomio == "grado" and !((temp.at(i+1) <= 57 and temp.at(i+1) >= 48) or temp.at(i+1) == ' ' or temp.at(i+1) == '+' or temp.at(i+1) == '-' or temp.at(i+1) == ' '))
                return false;
            else
                continue;
        }
        
        else if (temp.at(i) == '.')
        {
            lugar_monomio = "decimal";
            if (!(temp.at(i+1) <= 57 and temp.at(i+1) >= 48))
                return false;
            else
                continue;
        }
        
        else if (temp.at(i) == '*')
        {
            lugar_monomio = "grado";
            if (temp.at(i+1) != 'x')
                return false;
            else
                continue;
        }
        else if (temp.at(i) == 'x')
        {
            if (!(temp.at(i+1) <= 57 and temp.at(i+1) >= 48))
                return false;
            else
                continue;
        }
        else if (temp.at(i) == '+' or temp.at(i) == '-' )
        {
            if (!((temp.at(i+1) <= 57 and temp.at(i+1) >= 48) or temp.at(i+1) == ' '))
                return false;
            else
                lugar_monomio = "entero";
                continue;
        }
        
        
            //Siguiente comprobacion: Si "x", "*", ".", el siguiente caracter no puede ser un espacio,
            //Si "char numero", y el siguiente caracter es un espacio, se debe recorrer mediante un bucle un temp.at() todos los espacios hasta encontrar un "+", caso contrario se retorna falso
            //Si "+" o "-", y el siguiente caracater es un espacio, se se debe recorrer mediante un bucle un temp.at() todos los espacios  hasta encontrar un numero, caso contrario se retorna falso
    }
    return true;
}