#include <iostream>

// Naive Singleton
class Singleton {
protected: 
    Singleton(std::string value): _value(value)
    {
    }
    
    std::string _value;
    static Singleton* singleton_;

public:
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;
    
    static Singleton *GetInstance(const std::string& value);
    
    std::string value() const{
        return _value;
    }
};

Singleton* Singleton::singleton_ = nullptr;

Singleton *Singleton::GetInstance(const std::string& value) {
    if (singleton_==nullptr) { 
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

int main() {
    
    Singleton* one = Singleton::GetInstance("FOO");
    Singleton* two = Singleton::GetInstance("BAR");
    
    std::cout << one->value() << " " << two->value() << std::endl;
    
    
}
