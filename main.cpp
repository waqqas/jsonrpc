#include <iostream>
#include <fstream>

#include "json_rpc.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "Usage: main json-file" << endl;
        return -1;
    }

    ifstream jsonFile(argv[1]);
    if (jsonFile.is_open())
    {
        jsonrpc::parser parser(jsonFile);
        // try
        // {
        parser.parse();
        // }
        // catch (exception &e)
        // {
        //     cerr << e.what() << endl;
        // }

        jsonFile.close();
    }
    return 0;
}