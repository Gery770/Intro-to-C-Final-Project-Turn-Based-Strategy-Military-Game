#include <iostream>
#include <string>
#include "troop.h"
#include "player.h"
#include <vector>
#include "functions.h"
#include <windows.h>
#include <algorithm>
#include <random>
#include <math.h>

std::map<std::string, std::map<std::string, int>> troopRatios = {
	{"Soldier", {
		{"Soldier", 1},
		{"Anti-Tank Soldier", 2},
		{"Anti-Air Soldier", 2},
		{"Anti-Tank Bomber", -2},
		{"Tank", -4},
		{"Heavy Tank", -5},
		{"Anti-Air Tank", -2},
		{"Attack Helicopter", -5},
		{"Jet", -6}

	}},
	{"Anti-Tank Soldier", {
		{"Soldier", -2},
		{"Anti-Tank Soldier", 1},
		{"Anti-Air Soldier", 1},
		{"Anti-Tank Bomber", -3},
		{"Tank", 3},
		{"Heavy Tank", 2},
		{"Anti-Air Tank", 4},
		{"Attack Helicopter", -6},
		{"Jet", -8}

	}},
	{"Anti-Air Soldier", {
		{"Soldier", -2},
		{"Anti-Tank Soldier", 1},
		{"Anti-Air Soldier", 1},
		{"Anti-Tank Bomber", 4},
		{"Tank", -6},
		{"Heavy Tank", -8},
		{"Anti-Air Tank", -3},
		{"Attack Helicopter", 3},
		{"Jet", 2}

	}},
	{"Anti-Tank Bomber", {
		{"Soldier", 2},
		{"Anti-Tank Soldier", 4},
		{"Anti-Air Soldier", -4},
		{"Anti-Tank Bomber", 1},
		{"Tank", 5},
		{"Heavy Tank", 3},
		{"Anti-Air Tank", 1},
		{"Attack Helicopter", -3},
		{"Jet", -5}

	}},
	{"Tank", {
		{"Soldier", 4},
		{"Anti-Tank Soldier", -3},
		{"Anti-Air Soldier", 6},
		{"Anti-Tank Bomber", -5},
		{"Tank", 1},
		{"Heavy Tank", -3},
		{"Anti-Air Tank", 2},
		{"Attack Helicopter", -3},
		{"Jet", -4}

	}},
	{"Heavy Tank", {
		{"Soldier", 5},
		{"Anti-Tank Soldier", -2},
		{"Anti-Air Soldier", 8},
		{"Anti-Tank Bomber", -3},
		{"Tank", 3},
		{"Heavy Tank", 1},
		{"Anti-Air Tank", 4},
		{"Attack Helicopter", -2},
		{"Jet", -3}

	}},
	{"Anti-Air Tank", {
		{"Soldier", 2},
		{"Anti-Tank Soldier", -4},
		{"Anti-Air Soldier", 3},
		{"Anti-Tank Bomber", 1},
		{"Tank", -2},
		{"Heavy Tank", -4},
		{"Anti-Air Tank", 1},
		{"Attack Helicopter", 5},
		{"Jet", 3}

	}},
	{"Attack Helicopter", {
		{"Soldier", 5},
		{"Anti-Tank Soldier", 6},
		{"Anti-Air Soldier", -3},
		{"Anti-Tank Bomber", 3},
		{"Tank", 3},
		{"Heavy Tank", 2},
		{"Anti-Air Tank", -5},
		{"Attack Helicopter", 1},
		{"Jet", -3}

	}},
	{"Jet", {
		{"Soldier", 6},
		{"Anti-Tank Soldier", 8},
		{"Anti-Air Soldier", -2},
		{"Anti-Tank Bomber", 5},
		{"Tank", 4},
		{"Heavy Tank", 3},
		{"Anti-Air Tank", -3},
		{"Attack Helicopter", 3},
		{"Jet", 1}

	}}
};

