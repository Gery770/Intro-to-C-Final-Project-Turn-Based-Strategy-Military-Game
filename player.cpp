#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include "troop.h"

player::player(const int& cash,const std::string& name,const int& base_health, const bool& is_red) {
	set_cash(cash);
	set_name(name);
	set_base_health(base_health);
	this->is_red = is_red;
	if (is_red) {
		base_pos = 1;
	}
	else {
		base_pos = 11;
	}
}

void player::set_name(const std::string& name) {
	if (name.empty()) {
		throw std::exception("Invalid Name");
	}
	this->name = name;
}

void player::set_cash(const int& cash) {
	if (cash < 0 || cash > 10000) {
		throw std::exception("Invalid cash");
	}
	this->cash = cash;
}

int player::get_cash() const{
	return cash;
}

void player::change_cash(const int value) {
	if (cash + value < 0) {
		cash = 0;
	}
	else {
		cash += value;
	}
}

void player::set_base_health(const int& base_health) {
	if (base_health < 0 || base_health > 10000) {
		throw std::exception("Invalid base_health");
	}
	this->base_health = base_health;
}

void player::change_base_health(const int value) {
	if (base_health + value < 0) {
		base_health = 0;
	}
	else
	{
		base_health += value;
	}
}

int player::get_base_health() const{
	return base_health;
}

void player::add_troops(std::string name, int amount) {
	for (int i = 0; i < amount; i++) {
		troop new_troop(name,base_pos,is_red);
		units.push_back(new_troop);
	}
}

void player::move_troops(const int start,const int end) {
	for (auto& i : units) {
		if (i.get_position() == start) {
			i.set_position(end);
		}
	}
}

std::vector<troop> player::get_troops() {
	return units;
}

void player::print_troops() const{
	for (auto i : units) {
		std::cout << "Troop Detected";
	}
	std::cout << units.size();
}

bool player::get_team() const {
	return is_red;
}

void player::set_troops_at_pos(const int pos, const std::string unit_name, const int unit_num) {
	for (auto it = units.begin(); it != units.end();) {
		if (it->get_position() == pos && it->get_name() == unit_name) {
			it = units.erase(it);
		}
		else {
			++it;
		}
	}
	for (int i = 0; i < unit_num; i++) {
		troop new_troop(unit_name, pos, is_red);
		units.push_back(new_troop);
	}
}

std::string player::get_name() const {
	return name;
}