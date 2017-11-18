#include <iostream>
#include <cstdlib>
#include <utility>
#include <time.h>
#include <cstring>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdarg.h>
#include <algorithm>
#include <vector>


typedef enum
{
	home,
	work,
	mobile,
	other,
}type_t;

typedef struct
{
	char name[100] = { { NULL } };
	unsigned long numbers[10] = { { NULL } };
	type_t type[10];
	char adress_street[100] = { NULL };
	unsigned int adress_house = { NULL };
	unsigned int adress_kv = { NULL };
}pb_t;






pb_t* open(pb_t* phonebook, size_t* size)
{
	FILE* file1 = fopen("save", "rb");
	if (file1 == NULL)
	{
		return phonebook;
	}
	else
	{
		//FILE* file1 = fopen("save", "rb");
		fseek(file1, 0, SEEK_SET);
		fread(size, sizeof(size_t), 1, file1);
		pb_t* pb = (pb_t*)calloc(*size, sizeof(pb_t));
		fread(pb, sizeof(pb_t), *size, file1);

		fclose(file1);
		return pb;
	}
}

void save(pb_t* phonebook, size_t* size)
{
	FILE* file1 = fopen("save", "wb");
	fwrite(size, sizeof(size_t), 1, file1);	
	fwrite(phonebook, sizeof(pb_t), *size, file1);
	fclose(file1);
	//rename("save_temp", "save");
}

void t_o(type_t* t)
{
	if (*t == 0)
	{
		std::cout << "home";
		//return "home";
	}
	else if (*t == 1)
	{
		std::cout << "work";
	}
	else if (*t == 2)
	{
		std::cout << "mobile";
	}
	else if (*t == 3)
	{
		std::cout << "other";
	}
}

pb_t* add_contact(pb_t* phonebook1, size_t* size, unsigned long number)
{
	
	
	pb_t pb;
	
	//std::cout << number << '\n';

	int i2 = 0, t = -1, g2 = -1;
	std::cout << "Name: ";
	std::cin >> pb.name;
	while (i2 < 10)
	{
		if (number == 0)
		{
			std::cout << "Number: ";
			std::cin >> pb.numbers[i2];
		}
		else
		{
			pb.numbers[i2] = number;
			number = 0;
		}

		//std::cout << pb.numbers[0] << '\n';

		std::cout << "type, 1 - home, 2 - work, 3 - mobile, 4 - other: ";
		std::cin >> t;
		if (t == 1)
		{
			pb.type[i2] = home;
		}
		else if (t == 2)
		{
			pb.type[i2] = work;
		}
		else if (t == 3)
		{
			pb.type[i2] = mobile;
		}
		else if (t == 4)
		{
			pb.type[i2] = other;
		}
		std::cout << "1 - add other number, 0 - exit: ";
		std::cin >> g2;
		i2++;
		if (g2 == 0)
		{
			break;
		}	
	}
	std::cout << "adress, street: ";
	std::cin >> pb.adress_street;
	std::cout << "adress, house: ";
	std::cin >> pb.adress_house;
	std::cout << "adress, kv: ";
	std::cin >> pb.adress_kv;




	(*size)++;
	pb_t* phonebook = (pb_t*)calloc((*size), sizeof(pb_t));
	for (int i = 0; i < (*size)-1; i++)
	{
		phonebook[i] = phonebook1[i];
	}

	//memcpy(phonebook, phonebook1, *size);
	phonebook[(*size)-1] = pb;
	
	//std::cout << phonebook[(*size) - 1].name << '\n';
	//free(phonebook1);

	
	return phonebook;
}

pb_t* del_contact(pb_t* phonebook1, size_t* size, int ind)
{
	(*size)--;
	int i2 = 0;
	pb_t* phonebook = (pb_t*)calloc(*size, sizeof(pb_t));
	for (int i = 0; i <= *size; i++)
	{
		if (i != ind)
		{
			phonebook[i2] = phonebook1[i];
			i2++;
		}		
	}
	//free(phonebook1);
	
	return phonebook;
}