std::map<int, std::string> troop_values = {
	{1, "Soldier"},
	{2, "Anti-Tank Soldier"},
	{3, "Anti-Air Soldier"},
	{4, "Tank"},
	{5, "Heavy Tank"},
	{6, "Anti-Air Tank"},
	{7, "Attack Helicopter"},
	{8, "Anti-Tank Bomber"},
	{9, "Jet"},
	
};

std::map<std::string, int> troop_cost = {
	{"Soldier", 5},
	{"Anti-Tank Soldier", 7},
	{"Anti-Air Soldier", 9},
	{"Tank", 10},
	{"Heavy Tank", 15},
	{"Anti-Air Tank", 13},
	{"Attack Helicopter", 20},
	{"Anti-Tank Bomber", 25},
	{"Jet", 30},

};

std::map<int, std::vector<int>> valid_moves = {
	{1, {2,3,4}},
	{2, {1,4}},
	{3, {1,4}},
	{4, {1,2,3,5,6,7}},
	{5, {4,6,8}},
	{6, {4,5,7,8}},
	{7, {4,6,8}},
	{8, {5,6,7,9,10,11}},
	{9, {8,11}},
	{10, {8,11}},
	{11, {9,10,8}},

};

void display_turn(player &plr) {
	system("cls");

	if (plr.get_team()) {//red
		std::cout <<
		"\033[1;31m-----------------------------------\033[0m\n"
		"\033[1;31m----------RED PLAYER TURN----------\033[0m\n"
		"\033[1;31m-----------------------------------\033[0m\n";
	}
	else {//blue
		std::cout <<
		"\033[1;34m------------------------------------\033[0m\n"
		"\033[1;34m----------BLUE PLAYER TURN----------\033[0m\n"
		"\033[1;34m------------------------------------\033[0m\n";
	}
	system("pause");
}

void shop(player &plr) {
	int choice = 10;
	while (choice != 0) {
		system("cls");
		std::cout << "You have $" << plr.get_cash() << "." << std::endl;
		std::cout << "Your base is at " << plr.get_base_health() << "% health" << std::endl;
		std::cout << "-----------------------" << std::endl;
		std::cout << "Welcome to the Barracks" << std::endl;
		std::cout << "-----------------------" << std::endl << std::endl;
		std::cout << "Please select a unit to purchase" << std::endl;
		std::cout << "[1] Soldier - $5" << std::endl;
		std::cout << "[2] Anti-Tank Soldier - $7" << std::endl;
		std::cout << "[3] Anti-Air Soldier - $9" << std::endl;
		std::cout << "[4] Tank - $10" << std::endl;
		std::cout << "[5] Heavy Tank - $15" << std::endl;
		std::cout << "[6] Anti-Air Tank - $13" << std::endl;
		std::cout << "[7] Attack Helicopter - $20" << std::endl;
		std::cout << "[8] Anti-Tank Bomber - $25" << std::endl;
		std::cout << "[9] Jet - $30" << std::endl << std::endl;
		std::cout << "[0] - Continue " << std::endl;
		std::string choice_str;
		std::getline(std::cin, choice_str);
		choice = std::stoi(choice_str);
		if (choice != 0) {
			std::string chosen_unit = troop_values.at(choice);
			int chosen_unit_cost = troop_cost.at(chosen_unit);
			if (plr.get_cash() >= chosen_unit_cost) {
				system("cls");
				std::cout << "You have $" << plr.get_cash() << "." << std::endl;
				std::cout << "Please enter how many " << chosen_unit << "s you like to purchase at $" << chosen_unit_cost << " per unit." << std::endl;
				std::cout << "You can buy a maximum of " << plr.get_cash() / chosen_unit_cost << " " << chosen_unit << "s." << std::endl;
				std::string temp_chosen_unit_amount;
				std::getline(std::cin, temp_chosen_unit_amount);
				int chosen_unit_amount = std::stoi(temp_chosen_unit_amount);

				if (plr.get_cash() >= chosen_unit_cost * chosen_unit_amount) {
					system("cls");
					std::cout << "Confirm you would like to purchase " << chosen_unit_amount << " " << chosen_unit << "s for $" << chosen_unit_cost * chosen_unit_amount << "." << std::endl;
					std::cout << "[1] Confirm" << std::endl;
					std::cout << "[2] Cancel" << std::endl;
					std::string conf_string;
					std::getline(std::cin, conf_string);
					int conf = std::stoi(conf_string);
					if (conf == 1) {
						system("cls");
						std::cout << "You have purchased " << chosen_unit_amount << " " << chosen_unit << "s." << std::endl;
						for (int i = 0; i < chosen_unit_amount; i++) {
							print_unit(chosen_unit, plr.get_team());
						}
						plr.change_cash(-(chosen_unit_cost * chosen_unit_amount));
						plr.add_troops(chosen_unit, chosen_unit_amount);
						system("pause");
					}
				}
				else {
					system("cls");
					std::cout << "You don't have enough money for that" << std::endl;
					system("pause");
				}
			}
			else {
				system("cls");
				std::cout << "You don't have enough money for that" << std::endl;
				system("pause");
			}
			

		}

		
	}

}

