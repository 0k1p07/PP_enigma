#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "class.h"
#include <string.h>


//#####################################################
//##############Reflector functions####################
//#####################################################
Reflector::Reflector(int alphabet_size)
{
	pattern = new int[alphabet_size];
	for (int i = 0; i < alphabet_size; i++)
	{
		int tmp;
		scanf("%i", &tmp);
		pattern[i] = tmp - (i + 1);
	}
}

Reflector::~Reflector()
{
	delete pattern;
}

void Reflector::view(int alphabet_size)
{
	for (int i = 0; i < alphabet_size; i++)
	{
		printf("%i ", pattern[i]);
	}
	printf("\n");
}

int Reflector::letter_encode(int letter, int alphabet_size)
{
	int encode = letter + pattern[letter - 1];
	if (encode == 0)
	{
		encode = alphabet_size;
	}
	return encode;
}

//#####################################################
//##################Rotor functions####################
//#####################################################
Rotor::Rotor(const Rotor* rotor, int kstep)
{
	en_pattern = rotor->en_pattern;
	de_pattern = rotor->de_pattern;
	step = kstep;
	notches_quantity = rotor->notches_quantity;
	notches = rotor->notches;
	is_copy = true;
}

Rotor::Rotor(int alphabet_size)
{
	en_pattern = new int[alphabet_size];
	de_pattern = new int[alphabet_size];
	for (int i = 0; i < alphabet_size; i++)
	{
		int tmp;
		scanf("%i", &tmp);
		en_pattern[i] = tmp - (i + 1);
		de_pattern[tmp - 1] = i + 1 - tmp;
	}
	scanf("%i", &notches_quantity);
	if (notches_quantity > 0)
	{
		notches = new int[alphabet_size];
		memset(notches, 0, alphabet_size * sizeof(int));
		for (int i = 0; i < notches_quantity; i++)
		{
			int tmp;
			scanf("%i", &tmp);
			notches[tmp-1] = 1;
		}
	}
	else
	{
		notches = NULL;
	}
	step = 0;
	is_copy = false;
}

Rotor::~Rotor()
{
	if (is_copy == false)
	{
		delete en_pattern;
		delete de_pattern;
		delete notches;
	}
}

void Rotor::view(int alphabet_size)
{
	for (int i = 0; i < alphabet_size; i++)
	{
		printf("%i ", en_pattern[i]);
	}
	printf("\n");
	for (int i = 0; i < alphabet_size; i++)
	{
		printf("%i ", de_pattern[i]);
	}
	printf("\nN:");

	for (int i = 0; i < notches_quantity; i++)
	{
		printf("%i ", notches[i]);
	}
	printf(" S:%i\n", step);
}

void Rotor::move(int alphabet_size)
{
	step++;
	if (step == alphabet_size + 1)
	{
		step = 1;
	}
}
//mod - modificator, FE: to check next step, mod = 1, prev mod = -1 etc
bool Rotor::is_notch(int mod, int alphabet_size)
{
	if (notches_quantity > 0)
	{
		int spr = (step + mod);
		if (spr < 1)
		{
			spr += alphabet_size;
		}
		else if (spr > alphabet_size)
		{
			spr -= alphabet_size;
		}
		if (notches[spr-1]==1)
		{
			return true;
		}
	}
	return false;
}

int  Rotor::letter_encode(int letter, int alphabet_size)
{
	int index = letter + step - 1;
	if (index > alphabet_size)
	{
		index -= alphabet_size;
	}
	int encode = letter + en_pattern[index - 1];
	if (encode < 1)
	{
		encode += alphabet_size;
	}
	else if (encode > alphabet_size)
	{
		encode -= alphabet_size;
	}
	return encode;
}

int  Rotor::letter_decode(int letter, int alphabet_size)
{
	int index = letter + step - 1;
	if (index > alphabet_size)
	{
		index -= alphabet_size;
	}
	int decode = letter + de_pattern[index - 1];
	if (decode < 1)
	{
		decode += alphabet_size;
	}
	else if (decode > alphabet_size)
	{
		decode -= alphabet_size;
	}
	return decode;
}


//#####################################################
//##################Enigma functions###################
//#####################################################
Enigma::Enigma(Rotor** rotors, Reflector** reflectors)
{
	scanf("%i", &e_rotors_quantity);
	e_rotors = new Rotor * [e_rotors_quantity];
	for (int i = 0; i < e_rotors_quantity; i++)
	{
		int rotor_index, step;
		scanf("%i", &rotor_index);
		scanf("%i", &step);
		e_rotors[i] = new Rotor(rotors[rotor_index], step);
	}
	int reflector_index;
	scanf("%i", &reflector_index);
	e_reflector = reflectors[reflector_index];
	is_1rotor_moved = false;
	is_2rotor_moved = false;
}

Enigma::~Enigma()
{
	for (int i = 0; i < e_rotors_quantity; i++)
	{
		delete e_rotors[i];
	}

	delete[] e_rotors;
}

void Enigma::view(int alphabet_size)
{
	for (int i = 0; i < e_rotors_quantity; i++)
	{
		printf("\nE.Rotor %i:", i);
		e_rotors[i]->view(alphabet_size);
	}
	printf("\nE.reflector");
	e_reflector->view(alphabet_size);
}

void Enigma::rotors_move(int alphabet_size)
{
	bool double_step = false;
	e_rotors[0]->move(alphabet_size);
	if ((e_rotors_quantity > 2) && e_rotors[1]->is_notch(1, alphabet_size) && is_2rotor_moved == true)
	{
		e_rotors[2]->move(alphabet_size);
		e_rotors[1]->move(alphabet_size);
		double_step = true;
	}
	else if ((e_rotors_quantity > 1) && e_rotors[0]->is_notch(0, alphabet_size) &&  is_1rotor_moved == true && double_step == false)
	{
		e_rotors[1]->move(alphabet_size);
		is_2rotor_moved = true;
	}
	
	is_1rotor_moved = true;
}

int Enigma::encrypt(int letter, int alphabet_size)
{
	rotors_move(alphabet_size);
	int encrypt_letter = letter;
	printf("\nLetter: %i\n",letter);
	for (int i = 0; i < e_rotors_quantity; i++)
	{
		if (i < 3)
		{
			printf("Rotor nr : %i Postion : %i\n", (i + 1), (e_rotors[i]->step));
		}
		encrypt_letter = e_rotors[i]->letter_encode(encrypt_letter, alphabet_size);

	}

	encrypt_letter = e_reflector->letter_encode(encrypt_letter, alphabet_size);
	

	for (int i = e_rotors_quantity - 1; i >= 0; i--)
	{

		encrypt_letter = e_rotors[i]->letter_decode(encrypt_letter, alphabet_size);
		


	}
	return encrypt_letter;
}