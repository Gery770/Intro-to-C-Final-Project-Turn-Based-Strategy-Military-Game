#include "troop.h"
#include <iostream>
#include <string>
#include <vector>

troop::troop(const std::string& name, const int& position, const bool& is_red) {
	set_name(name);
	set_position(position);
	set_team(is_red);
}

void troop::set_name(const std::string& name) {
	if (name.empty()) {
		throw std::exception("Invalid Name");
	}
	this->name = name;
}

std::string troop::get_name() const{
	return name;
}

void troop::set_position(const int& position) {
	if (position < 1 || position > 11) {
		throw std::exception("Invalid position");
	}
	this->position = position;
}

int troop::get_position() const{
	return position;
}

void troop::set_team(const bool& is_red) {
	this->is_red = is_red;
}

bool troop::get_team() const {
	return is_red;
}

void troop::change_position(const int value) {
	if (position + value < 1 || position + value > 11) {
		throw std::exception("Invalid position");
	}
	position += value;

}