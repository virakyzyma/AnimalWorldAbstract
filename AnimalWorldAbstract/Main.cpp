#include <iostream>
using namespace std;


class Herbivore abstract
{
protected:
	bool life;
	int weight;
public:
	virtual void SetWeight() abstract;
	void SetLife(bool life) 
	{
		this->life = life;
	};
	bool GetLife() 
	{
		return life;
	}
	int GetWeight()
	{
		return weight;
	}
	void Eat_Grass() {
		weight += 10;
		std::cout << "Weight: " << weight << std::endl;
	}
};


class Bison : public Herbivore
{
public:
	void SetWeight() override
	{
		weight = rand() % (123 - 45) + 45;
	}
};

class Wildebeest : public Herbivore
{
public:
	void SetWeight() override
	{
		weight = rand() % (100 - 22) + 22;
	}
};

class Elk : public Herbivore
{
public:
	void SetWeight() override 
	{
		weight = rand() % (222 - 100) + 100;
	}
};

class Carnivore abstract
{
protected:
	int power;
public:
	virtual void SetPower() abstract;
	void Eat(Herbivore* animal) 
	{
		if (!animal->GetLife()) 
		{
			return;
		}
		if (power > animal->GetWeight()) 
		{
			power += 10;
			std::cout << "Power: " << power << std::endl;
			animal->SetLife(false);
		}
		else 
		{
			power -= 10;
			std::cout << "Power: " << power << std::endl;
		}
	}
};

class Wolf : public Carnivore
{
public:
	void SetPower() override
	{
		power = rand() % (1300 - 500) + 500;
	}
};

class Lion : public Carnivore
{
public:
	void SetPower() override 
	{
		power = rand() % (400 - 100) + 100;
	}
};

class Tiger : public Carnivore
{
public:
	void SetPower() override 
	{
		power = rand() % (800 - 300) + 300;
	}
};

class Continent abstract
{
public:
	virtual Herbivore* CreateHerbivoreAnimal() abstract;
	virtual Carnivore* CreateCarnivoreAnimal() abstract;
};

class North_America : public Continent
{
public:
	Herbivore* CreateHerbivoreAnimal() 
	{
		Herbivore* animal = new Bison();
		animal->SetWeight();
		animal->SetLife(true);
		return animal;
	}
	Carnivore* CreateCarnivoreAnimal() {
		Carnivore* animal = new Wolf();
		animal->SetPower();
		return animal;
	}
};


class Africa : public Continent
{
public:
	Herbivore* CreateHerbivoreAnimal()
	{
		Herbivore* animal = new Wildebeest();
		animal->SetWeight();
		animal->SetLife(true);
		return animal;
	}
	Carnivore* CreateCarnivoreAnimal()
	{
		Carnivore* animal = new Lion();
		animal->SetPower();
		return animal;
	}
};

class Eurasia : public Continent
{
public:
	Herbivore* CreateHerbivoreAnimal() 
	{
		Herbivore* animal = new Elk();
		animal->SetWeight();
		animal->SetLife(true);
		return animal;
	}
	Carnivore* CreateCarnivoreAnimal() 
	{
		Carnivore* animal = new Tiger();
		animal->SetPower();
		return animal;
	}
};

class Animal_World 
{
	Carnivore* carnivore[2];
	Herbivore* herbivore[2];
public:
	Animal_World(Continent* continent)
	{
		for (size_t i = 0; i < 2; i++)
		{
			herbivore[i] = continent->CreateHerbivoreAnimal();
			carnivore[i] = continent->CreateCarnivoreAnimal();
		}
	}
	void Meals_Herbivores()
	{
		for (size_t i = 0; i < 2; i++)
		{
			herbivore[i]->Eat_Grass();
		}
	}

	void Nutrition_Carnivores() 
	{
		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				carnivore[i]->Eat(herbivore[j]);
			}
		}
	}
};



int main()
{
	srand(time(0));
	Continent* Continent = new Africa();
	Animal_World* World = new Animal_World(Continent);
	cout << "Africa\n" << endl;
	World->Meals_Herbivores();
	World->Nutrition_Carnivores();
	delete Continent;
	delete World;

	cout << "\nNorth America\n";
	Continent = new North_America();
	World = new Animal_World(Continent);
	World->Meals_Herbivores();
	World->Nutrition_Carnivores();
	delete Continent;
	delete World;

	cout << "\nEurasia\n";
	Continent = new Eurasia();
	World = new Animal_World(Continent);
	World->Meals_Herbivores();
	World->Nutrition_Carnivores();
	delete Continent;
	delete World;

	return 0;
}