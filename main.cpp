#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "class.h"

Rotor** rotors_initiation(int* rotors_quantity);
Reflector** reflectors_initiation(int* reflectors_quantity);
void deinitiation(Rotor** rotors, int rotors_quantity, Reflector** reflectors, int reflectors_quantity);
void test_view(Rotor** rotors, int rotors_quantity, Reflector** reflectors, int reflectors_quantity);

int ALPHABET_SIZE;

int main()
{
	scanf("%i", &ALPHABET_SIZE);

	int rotors_quantity;
	Rotor** rotors = rotors_initiation(&rotors_quantity);

	int reflectors_quantity;
	Reflector** reflectors = reflectors_initiation(&reflectors_quantity);

	//test_view(rotors, rotors_quantity, reflectors, reflectors_quantity);

	int messeges_quantity;
	scanf("%i", &messeges_quantity);
	for (int i = 0; i < messeges_quantity; i++)
	{
		Enigma enigma(rotors, reflectors);
		enigma.view(ALPHABET_SIZE);
		int letter;
		scanf("%i", &letter);
		while (letter != 0)
		{
			int encrypted_letter = enigma.encrypt(letter, ALPHABET_SIZE);
			printf("%i ", encrypted_letter);
			scanf("%i", &letter);
		}
		printf("\n");
	}

	deinitiation(rotors, rotors_quantity, reflectors, reflectors_quantity);


	return 0;
}

Rotor** rotors_initiation(int* rotors_quantity)
{

	scanf("%i", rotors_quantity);
	Rotor** rotors = new Rotor * [*rotors_quantity];

	for (int i = 0; i < *rotors_quantity; i++)
	{
		rotors[i] = new Rotor(ALPHABET_SIZE);
	}

	return rotors;
}

Reflector** reflectors_initiation(int* reflectors_quantity)
{
	scanf("%i", reflectors_quantity);
	Reflector** reflectors = new Reflector * [*reflectors_quantity];
	for (int i = 0; i < *reflectors_quantity; i++)
	{
		reflectors[i] = new Reflector(ALPHABET_SIZE);
	}
	return reflectors;
}

void deinitiation(Rotor** rotors, int rotors_quantity, Reflector** reflectors, int reflectors_quantity)
{
	for (int i = 0; i < reflectors_quantity; i++)
	{
		delete reflectors[i];
	}
	delete[] reflectors;

	for (int i = 0; i < rotors_quantity; i++)
	{
		delete rotors[i];
	}
	delete[] rotors;
}

void test_view(Rotor** rotors, int rotors_quantity, Reflector** reflectors, int reflectors_quantity)
{
	for (int i = 0; i < rotors_quantity; i++)
	{
		printf("\nRotor %i:", i);
		rotors[i]->view(ALPHABET_SIZE);
	}
	for (int i = 0; i < reflectors_quantity; i++)
	{
		printf("\nReflector %i:", i);
		reflectors[i]->view(ALPHABET_SIZE);
	}
}