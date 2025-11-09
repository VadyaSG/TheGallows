#define NOMINMAX

#include<iostream>
#include<string>
#include<fstream>
#include<random>
#include<vector>
#include <limits>  
#include <Windows.h> 

void init_Ptp(int& letter_A, int& letter_B, char* word, std::string& hiden_Word);
void main_Game(int& score, std::string& progress, std::string& hiden_Word, char& letter_C, char* word, bool& found_letter_in_word);
void grafic_Render(int score);
bool restart_game();
int main()
{	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int letter_A{};
	int letter_B{};
	int score{};
	int game_Mode{};
	char letter_C{};
	bool found_letter_in_word{false};
	
	
	std::string hiden_Word{};
	std::string progress{};

	std::vector<std::string> words_from_file;

	std::ifstream file;

	int index;
	int index2;
	do
	{
		system("cls");
		char* word = nullptr;

		{
			score = 0;
			hiden_Word = "";
			progress = "";
			letter_A = 0;
			letter_B = 0;
			letter_C = '\0';
			found_letter_in_word = false;
			if (word != nullptr)
			{
				delete[] word;
				word = nullptr;
			}
			while (true)
			{
				std::cout << "Chouse the Game mode " << std::endl;
				std::cout << "1) Playing with the PC " << std::endl
					<< "2) Playing with friend" << std::endl;
				std::cout << "Number of game mode:";
				std::cin >> game_Mode;
				system("cls");

				if (std::cin.fail())
				{
					std::cout << "Error,enter the number!" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				}
				else if (game_Mode < 1 || game_Mode>2)
				{
					std::cout << "Enter 1 or 2!" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else
				{
					break;
				}
			}


		}

		system("cls");

		switch (game_Mode)
		{
		case 1:
			file.open("words.txt");
			if (!file.is_open()) {
				std::cerr << "can't open words.txt!" << std::endl;
				return 1;
			}
			while (file >> hiden_Word)
			{
				words_from_file.push_back(hiden_Word);
			}
			file.close();


			srand(time(0));
			index = rand() % words_from_file.size();
			hiden_Word = words_from_file[index];
			word = new char[hiden_Word.length() + 1] {};

			srand(time(0) - 1);
			index2 = rand() % words_from_file.size();

			init_Ptp(index, index2, word, hiden_Word);

			main_Game(score, progress, hiden_Word, letter_C, word, found_letter_in_word);

			break;
		case 2:
			std::cout << "Enter the word: ";
			std::cin >> hiden_Word;

			word = new char[hiden_Word.length() + 1] {};

			while (true)
			{


				std::cout << "Enter numbers of 2 letters you want to show:" << std::endl;
				std::cout << "letter A: ";
				std::cin >> letter_A;
				std::cout << "letter B: ";
				std::cin >> letter_B;
				system("cls");

				if (std::cin.fail())
				{
					std::cout << "Error,enter the number!" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else if (letter_A > hiden_Word.length() || letter_B > hiden_Word.length())
				{
					std::cout << "enter a number from 0 to " << hiden_Word.length() << std::endl;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else
				{
					break;
				}
			}

			system("cls");

			init_Ptp(letter_A, letter_B, word, hiden_Word);

			main_Game(score, progress, hiden_Word, letter_C, word, found_letter_in_word);

			break;
			
		}
		
	}
	while (restart_game());
	return 0;
}

void init_Ptp(int& letter_A, int& letter_B, char* word, std::string& hiden_Word)
{
	for (int i{ 0 }; i < hiden_Word.length(); ++i)
	{
		if (i == letter_A - 1 || i == letter_B - 1)
		{
			word[i] = hiden_Word[i];
		}
		else
		{
			word[i] = '_';
		}
	}
	word[hiden_Word.length()] = '\0';
	for (int i{ 0 }; i < hiden_Word.length(); ++i)
	{
		std::cout << word[i];
	}

}

void main_Game(int& score, std::string& progress, std::string& hiden_Word, char& letter_C, char* word,  bool& found_letter_in_word)
{
	
	while (score < 6 && progress != hiden_Word)
	{
		

		std::cout << std::endl;
		std::cout << score << "/ 6 Enter the letter:";
		std::cin >> letter_C;


		for (int i{ 0 }; i < hiden_Word.length(); ++i)
		{
			if (hiden_Word[i] == letter_C)
			{
				
				word[i] = letter_C;
				found_letter_in_word = true;
			}


		}

		if (found_letter_in_word)
		{

			std::cout << "Letter '" << letter_C << "' is in the word." << std::endl;
			found_letter_in_word = false;
		
		}
		else
		{
			std::cout << "Sorry, letter '" << letter_C << "' is not in the word." << std::endl;
			++score;
			
		}
		system("cls");
		progress = word;
		grafic_Render(score);
		std::cout << progress;

		
	}

	system("cls");

	if (hiden_Word == progress)
	{
		std::cout << "You are won!!!" << std::endl;

	}
	else
	{
		std::cout << "You are Dead!!!" << std::endl;
		grafic_Render(score);
		std::cout << "The word is: " << hiden_Word << std::endl;
	}

	delete[] word;
}

void grafic_Render(int score)
{
	const int arr_widh{ 10 };
	const int arr_heigh{ 10 };

	char dead_indicator_0[arr_widh][arr_heigh]
	{
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|','-','-','-','-','-','-',' ',' ',
' ','|',' ','/',' ',' ',' ','|',' ',' ',
' ','|','/',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',

	};
	char dead_indicator_1[arr_widh][arr_heigh]
	{
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|','-','-','-','-','-','-',' ',' ',
' ','|',' ','/',' ',' ',' ','|',' ',' ',
' ','|','/',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ','O',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',

	};
	char dead_indicator_2[arr_widh][arr_heigh]
	{
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|','-','-','-','-','-','-',' ',' ',
' ','|',' ','/',' ',' ',' ','|',' ',' ',
' ','|','/',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ','O',' ',' ',
' ','|',' ',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
	};
	char dead_indicator_3[arr_widh][arr_heigh]
	{
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|','-','-','-','-','-','-',' ',' ',
' ','|',' ','/',' ',' ',' ','|',' ',' ',
' ','|','/',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ','O',' ',' ',
' ','|',' ',' ',' ',' ',' ','|','\\',' ',
' ','|',' ',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',

	};
	char dead_indicator_4[arr_widh][arr_heigh]
	{
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|','-','-','-','-','-','-',' ',' ',
' ','|',' ','/',' ',' ',' ','|',' ',' ',
' ','|','/',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ','O',' ',' ',
' ','|',' ',' ',' ',' ','/','|','\\',' ',
' ','|',' ',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
	};
	char dead_indicator_5[arr_widh][arr_heigh]
	{
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|','-','-','-','-','-','-',' ',' ',
' ','|',' ','/',' ',' ',' ','|',' ',' ',
' ','|','/',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ','O',' ',' ',
' ','|',' ',' ',' ',' ','/','|','\\',' ',
' ','|',' ',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ','/',' ',' ',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
	};
	char dead_indicator_6[arr_widh][arr_heigh]
	{
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ','|','-','-','-','-','-','-',' ',' ',
' ','|',' ','/',' ',' ',' ','|',' ',' ',
' ','|','/',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ',' ','O',' ',' ',
' ','|',' ',' ',' ',' ','/','|','\\',' ',
' ','|',' ',' ',' ',' ',' ','|',' ',' ',
' ','|',' ',' ',' ',' ','/',' ','\\',' ',
' ','|',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',

	};
	//-------------------------------------------------------------------------------------------------------------------------
	if(score==0)
		for (int i{}; i < arr_heigh; ++i)
		{

			for (int j{}; j < arr_widh; ++j)
			{
				std::cout << dead_indicator_0[i][j];
			}
			std::cout << std::endl;

		}
	//-------------------------------------------------------------------------------------------------------------------------
	if (score == 1)
		for (int i{}; i < arr_heigh; ++i)
		{

			for (int j{}; j < arr_widh; ++j)
			{
				std::cout << dead_indicator_1[i][j];
			}
			std::cout << std::endl;

		}
	//-------------------------------------------------------------------------------------------------------------------------
	if (score ==2)
		for (int i{}; i < arr_heigh; ++i)
		{

			for (int j{}; j < arr_widh; ++j)
			{
				std::cout << dead_indicator_2[i][j];
			}
			std::cout << std::endl;

		}
	//-------------------------------------------------------------------------------------------------------------------------
	if (score == 3)
		for (int i{}; i < arr_heigh; ++i)
		{

			for (int j{}; j < arr_widh; ++j)
			{
				std::cout << dead_indicator_3[i][j];
			}
			std::cout << std::endl;

		}
	//-------------------------------------------------------------------------------------------------------------------------
	if (score == 4)
		for (int i{}; i < arr_heigh; ++i)
		{

			for (int j{}; j < arr_widh; ++j)
			{
				std::cout << dead_indicator_4[i][j];
			}
			std::cout << std::endl;

		}
	//-------------------------------------------------------------------------------------------------------------------------
	if (score == 5)
		for (int i{}; i < arr_heigh; ++i)
		{

			for (int j{}; j < arr_widh; ++j)
			{
				std::cout << dead_indicator_5[i][j];
			}
			std::cout << std::endl;

		}
	//-------------------------------------------------------------------------------------------------------------------------
	if (score == 6)
		for (int i{}; i < arr_heigh; ++i)
		{

			for (int j{}; j < arr_widh; ++j)
			{
				std::cout << dead_indicator_6[i][j];
			}
			std::cout << std::endl;

		}
	//-------------------------------------------------------------------------------------------------------------------------
}

bool restart_game()
{
	int choise;
	std::cout << "Restart game?\n " << "1)yes\n " << "2)No" << std::endl;
	std::cin >> choise;
	while (std::cin.fail()||choise < 1 || choise>2)
	{
		std::cout << "Invalid input. Please enter 1 for Yes or 2 for No: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> choise;
	}
	system("cls");

	if (choise == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}