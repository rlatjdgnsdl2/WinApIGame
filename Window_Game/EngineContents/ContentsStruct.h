#pragma once



struct Room {
	int x, y, width, height;
	bool isValid() const {
		return width > 0 && height > 0;
	}
};

struct Node {
	int x, y, width, height;
	Room room;
	Node* left = nullptr;
	Node* right = nullptr;
	bool isLeaf() const { return left == nullptr && right == nullptr; }

	~Node() {
		delete left;
		delete right;
	}
};


struct AnimInfo
{
	AnimInfo() {}
	AnimInfo(
		int _AttackAnimCount,
		int _HurtAnimCount,
		int _IdleAnimCount,
		int _WalkAnimCount) :
		AttackAnimCount(_AttackAnimCount),
		HurtAnimCount(_HurtAnimCount),
		IdleAnimCount(_IdleAnimCount),
		WalkAnimCount(_WalkAnimCount) {}
	int AttackAnimCount{};
	int HurtAnimCount{};
	int IdleAnimCount{};
	int WalkAnimCount{};
};

struct PokemonInfo
{
	PokemonInfo() {}
	PokemonInfo(
		unsigned int _Level,
		unsigned int _Hp,
		unsigned int _Attack,
		unsigned int _Defense,
		unsigned int _Special_Attack,
		unsigned int _Special_Defense,
		unsigned int _Speed,
		PokemonType _PokemonType) :
		Level(_Level),
		Hp(_Hp),
		Attack(_Attack),
		Defense(_Defense),
		Special_Attack(_Special_Attack),
		Special_Defense(_Special_Defense),
		Speed(_Speed),
		PokemonType(_PokemonType) {}
	unsigned int Level;
	unsigned int Hp;
	unsigned int Attack;
	unsigned int Defense;
	unsigned int Special_Attack;
	unsigned int Special_Defense;
	unsigned int Speed;
	PokemonType PokemonType;
};





struct DungeonInfo {
	std::vector<std::string> Pokemons_In_Dongeon;
};






