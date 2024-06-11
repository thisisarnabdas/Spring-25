#include<bits/stdc++.h>
using namespace std;

class symbol_info
{
private:
    string name;
    string type;

    // Write necessary attributes to store what type of symbol it is (variable/array/function)
    string symbol_type;
    // Write necessary attributes to store the type/return type of the symbol (int/float/void/...)
    string return_type;
    // Write necessary attributes to store the parameters of a function
    vector <string> parameters;
    // Write necessary attributes to store the array size if the symbol is an array
    int array_size;
public:
    symbol_info(string name, string type)
    {
        this->name = name;
        this->type = type;
    }
    string getname()
    {
        return name;
    }
    string get_type()
    {
        return type;
    }
    string get_symbol_type()
    {
        return symbol_type;
    }
    string get_return_type()
    {
        return return_type;
    }
    const vector <string> &get_parameters()
    {
        return parameters;
    }
    int get_array_size()
    {
        return array_size;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    void set_type(string type)
    {
        this->type = type;
    }
    // Write necessary functions to set and get the attributes
    void  set_symbol_type(string symbol_type){
        this->symbol_type = symbol_type;
    }
    void set_return_type(string return_type){
        this->return_type = return_type;
    }
    void set_parameters(vector<string>& parameters){
        this->parameters=parameters;
    }
    void set_array_size(int array_size){
        this->array_size = array_size;
    }
    ~symbol_info()
    {
        // Write necessary code to deallocate memory, if necessary
    }
};