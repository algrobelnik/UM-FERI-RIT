#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    vector<char> v;
    v.push_back('a');
    v.push_back('e');
    v.push_back('c');
    v.push_back('g');

    string s = "geslo";

    vector<char>::iterator pos;

    pos = search(s.begin(),s.end(),v.begin(),v.end());

    if (pos != s.end())
    {
        cout << "found" << endl;
    }

    return 0;
}