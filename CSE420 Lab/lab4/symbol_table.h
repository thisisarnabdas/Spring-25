#include "scope_table.h"

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket_count){
        this->bucket_count = bucket_count;
        this->current_scope = nullptr;
        this->current_scope_id = 0;
    }
    ~symbol_table();
    void enter_scope(ofstream& outlog){
        scope_table *new_scope = new  scope_table(bucket_count, current_scope_id++,  current_scope);
        //cout << "New ScopeTable with ID"<< current_scope->get_unique_id()<<" created"<<endl;
        outlog<<"New ScopeTable with ID"<< current_scope->get_unique_id()<<" created"<<endl;
    }
    void exit_scope(ofstream& outlog){
        if (current_scope == nullptr){
            return;
        }
        cout << "ScopeTable with ID"<< current_scope->get_unique_id()<<" removed"<<endl;
        scope_table* parent_scope = current_scope->get_parent_scope();
        delete current_scope;
        current_scope = parent_scope;   
    }
    bool insert(symbol_info* symbol) {
        if (current_scope == nullptr) {
            return false;
        }
        return current_scope->insert_in_scope(symbol);
    }
    symbol_info* lookup(symbol_info* symbol) {
        scope_table* scope = current_scope;
        while (scope != nullptr) {
            symbol_info* found_symbol = scope->lookup_in_scope(symbol);
            if (found_symbol != nullptr) {
                return found_symbol;
            }
            scope = scope->get_parent_scope();
        }
        return nullptr;
    }
    void print_current_scope(ofstream& outlog){
        if (current_scope == nullptr) {
            return;
        }
        outlog << "################################" << endl << endl;
        current_scope->print_scope_table(outlog);
        outlog << "################################" << endl << endl;
    }
    void print_all_scopes(ofstream& outlog){
        outlog<<"################################"<<endl<<endl;
        scope_table *temp = current_scope;
        while (temp != NULL)
        {
            temp->print_scope_table(outlog);
            temp = temp->get_parent_scope();
        }
        outlog<<"################################"<<endl<<endl;
    }

    // you can add more methods if you need 
    bool insert_function(const string& name, const string& returnType) {
        if (symbols.find(name) != symbols.end()) {
            cout << "Error: Function " << name << " already exists in the current scope." << endl;
            return false;
        } else {
            symbol_info funcSymbol;
            funcSymbol.name = name;
            funcSymbol.type = returnType;
            // Insert the function symbol into the table
            symbols[name] = funcSymbol;
            return true;
        }
    }

    // Function to insert a parameter symbol into the scope table
    bool insert_parameter(const string& funcName, const string& paramName, const string& paramType) {
        // Check if the function exists in the scope table
        auto it = symbols.find(funcName);
        if (it == symbols.end()) {
            cout << "Error: Function " << funcName << " not found in the current scope." << endl;
            return false;
        } else {
            // Check if the parameter already exists in the function's parameters
            if (it->second.parameters.find(paramName) != it->second.parameters.end()) {
                cout << "Error: Parameter " << paramName << " already exists in function " << funcName << "." << endl;
                return false;
            } else {
                // Insert the parameter into the function's parameters
                symbol_info paramSymbol;
                paramSymbol.name = paramName;
                paramSymbol.type = paramType;
                // Insert the parameter symbol into the function's parameters
                it->second.parameters[paramName] = paramSymbol;
                return true;
            }
        }
    }
    void insert_variable(const std::string& name, const std::string& type) {
        // Check if the variable already exists in the symbol table
        if (table.find(name) != table.end()) {
            std::cout << "Variable '" << name << "' already exists in the symbol table." << std::endl;
            return;
        }

        // Create a new symbol_info object and insert it into the table
        symbol_info* new_symbol = new symbol_info(name, type);
        table[name] = new_symbol;
    }
};

// complete the methods of symbol_table class


// void symbol_table::print_all_scopes(ofstream& outlog)
// {
//     outlog<<"################################"<<endl<<endl;
//     scope_table *temp = current_scope;
//     while (temp != NULL)
//     {
//         temp->print_scope_table(outlog);
//         temp = temp->get_parent_scope();
//     }
//     outlog<<"################################"<<endl<<endl;
// }