#include <iostream>
#include <typeinfo>

class Context;

// Abstract state 
class State {
  protected:
  Context *_context;
  
  public:
  virtual ~State() {
  }
  
  void set_context(Context *context) {
      this->_context = context;
  }
  
  virtual void Handle1() = 0;
  virtual void Handle2() = 0;
  
  
};

class Context {
  private:
  State *state_;
  
  public:
  Context(State *state) : state_(nullptr) {
      this->TransitionTo(state);
  }
  
  ~Context() {
      delete state_;
  }
  
  void TransitionTo(State *state) {
      std::cout << "Context: Transition To " << typeid(*state).name() << ".\n";
      // delete the current state
      if (this->state_ != nullptr) {
          delete this->state_;
      }
      // switch to new state
      this->state_ = state;
      this->state_->set_context(this);
  }
  
  void Request1() {
      this->state_->Handle1();
  }
  
  void Request2() {
      this->state_->Handle2();
  }
};


class ConcreteStateA : public State {
  void Handle1() override;
  
  void Handle2() override {
      std::cout << "ConcreteStateA handles Request2.\n";
  }
};

class ConcreteStateB : public State {
    void Handle1() override {
        std::cout << "ConcreteStateB handles Request1.\n";
    }
    
    void Handle2() override {
        std::cout << "ConcreteStateB handles Request2.\n";
        std::cout << "ConcreteStateB wants to change the state of the context.\n";
        this->_context->TransitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::Handle1() {
  {
    std::cout << "ConcreteStateA handles request1.\n";
    std::cout << "ConcreteStateA wants to change the state of the context.\n";

    this->_context->TransitionTo(new ConcreteStateB);
  }
}

void Client() {
  Context *context = new Context(new ConcreteStateA);
  context->Request1();
  context->Request2();
  delete context;
}

int main()
{
    Client();
    return 0;
}
