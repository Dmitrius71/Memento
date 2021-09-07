#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <vector> 

using namespace std;

class IMemento
{
public:
	virtual string GetName() = 0;
	virtual string Date() = 0;
	virtual string State() = 0;

};

class ConcretreMemento : public IMemento
{
	string state;
	string date;
public:
	ConcretreMemento(string state) : state{ state } {
		time_t now = time(0);
		date = ctime(&now);
	}

	string State()override
	{
		return this->state;
	}

	string Date() override
	{
		return this->date;
	}

	string GetName() override
	{
		return this->date + " | (" + this->state.substr(0, 9) + "..)";
	}
};


class Originator
{
	string state;
	string GenereteRandomString(int legth = 10)
	{
		const char alphanum[] = "0123456789ABCDEFGIKLMNOPQRSTUVWXYZabcdefgiklmnopqrstuvwxyz";
		string randstring = "";
		for (int i = 0; i < legth; i++)
		{
			randstring += alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		return randstring;
	}
public:
	Originator(string state) : state{ state }
	{
		cout << "Originator my origin stste = " << this->state << "\n";
	}

	void Method()
	{
		cout << "Originator doing something \n";
		this->state = this->GenereteRandomString(20);
		cout << "Originator current state = " << this->state << "\n";
	}

	IMemento* Save()
	{
		return new ConcretreMemento(this->state);
	}

	void Restore(IMemento* memento)
	{
		this->state = memento->State();
		cout << "Originator current restoring state = " << this->state << "\n";
	}

};

class Caretaker
{
	vector<IMemento*> mementos;
	Originator* originator;
public:
	Caretaker(Originator* originator) : originator{ originator } {}

	void Backup()
	{
		cout << "Carecker saving originator\n";
		this->mementos.push_back(this->originator->Save());
	}

	void Undo()
	{
		if (!this->mementos.size())
			return;
		IMemento* memento = this->mementos.back();
		this->mementos.pop_back();
		cout << "Cracker restoring originator to state = " << memento->GetName() << "\n";
		this->originator->Restore(memento);
	}


	void Showstory()
	{
		cout << "Caretaker list";
		for (IMemento* m : this->mementos)
			cout << m->GetName() << "\n";

	}
};




int main()
{
	srand(time(0));

	Originator* originator = new Originator("Begin state");
	Caretaker* caretaker = new Caretaker(originator);

	caretaker->Backup();
	originator->Method();
	caretaker->Backup();
	originator->Method();
	caretaker->Backup();
	originator->Method();
	caretaker->Backup();
	originator->Method();
	caretaker->Backup();
	originator->Method();

	cout << "\n";

	caretaker->Showstory();
	cout << "User go back! \n ";

	caretaker->Undo();
	caretaker->Showstory();

	cout << "User go back! \n ";

	caretaker->Undo();
	caretaker->Showstory();


	delete originator;
	delete caretaker;
	


	return 0;
}