void move(player &plr) {
	std::vector<int> moved_locations;
	int choice = 20;
	while (choice != 0) {

		system("cls");
		std::vector<troop> plr_units = plr.get_troops();
		std::cout << "Your base is at " << plr.get_base_health() << "% health" << std::endl;
		print_map();
		std::map<int, std::vector<troop>> locations;

		for (int i = 1; i < 12; i++) { // fill locations map
			std::vector<troop> troops_at_location;
			for (troop j : plr_units) { // for every troop 
				if (j.get_position() == i) { // if at same position of current location
					troops_at_location.push_back(j); // add to vector
				}
			}
			if (!troops_at_location.empty()) {
				locations.insert({ i,troops_at_location }); // add to map
			}
		}

		for (int i = 1; i < 12; i++) {
			if (locations.count(i) != 0) { // check if exists
				std::cout << "At fort #" << i << " you have these units: " << std::endl;
				std::map<std::string, int> troop_groups; // create a map where we store amount of certain troops at said location
				for (troop j : locations.at(i)) { // for every troop inside that location
					if (troop_groups.find(j.get_name()) == troop_groups.end()) { // if does not exist
						troop_groups.insert({ j.get_name(),1 });
					}
					else { // if does
						troop_groups.at(j.get_name()) += 1;
					}
				}
				for (auto k : troop_groups) {
					std::cout << " " << k.second << " " << k.first << "s " << std::endl;

				}
				std::cout << "--------------------" << std::endl;
			}
		}
		std::string current_pos_str;
		std::string next_pos_str;
		std::cout << "Enter [0] to exit" << std::endl;
		std::cout << "What position do you want to move troops from? [1-11]" << std::endl;
		std::getline(std::cin, current_pos_str);
		int current_pos = std::stoi(current_pos_str);
		if (current_pos == 0) {
			choice = 0;
			break;
		}
		std::cout << "What position would you like to move these troops to? [1-11]" << std::endl;
		std::getline(std::cin, next_pos_str);
		int next_pos = std::stoi(next_pos_str);
		bool is_valid = false;
		for (auto& x : valid_moves.at(current_pos)) {
			if (x == next_pos) {
				is_valid = true;
				for (int i = 0; i < moved_locations.size(); i++) {
					if (current_pos == moved_locations.at(i)) {
						is_valid = false;
						std::cout << "This position has already been moved" << std::endl;
						system("pause");
					}
				}
			}
		}
		if (locations.count(current_pos) == 0) {
			is_valid = false;
			std::cout << "There is nothing in that position to move" << std::endl;
			system("pause");
		}
		if (is_valid) {
			moved_locations.push_back(next_pos);
			plr.move_troops(current_pos, next_pos);
		}
		
		
	}
	
}