pb_t* edit_contact(pb_t* phonebook, size_t* size, int ind)
{
	int g = -1;

	std::cout << "1 - edit name, 2 - edit number, 3 - add number, 4 - delete number, 5 - edit adress: ";
	std::cin >> g;
	if (g == 1)
	{
		std::cout << "new name: ";
		std::cin >> phonebook[ind].name;		
	}
	else if (g == 2)
	{
		int n = -1, t = 0, c = 0;
		for (int i2 = 0; i2 < 10; i2++)
		{
			if (phonebook[ind].numbers[i2] != 0)
			{
				std::cout << i2 << " " << phonebook[ind].numbers[i2] << " ";
				t_o(phonebook[ind].type);
				std::cout << '\n';
				c++;
			}
		}
		std::cout << '\n';
		while (true)
		{
			std::cout << "number index: ";
			std::cin >> n;
			if (n >= c || n < 0)
			{
				std::cout << "invalid index" << '\n';
			}
			else
			{
				break;
			}
		}
		
		std::cout << "new number: ";
		std::cin >> phonebook[ind].numbers[n];
		std::cout << "type, 1 - home, 2 - work, 3 - mobile, 4 - other: ";
		std::cin >> t;
		if (t == 1)
		{
			phonebook[ind].type[n] = home;
		}
		else if (t == 2)
		{
			phonebook[ind].type[n] = work;
		}
		else if (t == 3)
		{
			phonebook[ind].type[n] = mobile;
		}
		else if (t == 4)
		{
			phonebook[ind].type[n] = other;
		}
	}
	else if (g == 3)
	{
		int t = -1;
		for (int i2 = 0; i2 < 10; i2++)
		{
			if (phonebook[ind].numbers[i2] == 0)
			{
				std::cout << "Number: ";
				std::cin >> phonebook[ind].numbers[i2];
				std::cout << "type, 1 - home, 2 - work, 3 - mobile, 4 - other: ";
				std::cin >> t;
				if (t == 1)
				{
					phonebook[ind].type[i2] = home;
				}
				else if (t == 2)
				{
					phonebook[ind].type[i2] = work;
				}
				else if (t == 3)
				{
					phonebook[ind].type[i2] = mobile;
				}
				else if (t == 4)
				{
					phonebook[ind].type[i2] = other;
				}
				break;
			}			
		}
	}
	else if (g == 4)
	{
		int n = 0, c = 0;
		for (int i2 = 0; i2 < 10; i2++)
		{
			if (phonebook[ind].numbers[i2] != 0)
			{
				std::cout << i2 << " " << phonebook[ind].numbers[i2] << " ";
				t_o(phonebook[ind].type);
				std::cout << '\n';
				c++;
			}
		}
		std::cout << '\n';
		while (true)
		{
			std::cout << "number index: ";
			std::cin >> n;
			if (n >= c || n < 0)
			{
				std::cout << "invalid index" << '\n';
			}
			else
			{
				break;
			}
		}
		
		phonebook[ind].numbers[n] = 0;
	}
	else if (g == 5)
	{
		std::cout << "adress, street: ";
		std::cin >> phonebook[ind].adress_street;
		std::cout << "adress, house: ";
		std::cin >> phonebook[ind].adress_house;
		std::cout << "adress, kv: ";
		std::cin >> phonebook[ind].adress_kv;
	}
	return phonebook;
}



pb_t* sorting(pb_t* phonebook, size_t size)
{
	while(true)
	{
		int p = 0;
		for (int i = 0; i < size-1; ++i)
		{
			if (strcmp(phonebook[i].name, phonebook[i + 1].name) > 0)
			{
				std::swap(phonebook[i].name, phonebook[i + 1].name);
				std::swap(phonebook[i].numbers, phonebook[i + 1].numbers);
				std::swap(phonebook[i].type, phonebook[i + 1].type);
				std::swap(phonebook[i].adress_street, phonebook[i + 1].adress_street);
				std::swap(phonebook[i].adress_house, phonebook[i + 1].adress_house);
				std::swap(phonebook[i].adress_kv, phonebook[i + 1].adress_kv);
				p++;
			}
		}
		if (p == 0)
		{
			break;
		}
	}
	return phonebook;
}

void neighbors(pb_t* phonebook, size_t* size, int ind, int n)
{
	unsigned int b = 0, l = 0, count = 0, c = 0;
	unsigned int* index = (unsigned int*)calloc(*size, sizeof(unsigned int));
	for (int i = 0; i < *size; i++)
	{
		if (strcmp(phonebook[ind].adress_street, phonebook[i].adress_street) == 0 && phonebook[ind].adress_house == phonebook[i].adress_house && phonebook[ind].adress_kv != phonebook[i].adress_kv)
		{
			index[c] = i;
			c++;
		}		
	}

	if (c == 0)
	{
		std::cout << "neighbors not found" << '\n';
		return;
	}

	b = phonebook[ind].adress_kv + 1;
	l = phonebook[ind].adress_kv - 1;
	
	while (count < n && count < c)
	{
		for (int i = 0; i < c; i++)
		{
			if (b == phonebook[index[i]].adress_kv)
			{
				std::cout << phonebook[index[i]].name << " " << phonebook[index[i]].adress_street << " " << phonebook[index[i]].adress_house << " kv - " << phonebook[index[i]].adress_kv << '\n';
				count++;
			}
			if (l == phonebook[index[i]].adress_kv)
			{
				std::cout << phonebook[index[i]].name << " " << phonebook[index[i]].adress_street << " " << phonebook[index[i]].adress_house << " kv - " << phonebook[index[i]].adress_kv << '\n';
				count++;
			}			
		}
		b++;
		l--;
	}
	std::cout << '\n';
}

