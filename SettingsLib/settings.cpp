#include "settings.h"

settings::settings(std::string const & filename)   {
    this->filename = filename;
    this->reload();
}

void settings::reload() {
    char *chr = new char[this->filename.length() + 1];
    strcpy(chr, this->filename.c_str());
    this->stored.clear();
    string str0, str1;
    std::ifstream input(chr);
    while (getline(input, str0)) {
        getline(input, str1);
        this->stored[str0] = str1;
    };
    input.close();
};

string const & settings::get(std::string const & name, std::string const & def) const {
    if(stored.find(name) != stored.end())  {
        return stored.find(name)->second;
    }
    else  {
        return def;
    };
}

void settings::set(std::string const & name, std::string const & value)  {
    this->stored[name] = value;
    char* chr = new char[filename.length() + 1];
    strcpy(chr, filename.c_str());
    std::ofstream output(chr);
    map <string, string> ::iterator i;
    for (i = stored.begin(); i != stored.end(); i++) {
        output << (*i).first << endl;
        output << (*i).second << endl;
    }
    output.close();
}

void settings::reset() {
    char *chr = new char[filename.length() + 1];
    strcpy(chr, filename.c_str());
    ofstream(chr, std::ofstream::trunc);
    stored.clear();
}

settings::param::param(const string & name, std::string value, const settings *parent) {
    this->value = value;
    this->name = name;
    this->parent = const_cast<settings* const>(parent);
}

settings::param::operator std::string() const {
    return string(value);
}

settings::param::operator bool() const {
    return (value == "true");
}

settings::param::operator int() const {
    return atoi(value.c_str());
}

settings::param::operator double() const {
    double z = ::atof(value.c_str());
    return z;
}

settings::param & settings::param::operator = (char const * value) {
    return this->operator=(std::string(value));
}

settings::param & settings::param::operator = (std::string const & value) {
    this->value = value;
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator = (int value) {
    stringstream stst;
    stst << value;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator = (bool value) {
    ostringstream stst;
    stst << boolalpha << value;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator = (double value) {
    ostringstream stst;
    stst << value;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator += (std::string const & value) {
    this->value += value;
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator += (int value) {
    stringstream stst;
    int dem = atoi(this->value.c_str()) + value;
    stst << dem;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator += (double value) {
    double zz = ::atof(this->value.c_str());
    zz = zz + value;
    ostringstream stst;
    stst << zz;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator -= (int value) {
    stringstream stst;
    int dem = atoi(this->value.c_str()) - value;
    stst << dem;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator -= (double value) {
    double zz = ::atof(this->value.c_str());
    zz = zz - value;
    ostringstream stst;
    stst << zz;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator *= (int value) {
    stringstream stst;
    int dem = atoi(this->value.c_str()) * value;
    stst << dem;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator *= (double value) {
    double zz = ::atof(this->value.c_str());
    zz = zz * value;
    ostringstream stst;
    stst << zz;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator /= (int value) {
    stringstream stst;
    int dem = atoi(this->value.c_str()) / value;
    stst << dem;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator /= (double value) {
    double zz = ::atof(this->value.c_str());
    zz = zz / value;
    ostringstream stst;
    stst << zz;
    this->value = stst.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator|=(bool value) {
    if(value){
        this->value="true";
    };
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator&=(bool value) {
    if(!value){
        this->value="false";
    };
    parent->set(this->name, this->value);
    return *this;
}

bool settings::param::is_empty() const {
    return this->value.empty();
}

const settings::param settings::operator[](std::string const &name) const {
    return param(name, stored.find(name)->second, this);
}

settings::param settings::operator[](std::string const & name) {
    return param(name, stored.find(name)->second, this);
}

int main(int argc, char* argv[]) {
    //settings* a = new settings("what.the");
    //a->reload();
    //cout << a->get("three");
    return 0;
}