void manage(player &plr) {
	system("cls");
	int choice = 0;
	int income = 0;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Welcome to your income manager" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "You currently have: $" << plr.get_cash() << " dollars" << std::endl << std::endl;
	std::cout << "Please enter your preffered method of income" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "[1] War Bonds - Sell War Bonds To Public - 100% return of $10-25" << std::endl;
	std::cout << "[2] Mercenary Contract - Provide Military Services For Customers - 80% return rate of $15-20" << std::endl;
	std::cout << "[3] Scavange Scrap - Gather And Sell Scrap From Battlefield - 75% return rate of $20-25" << std::endl;
	std::cout << "[4] Smuggle Weapons - Smuggle Weapons From Enemy Territory - 50% return rate of $25-30" << std::endl;
	std::cout << "[5] Black Market - Illegaly Sell Military Equipment On Temu - 20% return rate of $30-40" << std::endl;
	std::string choice_str;
	std::getline(std::cin, choice_str);
	choice = std::stoi(choice_str);

	std::random_device rd;
	std::mt19937 gen(rd());

	if (choice == 1) {
		std::uniform_int_distribution<> distr(10, 25);
		
		income = distr(gen);
		std::cout << "You have sold war bonds and made a total of $" << income << " dollars." << std::endl;
		plr.change_cash(income);
		system("pause");
	}
	else if (choice == 2) {
		std::uniform_int_distribution<> distr(1, 100);
		int chosen_num = distr(gen);
		
		if (chosen_num <= 80) {
			std::uniform_int_distribution<> distr2(15, 20);
			income = distr2(gen);
			std::cout << "You have successfully provided services for many forign leaders and made a total of $" << income << " dollars." << std::endl;
			plr.change_cash(income);
			system("pause");
		}
		else {
			std::cout << "You have failed to provide services for your customer, a cartel leader is now dead." << std::endl;
			system("pause");
		}
	}
	else if (choice == 3) {
		std::uniform_int_distribution<> distr(1, 100);
		int chosen_num = distr(gen);

		if (chosen_num <= 75) {
			std::uniform_int_distribution<> distr2(20, 25);
			income = distr2(gen);
			std::cout << "You have successfully scavanged and sold scrap, making a total of $" << income << " dollars." << std::endl;
			plr.change_cash(income);
			system("pause");
		}
		else {
			std::cout << "You have failed to find any valuable scrap, morale is low." << std::endl;
			system("pause");
		}
	}
	else if (choice == 4) {
		std::uniform_int_distribution<> distr(1, 100);
		int chosen_num = distr(gen);

		if (chosen_num <= 50) {
			std::uniform_int_distribution<> distr2(25, 30);
			income = distr2(gen);
			std::cout << "You have successfully smuggled weaponry from the enemy, making a total of $" << income << " dollars." << std::endl;
			plr.change_cash(income);
			system("pause");
		}
		else {
			std::cout << "The spy you hired was hung for espionage, you feel a great deal of guilt." << std::endl;
			system("pause");
		}
	}
	else if (choice == 5) {
		std::uniform_int_distribution<> distr(1, 100);
		int chosen_num = distr(gen);

		if (chosen_num <= 20) {
			std::uniform_int_distribution<> distr2(30, 35);
			income = distr2(gen);
			std::cout << "You have successfully sold contraband to foriegn customers on Temu, making a total of $" << income << " dollars." << std::endl;
			plr.change_cash(income);
			system("pause");
		}
		else {
			std::cout << "The FBI banned your Temu account, your boss seems upset." << std::endl;
			system("pause");
		}
	}

}

