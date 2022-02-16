#include <iostream>


// Abstract Product
class Product {
public:
  virtual ~Product() {};
  virtual std::string Operation() const = 0;
};

// Concrete Product #1
class ProductOne : public Product {
public:
    std::string Operation() const override {
        return "Product One Initialized";
    }
};

// Concrete Product #2 
class ProductTwo : public Product {
public:
    std::string Operation() const override {
        return "Product Two Initialized";
    }
};

// Abstract Creator Class
class Creator {
public:
    virtual ~Creator(){};
    virtual Product* FactoryMethod() const = 0;
    
    std::string SomeOperation() const {
        Product* product = this->FactoryMethod();
        
        std::string result = "From class Creator: " + product->Operation();
        delete product;
        return result;
    }
};

// Builds ProductOne
class CreatorOne : public Creator {
public:
    Product* FactoryMethod() const override {
        return new ProductOne();
    }
};

//Builds ProductTwo
class CreatorTwo : public Creator {
public:
    Product* FactoryMethod() const override {
        return new ProductTwo();
    }
};

// Client Code
void Client(const Creator& creator) {
    std::cout << "Independent of creator's class\n"
              << creator.SomeOperation() << std::endl;
}
void Client(const Creator& creator);


int main() {
    std::cout << "App: Launched with ProductOne.\n";
    Creator* creator1 = new CreatorOne();
    Client(*creator1);
    
    std::cout << std::endl;
    
    std::cout << "App: Launched with ProductTwo.\n";
    Creator* creator2 = new CreatorTwo();
    Client(*creator2);
    
    delete creator1;
    delete creator2;
    
    return 0;
    
}
