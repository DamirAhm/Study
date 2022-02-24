#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>


using namespace std;

string replace_space_groups(string str, int len) {
    bool last_was_space = false;
    
    string new_string = "";
    
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            if (!last_was_space) {
                new_string += str[i];
                last_was_space = true;
            }
        } else { 
            last_was_space = false;   
        }
    }
}

int main()
{
    ifstream in("in.txt");
    ofstream out("out.txt", ios::out);

    string str = "";
    int len = 0;

    while(!in.eof()) {
        char c;
        in >> resetiosflags(ios::skipws) >> c;
        str += c;
        len++;
    }

    string changed_str = replace_space_groups(str, 10);

    cout << changed_str;

    return 0;
}