void battle(player& plr_red, player& plr_blue, bool red_attack) {
	system("cls");

	std::random_device rd;
	std::mt19937 gen(rd());

	std::vector<troop> plr_red_units = plr_red.get_troops();
	std::vector<troop> plr_blue_units = plr_blue.get_troops();

	std::map<int, std::vector<troop>> plr_red_locations; // looks like pos 1 = tank, soldier, tank, jet
	std::map<int, std::vector<troop>> plr_blue_locations;

	for (int i = 1; i < 12; i++) { // fill locations map
		std::vector<troop> troops_at_location;
		for (troop j : plr_red_units) { // for every troop 
			if (j.get_position() == i) { // if at same position of current location
				troops_at_location.push_back(j); // add to vector
			}
		}
		if (!troops_at_location.empty()) {
			plr_red_locations.insert({ i,troops_at_location }); // add to map
		}
	}

	for (int i = 1; i < 12; i++) { // fill locations map
		std::vector<troop> troops_at_location;
		for (troop j : plr_blue_units) { // for every troop 
			if (j.get_position() == i) { // if at same position of current location
				troops_at_location.push_back(j); // add to vector
			}
		}
		if (!troops_at_location.empty()) {
			plr_blue_locations.insert({ i,troops_at_location }); // add to map
		}
	}

	bool is_battle = false;// later for if theres no battles
	for (int i = 1; i < 12; i++) { // FOR EVERY POSITION
		if (plr_red_locations.count(i) && plr_blue_locations.count(i)) { // check that both players have troops at location
			is_battle = true;
			
			
			std::map<std::string, int> plr_red_troop_groups;
			std::map<std::string, int> plr_blue_troop_groups;

			for (troop j : plr_red_locations.at(i)) { // add red troop groups
				if (plr_red_troop_groups.find(j.get_name()) == plr_red_troop_groups.end()) { // if does not exist
					plr_red_troop_groups.insert({ j.get_name(),1 });
				}
				else { // if does
					plr_red_troop_groups.at(j.get_name()) += 1;
				}
			}
			for (troop j : plr_blue_locations.at(i)) { // add blue troop groups
				if (plr_blue_troop_groups.find(j.get_name()) == plr_blue_troop_groups.end()) { // if does not exist
					plr_blue_troop_groups.insert({ j.get_name(),1 });
				}
				else { // if does
					plr_blue_troop_groups.at(j.get_name()) += 1;
				}
			}
			print_map_zone(i);
			std::cout << "-----------------" << std::endl;
			std::cout << "Battle of Fort #" << i << std::endl;
			std::cout << "-----------------" << std::endl;
			if (red_attack) {
				std::cout << "\033[1;31m-----Red Attack-----\033[0m\n";
			}
			else {
				std::cout << "\033[1;34m-----Blue Attack-----\033[0m\n";
			}
			for (auto t : plr_red_troop_groups) {
				int troop_value = 0;
				for (auto n : troop_values) {
					if (n.second == t.first) {
						troop_value = n.first;
					}
				}
				std::cout << "[" << troop_value << "] " << t.second << " " << t.first << "s" << std::endl;
			}
			std::cout << "--------------V.S.--------------" << std::endl;
			if (red_attack) {
				std::cout << "\033[1;34m-----Blue Defend-----\033[0m\n";
			}
			else {
				std::cout << "\033[1;31m-----Red Defend-----\033[0m\n";
			}
			for (auto t : plr_blue_troop_groups) {
				int troop_value = 0;
				for (auto n : troop_values) {
					if (n.second == t.first) {
						troop_value = n.first;
					}
				}
				std::cout << "[" << troop_value << "] " << t.second << " " << t.first << "s" << std::endl;
			}
			std::cout << "Enter which troops do you want to attack with? [1-9]" << std::endl;
			std::string chosen_attack_troop_str;
			std::getline(std::cin, chosen_attack_troop_str);
			int chosen_attack_troop = std::stoi(chosen_attack_troop_str);
			std::cout << "Enter which enemy troops you would like to attack [1-9]" << std::endl;
			std::string chosen_attacked_troop_str;
			std::getline(std::cin, chosen_attacked_troop_str);
			int chosen_attacked_troop = std::stoi(chosen_attacked_troop_str);

			std::string attacking_unit = troop_values.at(chosen_attack_troop);
			std::string defending_unit = troop_values.at(chosen_attacked_troop);

			int attacking_unit_num = plr_red_troop_groups.at(attacking_unit);
			int defending_unit_num = plr_blue_troop_groups.at(defending_unit);

			std::map<std::string, int> attacking_unit_ratios = troopRatios.at(attacking_unit);
			std::map<std::string, int> defending_unit_ratios = troopRatios.at(defending_unit);

			double attacking_unit_ratio = attacking_unit_ratios.at(defending_unit);
			double defending_unit_ratio = defending_unit_ratios.at(attacking_unit);
				
			double new_attacking_amount = 0;
			double new_defending_amount = 0;

			if (attacking_unit_ratio > 0 && attacking_unit_ratio != 1) {
				double num = attacking_unit_num * attacking_unit_ratio;
				if (num > defending_unit_num) {
					num -= defending_unit_num;
					num = ceil(num / attacking_unit_ratio);
					new_attacking_amount = num;
				}
				else {
					new_defending_amount = defending_unit_num - num;
				}
			}
			else if (attacking_unit_ratio == 1) {
				if (attacking_unit_num > defending_unit_num) {
					new_attacking_amount = attacking_unit_num - defending_unit_num;
				}
				else if (defending_unit_num > attacking_unit_num) {
					new_defending_amount = defending_unit_num - attacking_unit_num;
				}
			}
			else {
				double num = defending_unit_num * defending_unit_ratio;
				if (num > attacking_unit_num) {
					num -= attacking_unit_num;
					num = ceil(num / defending_unit_ratio);
					new_defending_amount = num;
				}
				else {
					new_attacking_amount = attacking_unit_num - num;
				}
			}
			system("cls");
			for (int b = 0; b < attacking_unit_num; b++) { // for every attacking unit
				print_unit(attacking_unit, plr_red.get_team());
			}
			std::cout << "----------V.S.----------" << std::endl;

			for (int b = 0; b < defending_unit_num; b++) { // for every defending unit
				print_unit(defending_unit, plr_blue.get_team());
			}
			system("pause");
			system("cls");
			for (int b = 0; b < new_attacking_amount; b++) { // for every attacking unit
				print_unit(attacking_unit, plr_red.get_team());
			}
			std::cout << "------------------------" << std::endl;

			for (int b = 0; b < new_defending_amount; b++) { // for every defending unit
				print_unit(defending_unit, plr_blue.get_team());
			}
			system("pause");
			

			plr_red.set_troops_at_pos(i, attacking_unit, new_attacking_amount);
			plr_blue.set_troops_at_pos(i, defending_unit, new_defending_amount);
		}
	}
}

