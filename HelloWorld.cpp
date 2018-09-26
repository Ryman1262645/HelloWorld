#include <iostream>
using std::cout;
using std::endl;
//using namespace std; would make it so everything in the std library didnt need to be prefaced with std::
//as it is im only using cout and endl so im only calling those two

int returnint(int i)
{
    return i;
}


int main()
{
    cout <<"Hello World!"<< endl;
    cout <<"The answer to the universe is "<<returnint(42)<<"!"<<endl;
    return 0;
}


//I want to merge my branches