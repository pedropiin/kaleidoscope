#include <string>
#include <vector>
#include <memory>

class expr_ast {
	public:
		virtual ~expr_ast() = default;
};

class number_expr_ast : public expr_ast {
	double val;

	public:
		number_expr_ast(double val) : val(val) {}
};

class variable_expr_ast : public expr_ast {
	std::string name;

	public:
		variable_expr_ast(std::string &name) : name(name) {}
};

class binary_expr_ast : public expr_ast {
	char op;
	std::unique_ptr<expr_ast> lhs, rhs;

	public:
		binary_expr_ast(char op, std::unique_ptr<expr_ast> lhs, std::unique_ptr<expr_ast> rhs) 
			: op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class call_expr_ast : public expr_ast {
	std::string callee;
	std::vector<std::unique_ptr<expr_ast>> args;

	public:
		call_expr_ast(const std::string &callee, std::vector<std::unique_ptr<expr_ast>> args) 
			: callee(callee), args(std::move(args)) {}
};

class prototype_ast {
	std::string name;
	std::vector<std::string> args;

	public:
		prototype_ast(const std::string &name, std::vector<std::string> args) 
			: name(name), args(std::move(args)) {}

		const std::string &get_name() const {
			return name;
		}
};

class function_ast {
	std::unique_ptr<prototype_ast> proto;
	std::unique_ptr<expr_ast> body;

	public:
		function_ast(std::unique_ptr<prototype_ast> proto, std::unique_ptr<expr_ast> body)
			: proto(std::move(proto)), body(std::move(body)) {}
};


