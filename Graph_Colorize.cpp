﻿#include <iostream>
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

class Graph_object
{
private:
    vector <element> Graph;
    vector <unsigned int> color;
    int color_counter = 1;
public:

    Graph_object(vector <element> data) : Graph(data)
    {
        color.resize(data.size(), 0);
        Graph_transform();
        color[Graph[0].num] = color_counter;
    }

    int get_degree(element & node)
    {
        int counter = 0;
        for (auto x : node.edges)
            if (color[x] == 0)
                counter++;
    }

    void Graph_transform()
    {
        sort(Graph.begin(), Graph.end(), [=](element a, element b)
            {return get_degree(a) > get_degree(b); });
    }

    bool color_node_check(int colr_check, element obj)
    {
        for (auto x : obj.edges)
            if (color[x] == colr_check)
                return false;
        return true;
    }

    bool try_colorize()
    {
        bool flag = false;
        for (auto x : Graph)
            if (color[x.num] == 0)
                if (color_node_check(color_counter, x))
                {
                    flag = true;
                    color[x.num] = color_counter;
                }                    
        color_counter++;
        Graph_transform();
        return flag;
    }

    int return_chr()
    {
        return color_counter;
    }
};

class element
{
public:
    vector <int> edges;
    int num = 0;
    element(int data) : num(data)
    {};

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
    return edge(stod(data.substr(0, pos)) - 1, stod(data.substr(pos + transp)) - 1);
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
                vector <element> Graph(N);
                for (int i = 0; i < N; i++)
                    Graph[i] = element(i);
                while (getline(file, buf))
                {
                    if (buf == "") continue;
                    start_data = split(buf);
                    Graph[start_data.x].edges.push_back(start_data.y);
                    Graph[start_data.y].edges.push_back(start_data.x);
                }
                file.close();
                Graph_object test_data(Graph);
                while (!test_data.try_colorize()) {}
            }
        }
    catch (exception& e)
    {
        cout << e.what();
        cin.get();
    }
    fout.close();
}

