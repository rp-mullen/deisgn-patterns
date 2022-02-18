#include <iostream>
#include <ctime>
#include <vector>

// Client function
void Client();

// Memento (Interface)
class Memento {
    public:
    virtual std::string GetName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
};

class MementoConcrete : public Memento {
    private:
    std::string state_;
    std::string date_;
    
    public:
    MementoConcrete(std::string state) : state_(state) {
        this->state_ = state;
        std::time_t now = std::time(0);
        this->date_ = std::ctime(&now);
    }
    
    std::string state() const override {
        return this->state_;
    }
    
    std::string date() const override {
        return this->date_;
    }
    
    std::string GetName() const override {
        return this->date_;
    }
};

// Originator
class Originator {
    private:
    std::string state_;
    
    std::string GenerateRandomState(int length = 10) {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRXTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;
        
        std::string random_string;
        for (int i = 0; i < length; i++) {
            random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }

    
    public:
    Originator(std::string state) : state_(state) {
        std::cout << "Originator: Initial state is: " << this->state_ << std::endl;
    }
    
    void DoSomething() {
        // generate state
        std::cout << "Changing state...\n";
        this->state_ = this->GenerateRandomState(30);
        std::cout << "State has changed to: " << this->state_ << std::endl;
    }
    
    // save current state to memento
    Memento *Save() {
        return new MementoConcrete(this->state_);
    }
    
    // restore originator's state from memento object
    void Restore(Memento *memento) {
        this->state_ = memento->state();
        std::cout << "Originator: State has changed to: " << this->state_ << std::endl;
    }    
};

/* Caretaker class doesn't depend on concrete implementation of the 
   Memento class, thus can't access the originator's state. 
   Works with all mementos via base Memento interface.
*/
class Caretaker {
    private:
    std::vector<Memento *> mementos_;
    Originator *originator_;
    
    public:
    Caretaker(Originator *originator) : originator_(originator) {
        this->originator_ = originator;
    }
    
    void Backup() {
        std::cout << "\nCaretaker: Saving Originator's state...\n";
        this->mementos_.push_back(this->originator_->Save());
    }
    void Undo() {
        if (!this->mementos_.size()) {
            return;
        }
        Memento *memento = this->mementos_.back();
        this->mementos_.pop_back();
        std::cout << "Caretaker: Restoring state to: " << memento->GetName() << std::endl;
        try {
            this->originator_->Restore(memento);
        } catch (...) {
            this->Undo();
        }
    }
    
    void ShowHistory() const {
        std::cout << "Caretaker: Here's the list of mementos:\n";
        for (Memento *memento : this->mementos_) {
            std::cout << memento->GetName() << std::endl;
        }
    }
};

void Client() {
    Originator *originator = new Originator("Initialized.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    std::cout << "\n";
    caretaker->ShowHistory();
    std::cout << "Roll Back...\n";
    caretaker->Undo();
    std::cout << "One more time...\n";
    caretaker->Undo();
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Client();
    return 0;
}
