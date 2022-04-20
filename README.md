TareaExtraPA
#include <iostream>
#include <limits>
#include <iostream>
#include <vector>
#include <fstream>
/*
 *Ejercicio Extra
 *Daniel Hernandez Toledo
 *Daniel Alejandro Osornio Lopez
*/
using namespace std;
struct productos{
    string ProductName;
    int price{};
    bool stock{true};

public:
    void printProducts() const {
        cout << "Product: " << ProductName << endl;
        cout << "Price: " << price << endl;
    }

    void PrintProductsFile(ofstream & f) const {
        f << "Product: " << ProductName << endl;
        f << "Price: " << price << endl;
    }
};
using namespace std;
void guardar_todo(vector<productos> & arreglo);
void imprimir_todos(vector<productos> & arreglo);
void agregardatos(vector<productos> & arreglo);
void menu();

int main()
{
    fstream f;
    vector<productos>productos;
    int opcion =0, lazy;
    do
    {
        guardar_todo(productos);
        menu();
        cout<<"Ingrese la opcion: ";
        cin >> opcion;
        imprimir_todos(productos);
        switch (opcion)
        {
            case 1:
            {
                int lenn;
                cout << "Ingrese la cantidad de productos a agregar: ";
                cin >> lenn;

                for (int i=0; i<lenn; i++)
                    agregardatos(productos);
                break;

            }
            case 2:
            {
                string buscar;
                cout << "Ingrese un productos a buscar: ";
                cin >> buscar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for (auto & producto : productos) {
                    if (buscar == producto.ProductName) {
                        cout << "El productos ah sido encontrado exitosamente: " << producto.ProductName << endl;
                        producto.printProducts();

                    } else {
                        cout << "Libro no encontrado" << endl;
                    }

                }
            }

                break;

            case 3:
            {

                do{

                cout << "Ingresa la posicion del productos a devolver: ";
                cin >> lazy;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            } while (lazy < 0 || lazy > productos.size() - 1);
            productos[lazy].stock = true;
            break;
        }
        case 4:
        {
            do {
                cout << "Ingresa la posicion del productos a devolver: ";
                    cin >> lazy;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                } while (lazy < 0 || lazy > productos.size() - 1);

            productos[lazy].stock = true;

                break;
            }

            default:
                break;
        }

    } while (opcion != 5);

}

void menu()
{
    cout<<"MENU DEL SUPER"<<endl;
    cout<<"1. Agregar producto "<<endl;
    cout<<"2. Eliminar Producto "<<endl;
    cout<<"3. Modificar"<<endl;
    cout<<"4. Consulta"<<endl;
    cout<<"5. Comprar"<< endl;
    cout<<"6. Devolución"<<endl;
}

void guardar_todo(vector<productos> & arreglo) {
    ofstream f;
    f.open("products.txt");

    if (!f)
    {
        cout << "Algo salio mal al guardar los datos" << endl;
    }

    for (int i=0; i<arreglo.size(); i++)
    {
        f << "Id: " <<i << endl;
        arreglo[i].PrintProductsFile(f);
    }

}


void imprimir_todos(vector<productos> & arreglo)
{
    if (arreglo.empty())
    {
        cout << "No hay elementos en la lista" << endl;
        return;
    }

    for (int i=0; i<arreglo.size(); i++)
    {
        cout << "Id: " <<i << endl;
        arreglo[i].printProducts();
    }
}

void agregardatos(vector<productos> & arreglo)
{
    productos valor;
    string NameProduct;
    int prices;
    bool disponibilidad;
    cin.sync();
    cout << "Ingrese NameProduct: ";
    getline(cin, NameProduct);
    cin.sync();
    cout << "Ingrese price: ";
    cin>>prices;
    disponibilidad = true;

    valor ={
            NameProduct,
            prices,
            disponibilidad
    };

    arreglo.push_back(valor);
}

