#include "Racing.h" 
#include <iostream> 
#include <string>
#include <algorithm>
#include <cstdlib>

void Racing::OutputRegisteredTransport() 
{	
	std::cout << "Registered vehicles: ";
	for (int i = 0; i < regTransport.size(); ++i)
		{
			std::cout << regTransport[i].get()->name() << (i < regTransport.size() - 1 ? ", " : "");
		}
		std::cout << std::endl;
}

void Racing::OutputTransport(bool isAirVehicle)
{
	if (isAirVehicle)
		{
			for (int i = 4; i < vehicles.size(); ++i)
				{
					std::cout << i - 3 << ". " << vehicles[i].get()->name() << std::endl;
				}
			}
			else
			{
				for (int i = 0; i < vehicles.size() - 3; ++i)
					{
						std::cout << i + 1 << ". " << vehicles[i].get()->name() << std::endl;
					}
			}
}

void Racing::SortingMapContainer()
{
	std::copy(prizes.begin(), prizes.end(), 
		std::back_inserter<std::vector<std::pair<std::string, int>>>(s_prizes));

	std::sort(s_prizes.begin(), s_prizes.end(),
		[](const std::pair<std::string, int>& l, const std::pair<std::string, int>& r)
		{
			if (l.second != r.second)
			{
				return l.second < r.second;
			}

			return l.first < r.first;
		});
}

void Racing::CalculationOfRacePassing()
{
	int timeRace = 0;

	int regTransSize = regTransport.size();
	for (int i = 0; i < regTransSize; ++i)
	{
		auto vh = regTransport[i];
		int speed = vh.get()->r_speed();
		int dtbr = vh.get()->r_dtbr();
		int duration = vh.get()->r_duration();

		int distanceRest = 0;
		double remains = 0;
		int stops = 0;
		double rest = 0;
		int movement = 0;

		if (vh.get()->r_type() == "Ground")
		{
			distanceRest = speed * dtbr;
			stops = distance / distanceRest;

			if (distance != stops * distanceRest)
			{
				remains = distance - stops * distanceRest;
			}

			if (vh.get()->name() == "Camel")
			{
				if (stops > 1)
				{
					rest = duration + (stops - 2) * 8;
				}
				else if(stops == 1)
				{
					rest = duration;
				}				
				movement = stops * dtbr;

				double lastPush = 0;
				if (remains != 0)
				{
					lastPush = remains / speed;
					timeRace = rest + movement + lastPush;
				}
				else
				{
					timeRace = rest + movement;
				}
			}
			else if (vh.get()->name() == "Camel-fast")
			{
				if (stops == 2)
				{
					rest = duration + 6.5;
				}
				else if (stops > 2)
				{
					rest = duration + 6.5 + (stops - 2) * 8;
				}
				else
				{
					rest = duration;
				}

				movement = stops * dtbr;
				
				double lastPush = 0;
				if (remains != 0)
				{
					lastPush = remains / speed;
					timeRace = rest + movement + lastPush;
				}
				else
				{
					timeRace = rest + movement;
				}
			}
			else if (vh.get()->name() == "Centaur")
			{
				if (stops > 0) rest = stops * duration;

				movement = stops * dtbr;

				double lastPush = 0;
				if (remains != 0)
				{
					lastPush = remains / speed;
					timeRace = rest + movement + lastPush;
				}
				else
				{
					timeRace = rest + movement;
				}
			}
			else if (vh.get()->name() == "Boots")
			{
				if (stops == 1)
				{
					rest = duration;
				}
				else if (stops > 1)
				{
					rest = duration + (stops - 1) * 5;
				}
				movement = stops * dtbr;

				double lastPush = 0;
				if (remains != 0)
				{
					lastPush = remains / speed;
					timeRace = rest + movement + lastPush;
				}
				else
				{
					timeRace = rest + movement;
				}
			}
		}
		else if (vh.get()->r_type() == "Air")
		{
			if (vh.get()->name() == "Magic-carpet")
			{
				if (distance < 1000)
				{
					timeRace = distance / speed;
				}
				else if (distance < 5000)
				{
					int newDistance = distance - (distance * 3 / 100);
					timeRace = newDistance / speed;
				}
				else if (distance < 10000)
				{
					int newDistance = distance - (distance * 10 / 100);
					timeRace = newDistance / speed;
				}
				else if (distance >= 100000)
				{
					int newDistance = distance - (distance * 5 / 100);
					timeRace = newDistance / speed;
				}
			}
			else if (vh.get()->name() == "Eagle")
			{
				int newDistance = distance - (distance * 6 / 100);
				timeRace = newDistance / speed;
			}
			else if (vh.get()->name() == "Broomstick")
			{
				int ratio = distance / 1000;
				int newDistance = distance - (distance * ratio / 100);
				timeRace = newDistance / speed;
			}
		}
		prizes[vh.get()->name()] = timeRace;
	}
	SortingMapContainer();
}

void Racing::ClearingData()
{
	regTransport.clear();
	prizes.clear();
	s_prizes.clear();
}

void Racing::Beginning()
{
	int value = 1;
	std::cout << "Welcome to the racing simulator!" << std::endl;
	std::cout << "1. Race for ground transport" << std::endl;
	std::cout << "2. Race for air transport" << std::endl;
	std::cout << "3. Race for ground and air transport" << std::endl;
	std::cout << "Choose the type of race: ";
	std::cin >> type_race;

	std::cout << "Specify the distance length (Must be positive): ";
	std::cin >> distance;
	system("cls");
	std::cout << "At least 2 vehicles must be registered" << std::endl;
	std::cout << "1. Register a transport" << std::endl;
	std::cout << "2. Exit" << std::endl;
	std::cin >> value;

	system("CLS");

	switch (value)
	{
		case 1:
			Transport_registration();
			break;

		case 2:
			break;

		default:
			break;
	}
}