pb_t* search(pb_t* phonebook, size_t* size)
{
	int g = -1, ind = -1, g2 = -1, cc = 0, n_c = 0;
	char name[100],street[100];
	unsigned long number = 0;
	unsigned int house = 0;
	std::cout << "1 - name, 2 - number, 3 - street, 4 - house, 5 - neighbors: ";
	std::cin >> g;
	if (g == 1)
	{
		int f_count = 0;
		std::cout << "name: ";
		std::cin >> name;
		for (int i = 0; i < *size; i++)
		{
			if (strcmp(phonebook[i].name, name) == 0)
			{
				std::cout << i << " " << phonebook[i].name << " ";
				f_count++;
				for (int i2 = 0; i2 < 10; i2++)
				{
					if (phonebook[i].numbers[i2] != 0)
					{
						std::cout << phonebook[i].numbers[i2] << " ";
						t_o(phonebook[i].type);
						std::cout << " ";
					}
				}
				std::cout << '\n';
			}
		}
		if (f_count == 0)
		{
			std::cout << "not found" << '\n';
		}
		else
		{
			std::cout << "index: ";
			std::cin >> ind;
			std::cout << "1 - Call, 2 - Delete, 3 - edit: ";
			std::cin >> g2;
			int ind2 = 0;
			for (int i2 = 0; i2 < 10; i2++)
			{
				if (phonebook[ind].numbers[i2] != 0)
				{
					cc++;
					ind2 = i2;
				}
			}

			if (g2 == 1)
			{
				int n = -1;
				if (cc == 1)
				{
					std::cout << "Calling " << phonebook[ind].name << " " << phonebook[ind].numbers[ind2] << '\n';
					std::cin >> n;
				}
				else if (cc > 1)
				{
					for (int i2 = 0; i2 < 10; i2++)
					{
						if (phonebook[ind].numbers[i2] != 0)
						{
							std::cout << i2 << " " << phonebook[ind].numbers[i2] << '\n';
						}
					}
					std::cout << "number index: ";
					std::cin >> n;
					std::cout << "Calling " << phonebook[ind].name << " " << phonebook[ind].numbers[n] << '\n';
					std::cin >> n;
				}
			}
			else if (g2 == 2)
			{
				phonebook = del_contact(phonebook, size, ind);
			}
			else if (g2 == 3)
			{
				phonebook = edit_contact(phonebook, size, ind);
			}
		}	
	}
	else if (g == 2)
	{
		int ind2 = 0, f_count = 0;
		std::cout << "number: ";
		std::cin >> number;
		for (int i = 0; i < *size; i++)
		{
			for (int i2 = 0; i2 < 10; i2++)
			{
				if (number == phonebook[i].numbers[i2])
				{
					std::wcout << phonebook[i].name << " ";
					std::cout << phonebook[i].numbers[i2] << " ";
					t_o(phonebook[i].type);
					std::cout << " ";
					ind = i;
					ind2 = i2;
					f_count++;
					break;
				}
			}	
		}
		if (f_count == 0)
		{
			std::wcout << "not found" << '\n';
		}
		else
		{
			std::cout << '\n';
			std::cout << "1 - Call, 2 - Delete, 3 - edit: ";
			std::cin >> g2;
			if (g2 == 1)
			{
				int n = 0;
				std::cout << "Calling " << phonebook[ind].name << " " << phonebook[ind].numbers[ind2] << '\n';
				std::cin >> n;
			}
		}	
	}
	else if (g == 3)
	{
		std::cout << "street: ";
		std::cin >> street;
		for (int i = 0; i < *size; i++)
		{
			if (strcmp(phonebook[i].adress_street , street)==0)
			{
				std::cout << phonebook[i].name << ", " << phonebook[i].adress_street << " " << phonebook[i].adress_house << " kv - " << phonebook[i].adress_kv << '\n';
			}
		}
	}
	else if (g == 4)
	{
		std::cout << "street: ";
		std::cin >> street;
		std::cout << "house: ";
		std::cin >> house;
		for (int i = 0; i < *size; i++)
		{
			if (strcmp(phonebook[i].adress_street, street) == 0 && phonebook[i].adress_house == house)
			{
				std::cout << phonebook[i].name << ", " << phonebook[i].adress_street << " " << phonebook[i].adress_house << " kv - " << phonebook[i].adress_kv << '\n';
			}
		}
	}
	else if (g == 5)
	{
		for (int i = 0; i < *size; i++)
		{
			std::cout << i << " " << phonebook[i].name << ", " << phonebook[i].adress_street << " " << phonebook[i].adress_house << " kv - " << phonebook[i].adress_kv << '\n';
		}
		while (true)
		{
			std::cout << "index: ";
			std::cin >> ind;
			if (ind >= *size || ind < 0)
			{
				std::cout << "invalid index" << '\n';
			}
			else
			{
				break;
			}
		}
		
		std::cout << "count of neighbors: ";
		std::cin >> n_c;
		neighbors(phonebook, size, ind, n_c);
	}
	return phonebook;
}

