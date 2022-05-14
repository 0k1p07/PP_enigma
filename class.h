#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

class Reflector
{
public:
	Reflector(int alphabet_size);
	~Reflector();
	void view(int alphabet_size);
	int letter_encode(int letter, int alphabet_size);

private:
	int* pattern;
};


class Rotor
{
public:
	Rotor(int alphabet_size);
	Rotor(const Rotor* rotor, int kstep);
	~Rotor();
	void view(int alphabet_size);
	void move(int alphabet_size);
	bool is_notch(int mod, int alphabet_size);
	int letter_encode(int letter, int alphabet_size);
	int letter_decode(int letter, int alphabet_size);
	int step;

private:
	int* en_pattern;
	int* de_pattern;
	
	int notches_quantity;
	int* notches;
	bool is_copy;
};

class Enigma
{
public:
	Enigma(Rotor** rotors, Reflector** reflectors);
	~Enigma();
	void view(int alphabet_size);
	void rotors_move(int alphabet_size);
	int encrypt(int letter, int alphabet_size);

private:
	int e_rotors_quantity;
	Rotor** e_rotors;
	Reflector* e_reflector;
	bool is_1rotor_moved;
	bool is_2rotor_moved;
};