void Racing::Transport_registration()
{
	auto boots = std::make_shared<Boots>(6, 60, 10, "Boots");
	auto camel = std::make_shared <Camel>(10, 30, 5, "Camel");
	auto camelFast = std::make_shared<Camel_fast>(40, 10, 5, "Camel-fast");
	auto centaur = std::make_shared<Centaur>(15, 8, 2, "Centaur");
	auto eagle = std::make_shared<Eagle>(8, "Eagle");
	auto broomstick = std::make_shared<Broomstick>(20, "Broomstick");
	auto magicCarpet = std::make_shared<Magic_carpet>(10, "Magic-carpet");

	//Наземная гонка
	if (type_race == 1)
		{
			int value = 1;
			while (value != 0)
			{
				std::cout << "Race for a ground vehicle. Distance: " << distance << std::endl;

				//Вывод зарегистрированного транспорта
				if (regTransport.size() != 0)
				{
					OutputRegisteredTransport();
				}
				//Вывод траснпорта
				OutputTransport(false);
				std::cout << "Select transport or 0 to end the registration process: ";
				std::cin >> value;
				system("CLS");

				//Занесение транспорта в массив регистрации
				switch (value)
				{
					case 1:
						regTransport.push_back(boots);
						break;

					case 2:
						regTransport.push_back(camel);
						break;

					case 3:
						regTransport.push_back(camelFast);
						break;

					case 4:
						regTransport.push_back(centaur);
						break;
						
					case 0:
						break;

					default:
						break;
				}
				
				if (value != 0)
				{
					std::cout << regTransport.back().get()->name() << " successfully registered!" << std::endl;
				}
			}
		}
	// Воздушная гонка
	else if (type_race == 2)
	{		
		int value = 1;
		while (value != 0)
		{
			std::cout << "Race for a air vehicle. Distance: " << distance << std::endl;

			//Вывод зарегистрированного транспорта
			if (regTransport.size() != 0)
			{
				OutputRegisteredTransport();
			}
			//Вывод траснпорта
			OutputTransport(true);
			std::cout << "Select transport or 0 to end the registration process: ";
			std::cin >> value;
				
			system("CLS");

			//Занесение транспорта в массив регистрации
			switch (value)
			{
				case 1:
					regTransport.push_back(eagle);
					break;
						
				case 2:
					regTransport.push_back(broomstick);
					break;
						
				case 3:
					regTransport.push_back(magicCarpet);
					break;

				case 0:
					break;

				default:
					break;
			}
			if (value != 0)
			{
				std::cout << regTransport.back().get()->name() << " successfully registered!" << std::endl;
			}
		}
	}

	// Наземная и воздушная гонка
	else if (type_race == 3)
	{
		int value = 1;
		while (value != 0)
		{
			std::cout << "Race for a ground and air vehicle. Distance: " << distance << std::endl;

			//Вывод зарегистрированного транспорта
			if (regTransport.size() != 0)
			{
				OutputRegisteredTransport();
			}

			//Вывод траснпорта
			for (int i = 0; i < vehicles.size(); ++i)
			{
				std::cout << i + 1 << ". " << vehicles[i].get()->name() << std::endl;
			}
			std::cout << "Select transport or 0 to end the registration process: ";
			std::cin >> value;
			
			system("CLS");

			//Занесение транспорта в массив регистрации
			switch (value)
			{
				case 1:
					regTransport.push_back(boots);
					break;

				case 2:
					regTransport.push_back(camel);
					break;

				case 3:
					regTransport.push_back(camelFast);
					break;

				case 4:
					regTransport.push_back(centaur);
					break;

				case 5:
					regTransport.push_back(eagle);
					break;
					
				case 6:
					regTransport.push_back(broomstick);
					break;
				
				case 7:
					regTransport.push_back(magicCarpet);
					break;
				
				case 0:
					break;

				default:
					break;
			}

			if (value != 0)
			{
				std::cout << regTransport.back().get()->name() << " successfully registered!" << std::endl;
			}
		}
	}
	int choice = 0;
	std::cout << "1. Register a transport" << std::endl;
	std::cout << "2. Start the race" << std::endl;
	std::cout << "3. Exit" << std::endl;
	std::cout << "Select an action: ";
	std::cin >> choice;

	system("CLS");

	switch (choice)
	{
		case 1:
			Transport_registration();
			break;
				
		case 2:
			Race_results();
			break;
		
		case 3:
			break;
		
		default:
			break;
	}
}

void Racing::Race_results()
{
	std::cout << "Race results: " << std::endl;

	CalculationOfRacePassing();

	int medalPlace = 1;
	for (auto const& pair : s_prizes)
	{
		std::cout << medalPlace++ << ". ";
		std::cout << pair.first << ". Time: " << pair.second << std::endl;
	}

	std::cout << std::endl;

	int value = 0;
	std::cout << "1. Have another race?" << std::endl;
	std::cout << "2. Exit" << std::endl;
	std::cin >> value;

	switch (value)
	{
	case 1:
		ClearingData();
		system("cls");
		Beginning();
		break;

	case 2:
		break;

	default:
		break;
	}
}