#include <iostream>
#include <fstream>


using namespace std;

int main()
{
    int fieldsCount = 6;
    string filename = "datafile";
    ifstream fileIn (filename);

    if (!fileIn)
    {
        cout << "Cannot open the file!" << endl;
        return 1;
    }

    ofstream fileOut (filename + "_new_format");

    string textlineOriginal;
    while(getline(fileIn, textlineOriginal))
        {
            string textlineNew="";
            textlineNew+=textlineOriginal+"|";
            for (int i=1; i<fieldsCount; i++)
            {
                getline(fileIn, textlineOriginal);
                textlineNew+=textlineOriginal+"|";
            }
            fileOut<<textlineNew<<endl;
        }

    fileIn.close();
    fileOut.close();
}
