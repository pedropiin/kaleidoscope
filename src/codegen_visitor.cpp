#include "codegen_visitor.hpp"
#include "error.hpp"

// here I'm to implement the codegen functions themselves

llvm::Value *CodegenVisitor::visit_number_expr(NumberExprAST &number_expr) {
    // "Constants are all u niqued together and shared. 
	// For this reason, the API uses the 'foo::get(...)' idiom."
	return llvm::ConstantFP::get(*context, llvm::APFloat(number_expr.val));
}

llvm::Value *CodegenVisitor::visit_variable_expr(VariableExprAST &variable_expr) {
    std::map<std::string, llvm::Value *>::iterator v_it = named_values.find(variable_expr.name);
	if (v_it == named_values.end()) 
		log_error_value("Unkown variable name.");
	return v_it->second;
}

llvm::Value *CodegenVisitor::visit_binary_expr(BinaryExprAST &binary_expr) {
    llvm::Value *lhs_value = binary_expr.lhs->codegen(*this);
	llvm::Value *rhs_value = binary_expr.rhs->codegen(*this);
	if (!lhs_value || !rhs_value)
		return nullptr;

	switch (binary_expr.op) {
		case '+':
			return builder->CreateFAdd(lhs_value, rhs_value, "addtmp");
		case '-':
			return builder->CreateFSub(lhs_value, rhs_value, "subtmp");
		case '*':
			return builder->CreateFMul(lhs_value, rhs_value, "multmp");
		case '/':
			return builder->CreateFDiv(lhs_value, rhs_value, "divtmp");
		case '<':
			lhs_value = builder->CreateFCmpULT(lhs_value, rhs_value, "lcmptmp");
			return builder->CreateUIToFP(lhs_value, llvm::Type::getDoubleTy(*context), "booltmp");
		case '>':
			lhs_value = builder->CreateFCmpUGT(lhs_value, rhs_value, "gcmptmp");
			return builder->CreateUIToFP(lhs_value, llvm::Type::getDoubleTy(*context), "booltmp");
		default:
			return log_error_value("Invalid binary operator.");
	}
}

llvm::Value *CodegenVisitor::visit_call_expr(CallExprAST &call_expr) {
    llvm::Function *callee_function = module->getFunction(call_expr.callee);
	if (!callee_function)
		return log_error_value("Unkown function referenced.");

	if (callee_function->arg_size() != call_expr.args.size()) 
		return log_error_value("Incorrect number of arguments passed to function.");

	std::vector<llvm::Value *> args_values;
	for (unsigned i = 0, e = call_expr.args.size(); i != e; ++i) {
		args_values.push_back(call_expr.args[i]->codegen(*this));
		if (!args_values.back())
			return nullptr;
	}

	return builder->CreateCall(callee_function, args_values, "calltmp");
}

llvm::Function *CodegenVisitor::visit_function(FunctionAST &function) {

}

llvm::Function *CodegenVisitor::visit_prototype(PrototypeAST &prototype) {
    
}