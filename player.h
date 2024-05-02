#pragma once
#include <string>
#include <map>
#include <vector>
#include "troop.h"

class player {

private:

	int cash;
	std::string name;
	int base_health;
	int soldiers = 0;
	int tanks = 0;
	int planes = 0;
	bool is_red;
	int base_pos;

	std::vector<troop> units;


public:

	player(const int& cash, const std::string& name, const int& base_health, const bool& is_red);

	void set_name(const std::string& name);

	void set_cash(const int& cash);

	void change_cash(const int value);

	int get_cash() const;

	void set_base_health(const int& base_health);

	void change_base_health(const int value);

	int get_base_health() const;

	void add_troops(std::string name, int amount);

	std::vector<troop> get_troops();

	void print_troops() const;

	bool get_team() const;

	void move_troops(const int start,const int end);

	void set_troops_at_pos(const int pos, const std::string unit_name, const int unit_num);

	std::string get_name() const;

};

