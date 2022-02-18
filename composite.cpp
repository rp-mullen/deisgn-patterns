#include <iostream>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

// Component class defines the common operations between simple
// and complex objects of the composition.

class Component {
    protected:
    Component *parent_;
    
    public:
    virtual ~Component() {}
    void SetParent(Component *parent) {
        this->parent_ = parent;
    }
    Component *GetParent() const {
        return this->parent_;
    }
    
    virtual void Add(Component *component) {}
    virtual void Remove(Component *component) {}
    
    virtual bool IsComposite() const {
        return false;
    }
    
    virtual std::string Operation() const = 0;
};

class Leaf : public Component {
    public:
    std::string Operation() const override {
        return "Leaf";
    }
};

class Composite : public Component {
    protected:
    std::list<Component *> children_;
    
    public:
    void Add(Component *component) override {
        children_.remove(component);
        component->SetParent(nullptr);
    }
    bool IsComposite() const override {
        return true;
    }
    
    // traverse the object tree performing operation on all children
    std::string Operation() const override {
        std::string result;
        for (const Component *c : children_) {
            if (c == children_.back()) {
                result += c->Operation();
            } else {
                result += c->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};

void Client(Component *component) {
    std::cout << component->Operation();
}

void Client2(Component *component1, Component *component2) {
    if (component1->IsComposite()) {
        component1->Add(component2);
    }
    std::cout << "RESULT: " << component1->Operation();
}

// Client functions
void Client(Component *component);
void Client2(Component *component1, Component *component2);


int main()
{
    Component *simple = new Leaf;
    std::cout << "Client: Simple Component:\n";
    Client(simple);
    std::cout << "\n\n";
    
    //complex Composite
    Component *tree = new Composite;
    Component *branch1 = new Composite;
    
    Component *leaf1 = new Leaf;
    Component *leaf2 = new Leaf;
    Component *leaf3 = new Leaf;
    
    branch1->Add(leaf1);
    branch1->Add(leaf2);
    
    Component *branch2 = new Composite;
    branch2->Add(leaf3);
    
    tree->Add(branch1);
    tree->Add(branch2);
    
    std::cout << "Client: Initialized Composite tree:\n";
    Client(tree);
    std::cout << "\n\n";
    
    std::cout << "Client: Don't need to check the components' classes even when managing the tree!";
    Client2(tree,simple);
    std::cout << "\n";
    
    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf1;
    delete leaf2;
    delete leaf3;
    
    return 0;
}