pb_t* call(pb_t* phonebook, size_t* size)
{
	int flag1 = 0;
	unsigned long number = 0;
	std::cout << "enter number: ";
	std::cin >> number;
	for (int i = 0; i < *size; i++)
	{
		for (int i2 = 0; i2 < 10; i2++)
		{
			if (phonebook[i].numbers[i2] == number)
			{
				std::cout << "Calling " << phonebook[i].name << " " << number << '\n';
				t_o(phonebook[i].type);
				flag1 = 1;
				break;
			}
		}
	}
	if (flag1 != 1)
	{
		int g2 = -1;
		std::cout << "Calling " << number << '\n';
		std::cin >> flag1;
		flag1 = 0;
		std::cout << "1 - Add number to phonebook, 0 - not add";
		std::cin >> g2;
		if (g2 == 1)
		{
			phonebook = add_contact(phonebook, size, number);
		}
	}
	return phonebook;
}


pb_t* contacts(pb_t* phonebook, size_t* size)
{
	if (*size == 0)
	{
		return phonebook;
	}
	int g2 = -1, cc = 0, n = -1;
	unsigned int ind = 0;
	phonebook = sorting(phonebook, *size);
	for (int i = 0; i < *size; i++)
	{
		if (phonebook[i].name[0] != 0)
		{
			std::cout << i << " " << phonebook[i].name << " ";
			for (int i2 = 0; i2 < 10; i2++)
			{
				if (phonebook[i].numbers[i2] != 0)
				{
					std::cout << phonebook[i].numbers[i2] << " ";
					t_o(phonebook[i].type);
					std::cout << " ";
				}
			}
			std::cout << '\n';
		}
	}
	while (true)
	{
		std::cout << "index: ";
		std::cin >> ind;
		if (ind > (*size)-1  || ind < 0)
		{
			std::cout << "invalid index" << '\n';
		}
		else
		{
			break;
		}
	}
	
	std::cout << "1 - Call, 2 - Delete, 3 - edit: ";
	std::cin >> g2;
	int ind2 = 0;
	for (int i2 = 0; i2 < 10; i2++)
	{
		if (phonebook[ind].numbers[i2] != 0)
		{
			cc++;
			ind2 = i2;
		}
	}

	if (g2 == 1)
	{
		if (cc == 1)
		{
			std::cout << "Calling " << phonebook[ind].name << " " << phonebook[ind].numbers[ind2] << '\n';
			std::cin >> n;
		}
		else if (cc > 1)
		{
			for (int i2 = 0; i2 < 10; i2++)
			{
				if (phonebook[ind].numbers[i2] != 0)
				{
					std::cout << i2 << " " << phonebook[ind].numbers[i2] << '\n';
				}
			}
			while (true)
			{
				std::cout << "number index: ";
				std::cin >> n;
				if (n >= cc || n < 0)
				{
					std::cout << "invalid index" << '\n';
				}
				else
				{
					std::cout << "Calling " << phonebook[ind].name << " " << phonebook[ind].numbers[n] << '\n';
					std::cin >> n;
					break;
				}
			}	
		}
	}

	else if (g2 == 2)
	{
		phonebook = del_contact(phonebook, size, ind);
	}
	else if (g2 == 3)
	{
		phonebook = edit_contact(phonebook, size, ind);
	}
	return phonebook;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	int g = -1;
	size_t size = 0;
	
	pb_t pb;
	pb_t* phonebook = &pb;// = (pb_t*)calloc(size, sizeof(pb_t));
	

	phonebook = open(phonebook, &size);

	while (true)
	{
		save(phonebook, &size);
		std::cout << "1 - Contacts, 2 - Add contact, 3 - Call, 4 - search, 0 - exit: ";
		std::cin >> g;

		if (g == 1)
		{
			phonebook = contacts(phonebook, &size);
		}

		else if (g == 2)
		{
			phonebook = add_contact(phonebook, &size, 0);
		}
		else if (g == 3)
		{
			phonebook = call(phonebook, &size);
		}

		else if (g == 4)
		{
			phonebook = search(phonebook, &size);
		}

		else if (g == 0)
		{
			break;
		}
	}




	//system("pause");
	return 0;
}