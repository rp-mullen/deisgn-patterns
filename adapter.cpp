#include <iostream>
#include <algorithm>

class Target {
    public:
    virtual ~Target() = default;
    
    virtual std::string Request() const {
        return "Target: The default target's behavior";
    }
};

// Adaptee has its own behavior but its interface is not
// compatible with the client code and needs to be adapted
class Adaptee {
  public:
  std::string SpecificRequest() const {
      return ".eetpadA eht fo roivaheb laicepS";
  }
};

// Adapter makes Adaptee's interface compatible with Target's
// interface
class Adapter : public Target {
  private:
  Adaptee *adaptee_;
  
  public:
  Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
  std::string Request() const override {
      std::string to_reverse = this->adaptee_->SpecificRequest();
      std::reverse(to_reverse.begin(), to_reverse.end());
      return "Adapter: (TRANSLATED) " + to_reverse;
  }
};

void Client(const Target *target) {
    std::cout << target->Request();
}


int main()
{
    std::cout << "Client: I can work just fine with target objectives";
    Target *target = new Target;
    Client(target);
    std::cout << "\n\n";
    
    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The adaptee class:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: I can work with it via the Adapter: ";
    Adapter *adapter = new Adapter(adaptee);
    Client(adapter);
    std::cout << "\n";
    
    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}
