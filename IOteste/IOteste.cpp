// IOteste.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using std::stringstream;

#include "IODataFile.h"
#include "User.h"

stringstream loremIpsum;



string getLoremIpsumString() {
    loremIpsum << " >>-----> Lorem ipsum dolor sit amet, consectetur adipiscing elit. \n" <<
        "Donec vehicula sem quis accumsan cursus. Sed blandit vehicula risus sit amet \n" <<
        "mollis. Vivamus porta felis nec diam volutpat, nec vestibulum turpis fringilla. \n" <<
        "Nullam at tincidunt elit. Donec porta tortor vitae orci sodales \n" <<
        "euismod. Nullam sodales consequat nulla, nec imperdiet libero congue vitae. \n" <<
        "In at ex sed lectus dictum feugiat ut eu ipsum. Nulla leo erat, maximus a \n" <<
        "diam non, tristique ultrices elit.";
    return loremIpsum.str();
}

int main()
{
    int option = 0;

    IODataFile io;

    while (option != 3)
    {
        cout << "Escolha o tipo de operacao: \n";
        cout << "1 - Leitura \n";
        cout << "2 - Escrita \n";
        cout << "3 - Sair \n";

        cin >> option;
        getchar();
        
        if (option == 1)
        {
            cout << "Escolha o modo do arquivo: \n";
            cout << "1 - Texto \n";
            cout << "2 - Binario \n";
            cout << "3 - Sair \n";

            cin >> option;
            getchar();

            char fileName[100];
            system("cls");
            cout << "Informe o nome do arquivo." << endl;
            cin.getline(fileName, 100);

            if (option == 1)
            {
                io.open2Read(fileName, ios::_Nocreate);
                char line[1024];
                while (io.readLine(line)) {
                    cout << line << endl;
                }
            }
            else if (option == 2)
            {
                try {
                    io.open2Read(fileName, ios::binary);
                    char line[1024];
                    User u;
                    while (io.readObject<User>(&u))
                        u.print();
                }
                catch (IOFileException err) {
                    cout << err.what() << endl;
                }
                
            }
            else
            {
                cout << "Opção " << option << " não existente." << endl;
            }

            io.closeReadStream();
        }
        else if (option == 2) 
        {
            cout << "Escolha o modo do arquivo: \n";
            cout << "1 - Texto \n";
            cout << "2 - Binario \n";
            cout << "3 - Sair \n";

            cin >> option;
            getchar();

            char fileName[100];
            system("cls");
            cout << "Informe o nome do arquivo." << endl;
            cin.getline(fileName, 100);

            if (option == 1) 
            {
                io.open2Write(fileName, ios::trunc);

                system("cls");
                io.writeLine(getLoremIpsumString().c_str());
            }
            else if (option == 2)
            {
                system("cls");
                io.open2Write(fileName, ios::binary);
                User u;
                u.getNewUser();
                //io.writeObject<User>(&u);
                io.writeObject<User>(&u, 3);
            }
            else
            {
                cout << "Opção " << option << " não existente." << endl;
            }

            io.closeWriteStream();
        }
        else if (option == 3)
        {
            cout << "finalizando... \n";
        }
        else
        {
            cout << "Opção " << option << " não existente." << endl;
        }

    }
    
    
    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
