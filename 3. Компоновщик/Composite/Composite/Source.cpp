#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Component abstract
{
protected:
	string name;
	int price;
public: 
	Component(string name)
	{
		this->name = name;
	}
	Component(string name, int price)
	{
		this->name = name;
		this->price = price;
	}

	virtual  void Add(Component *c) abstract;
	virtual  void Remove(Component *c) abstract;
	virtual  void Display(int depth) abstract;
	virtual int GetPrice() {return price;}
};

class Composite : public Component
{
	vector<Component*> components;

public:
	Composite(string name):Component(name){	}

	void Add(Component * component) override
	{
		components.push_back(component);
	}
	void Remove(Component *component) override
	{
		auto iter = find(components.begin(), components.end(), component);
		components.erase(iter);
	}
	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << endl;

		for(Component *component : components)
		{
			component->Display(depth + 2);
		}
	}
	int GetPrice() override
	{
		int totalPrice = price;
		for (Component* component : components)
		{
			totalPrice += component->GetPrice();
		}
		return totalPrice;
	}
};

class Leaf : public Component
{
public:
	Leaf(string name, int price) : Component(name, price) {}

	void Add(Component *c) override
	{
		cout << "Cannot add to file\n";
	}
	void Remove(Component *c) override
	{
		cout << "Cannot remove from file\n";
	}
	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << endl;
	}
};

int main()
{
	Component* offices = new Composite("Offices");

	Component* reception = new Composite("Reception");
	reception->Add(new Leaf("Coffee table", 200));
	reception->Add(new Leaf("Soft sofa", 600));
	reception->Add(new Leaf("Secretary's desk", 500));
	offices->Add(reception);

	Component* auditorium1 = new Composite("Audience 1");
	auditorium1->Add(new Leaf("10 tables", 3000));
	auditorium1->Add(new Leaf("Board", 300));
	auditorium1->Add(new Leaf("Teacher's desk", 700));
	offices->Add(auditorium1);

	Component* auditorium2 = new Composite("Audience 2");
	auditorium2->Add(new Leaf("20 tables", 5000));
	auditorium2->Add(new Leaf("Board", 400));
	auditorium2->Add(new Leaf("Soft sofa", 400));
	offices->Add(auditorium2);

	Component* computerRoom = new Composite("Computer room");
	computerRoom->Add(new Leaf("10 computer desks", 100));
	computerRoom->Add(new Leaf("10 PC", 10000));
	computerRoom->Add(new Leaf("Board", 400));
	offices->Add(computerRoom);

	Component* diningRoom = new Composite("Dining room");
	diningRoom->Add(new Leaf("Coffee machine", 600));
	diningRoom->Add(new Leaf("Table", 100));
	diningRoom->Add(new Leaf("Refrigerator", 800));
	diningRoom->Add(new Leaf("Washbasin", 200));
	offices->Add(diningRoom);

	offices->Display(1);

	cout << "Total price: " << offices->GetPrice() << endl;

	delete offices;

	system("pause");
}