bool is_attack(player& plr_red, player& plr_blue) {
	bool is_battle = false;
	std::vector<troop> plr_red_units = plr_red.get_troops();
	std::vector<troop> plr_blue_units = plr_blue.get_troops();

	std::map<int, std::vector<troop>> plr_red_locations; // looks like pos 1 = tank, soldier, tank, jet
	std::map<int, std::vector<troop>> plr_blue_locations;

	for (int i = 1; i < 12; i++) { // fill locations map
		std::vector<troop> troops_at_location;
		for (troop j : plr_red_units) { // for every troop 
			if (j.get_position() == i) { // if at same position of current location
				troops_at_location.push_back(j); // add to vector
			}
		}
		if (!troops_at_location.empty()) {
			plr_red_locations.insert({ i,troops_at_location }); // add to map
		}
	}

	for (int i = 1; i < 12; i++) { // fill locations map
		std::vector<troop> troops_at_location;
		for (troop j : plr_blue_units) { // for every troop 
			if (j.get_position() == i) { // if at same position of current location
				troops_at_location.push_back(j); // add to vector
			}
		}
		if (!troops_at_location.empty()) {
			plr_blue_locations.insert({ i,troops_at_location }); // add to map
		}
	}

	for (int i = 1; i < 12; i++) { // FOR EVERY POSITION
		if (plr_red_locations.count(i) && plr_blue_locations.count(i)) { // check that both players have troops at location
			is_battle = true;
		}
	}
	return is_battle;
}

