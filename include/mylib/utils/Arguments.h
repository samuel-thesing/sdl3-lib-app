#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "mylib/export.h"
#include "mylib/utils/Logger.h"

class MYLIB_EXPORT Arguments {
private:
	std::string tool_name;

	std::unordered_set<std::string> flags;
	std::unordered_map<std::string, std::string> named_args;
	std::vector<std::string> args;

	struct Option {
		std::string name;
		std::string description;
		std::string abbreviation;
	};

	std::string tool_description;
	std::vector<Option> options;

public:
	Arguments(const std::string &tool_name);

	void add_option_flag(std::string name, std::string description,
		std::string abbreviation = "");
	void add_option_named_value(std::string name, std::string value_name,
		std::string description, std::string abbreviation = "");
	void set_general_description(std::string general_description);

	bool parse_args(int argc, char **argv);

	void print_help();

	unsigned get_arg_count() const {
		return static_cast<unsigned>(args.size());
	}
	unsigned is_args_empty() const { return args.empty(); }

	bool has_named_arg(const std::string &name);
	std::optional<std::string> get_named_arg(const std::string &name);
	bool has_flag(const std::string &name);

	Arguments &operator>>(char &c);
	Arguments &operator>>(std::string &s);
	Arguments &operator>>(int &i);
	Arguments &operator>>(long long &l);
	Arguments &operator>>(float &f);
	Arguments &operator>>(double &d);

	void remove_flag(const std::string &name);
	void remove_named_arg(const std::string &name);
	void clear_flags();
	void clear_named_args();
	void clear_args();
	void clear();
};

#endif // ARGUMENTS_H
