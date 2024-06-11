#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;

    int hash_function(string name)
    {
        // write your hash function here
        return name.length() % bucket_count;
    }

public:
    scope_table();
    scope_table(int bucket_count, int unique_id, scope_table *parent_scope);
    scope_table *get_parent_scope();
    int get_unique_id();
    symbol_info *lookup_in_scope(symbol_info* symbol);
    bool insert_in_scope(symbol_info* symbol);
    bool delete_from_scope(symbol_info* symbol);
    void print_scope_table(ofstream& outlog);
    ~scope_table();

    // you can add more methods if you need
};

scope_table::scope_table(){
    bucket_count = 0;
    unique_id= 0;
}
scope_table::scope_table(int bucket_count, int unique_id, scope_table *parent_scope) {
    this->bucket_count = bucket_count;
    this->unique_id = unique_id;
    this->parent_scope = parent_scope;
    table.resize(bucket_count);
}

scope_table* scope_table::get_parent_scope() {
    return parent_scope;
}

int scope_table::get_unique_id() {
    return unique_id;
}

symbol_info* scope_table::lookup_in_scope(symbol_info* symbol) {
    int index = hash_function(symbol->getname());
    for (symbol_info* sym : table[index]) {
        if (sym->getname() == symbol->getname()) {
            return sym;
        }
    }
    return nullptr;
}

bool scope_table::insert_in_scope(symbol_info* symbol) {
    if (lookup_in_scope(symbol) != nullptr) {
        return false; // Symbol already exists
    }
    int index = hash_function(symbol->getname());
    table[index].push_back(symbol);
    return true;
}

bool scope_table::delete_from_scope(symbol_info* symbol) { // this will bascially return false in case the symbol isn't found 
    int index = hash_function(symbol->getname());
    auto& symbols = table[index];
    for (auto it = symbols.begin(); it != symbols.end(); ++it) {
        if ((*it)->getname() == symbol->getname()) {
            symbols.erase(it);
            return true;
        }
    }
    return false; 
}
// complete the methods of scope_table class
void scope_table::print_scope_table(ofstream& outlog)
{
    outlog << "ScopeTable # "+ to_string(unique_id) << endl;

    //iterate through the current scope table and print the symbols and all relevant information
    for (int i = 0; i<bucket_count;++i){
        outlog << i << " -->";
        for (symbol_info* entry : table[i]){
            outlog << "< " << entry->getname() << " : " <<entry->get_type() << " >" << endl;
            outlog << "Variable" << endl;
            outlog << "Type: " << entry->get_type() << endl;
            outlog << endl;
        }

    }
}