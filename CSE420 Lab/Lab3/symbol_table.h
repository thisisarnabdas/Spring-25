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
    void enter_scope(){
        scope_table* new_scope = new  scope_table(bucket_count, current_scope_id++,  current_scope);
    }
    void exit_scope(){
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