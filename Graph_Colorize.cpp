#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
using namespace std;

class edge
{
public:
    int x, y;
    edge(int a, int b) : x(a), y(b)
    {

    };
};

vector <string> list_files(string dir)
{
    vector <string> result;
    for (const auto& entry : filesystem::directory_iterator(dir))
        result.push_back(entry.path().string().substr(5));
    return result;
}

edge split(string& data, string file_debug = "")
{
    auto pos = data.find(" ");
    int transp;
    if (data.find("  ") != string::npos) transp = 2;
    else transp = 1;
    return edge(stod(data.substr(0, pos)), stod(data.substr(pos + transp)));
}


int main()
{
    vector <string> data = list_files("data");
    string buf;
    ofstream fout;
    fout.open("result.txt");
    string x;
    try {
        for (int k = 0; k < data.size(); k++)
        {
            x = data[k];
            cout << "Starting " << x << endl << flush;
            ifstream file("data/" + x);
            getline(file, buf);
            edge start_data = split(buf);
            int N = start_data.x;
            vector <vector <int>> Graph (N, vector <int> (0))
            while (getline(file, buf))
            {
                if (buf == "") continue;
                start_data = split(buf);
                Graph[start_data.x].push_back(start_data.y);
                Graph[start_data.y].push_back(start_data.x);
            }
            file.close();
            
        }
    }
    catch (exception& e)
    {
        cout << e.what();
        cin.get();
    }
    fout.close();
}