void base_damage(player& plr_red, player& plr_blue) {

	std::vector<troop> plr_red_units = plr_red.get_troops();
	std::vector<troop> plr_blue_units = plr_blue.get_troops();

	std::map<int, std::vector<troop>> plr_red_locations; // looks like pos 1 = tank, soldier, tank, jet
	std::map<int, std::vector<troop>> plr_blue_locations;

	for (int i = 1; i < 12; i++) { // fill locations map
		std::vector<troop> troops_at_location;
		for (troop j : plr_red_units) { // for every troop 
			if (j.get_position() == i) { // if at same position of current location
				troops_at_location.push_back(j); // add to vector
			}
		}
		if (!troops_at_location.empty()) {
			plr_red_locations.insert({ i,troops_at_location }); // add to map
		}
	}

	for (int i = 1; i < 12; i++) { // fill locations map
		std::vector<troop> troops_at_location;
		for (troop j : plr_blue_units) { // for every troop 
			if (j.get_position() == i) { // if at same position of current location
				troops_at_location.push_back(j); // add to vector
			}
		}
		if (!troops_at_location.empty()) {
			plr_blue_locations.insert({ i,troops_at_location }); // add to map
		}
	}
	int red_damage = 0;
	int blue_damage = 0;
	if (plr_red_locations.count(11)) {// if red is at blue base
		for (troop t : plr_red_locations.at(11)) {
			blue_damage += 1;
		}
		system("cls");
		std::cout << "\033[1;31mRed\033[0m" << " does " << blue_damage << " damage to " "\033[1; 34mBlues\033[0m" << " base." << std::endl;
		plr_blue.change_base_health(-blue_damage);
		system("pause");
	}
	if (plr_blue_locations.count(1)){ // if blue is at red base
		for (troop t : plr_blue_locations.at(1)) {
			red_damage += 1;
		}
		system("cls");
		std::cout << "\033[1;34mBlue\033[0m" << " does " << red_damage << " damage to " "\033[1; 31mReds\033[0m" << " base." << std::endl;
		plr_red.change_base_health(-red_damage);
		system("pause");
	}


}

void two_plr_game() {

	system("cls");
	std::cout << "----------------------" << std::endl;
	std::cout << "2 Player Mode Selected" << std::endl;
	std::cout << "----------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Player 1, please enter your name: ";
	std::string p1_name;
	std::getline(std::cin,p1_name);
	std::cout << std::endl;
	std::cout << "Player 2, please enter your name: ";
	std::string p2_name;
	std::getline(std::cin, p2_name);

	player Red(100,p1_name,100, true);
	player Blue(100, p2_name, 100, false);

	std::cout << std::endl;
	std::cout << Red.get_name() << ", you are team " << "\033[1;31mRed\033[0m" << std::endl;
	std::cout << "----------V.S.----------" << std::endl;
	std::cout << Blue.get_name() << ", you are team " << "\033[1;34mBlue\033[0m" << std::endl;
	system("pause");

	while (Red.get_base_health() > 0 && Blue.get_base_health() > 0) { // while both players base alive
		display_turn(Red);
		shop(Red);
		move(Red);
		manage(Red);
		display_turn(Blue);
		shop(Blue);
		move(Blue);
		manage(Blue);
		while (is_attack(Red, Blue)) {
			battle(Red, Blue, true);
			battle(Blue, Red, false);
		}
		base_damage(Red,Blue);
	}
	if (Red.get_base_health() > 0) {
		system("cls");
		std::cout <<
			"\033[1;31m---------\033[0m\n"
			"\033[1;31mRed Wins!\033[0m\n"
			"\033[1;31m---------\033[0m\n";

	}
	else {
		system("cls");
		std::cout <<
			"\033[1;34m----------\033[0m\n"
			"\033[1;34mBlue Wins!\033[0m\n"
			"\033[1;34m----------\033[0m\n";
	}
}

int main() {
	std::cout << "Welcome to Tactical Warfare" << std::endl;
	std::cout << "Please Enter [1] To Start:" << std::endl;
	std::cout << std::endl;
	std::cout << "[1] Start 2 Player Game" << std::endl;

	std::string gamemode_answer_str;
	std::getline(std::cin, gamemode_answer_str);
	int gamemode_answer = std::stoi(gamemode_answer_str);
	if (gamemode_answer == 2) {
		
	}
	else {
		two_plr_game();
	}
	


	return 0;
};