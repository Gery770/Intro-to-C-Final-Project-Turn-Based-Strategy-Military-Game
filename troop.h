#pragma once
#include <string>
#include <map>
#include <vector>

class troop {

private:

	std::string name;
	int position;
	bool is_red;


public:

	troop(const std::string& name, const int& position, const bool& is_red);

	void set_name(const std::string& name);
	std::string get_name() const;
	void set_position(const int& position);
	int get_position() const;
	void set_team(const bool& is_red);
	bool get_team() const;
	void change_position(const int value);

};