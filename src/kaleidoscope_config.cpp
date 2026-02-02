#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <map>

#include "parser.cpp"
#include "codegen_visitor.hpp"

class KaleidoscopeConfig {
	public:
		Parser parser;
		CodegenVisitor visitor;

		void handle_definition() {
			if (std::unique_ptr<FunctionAST> function_node = parser.parse_definition()) {
				if (llvm::Function *function_ir = function_node->codegen(visitor)) {
					fprintf(stderr, "Read function definition:\n");
					function_ir->print(llvm::errs());
				}
			} else {
				parser.get_next_token();
			}
		}

		void handle_extern() {
			if (std::unique_ptr<PrototypeAST> prototype_node = parser.parse_extern()) {
				if (llvm::Function *prototype_ir = prototype_node->codegen(visitor)) {
					fprintf(stderr, "Read extern:\n");
					prototype_ir->print(llvm::errs());
				}
			} else {
				parser.get_next_token();
			}
		}

		void handle_top_level_expr() {
			if (std::unique_ptr<FunctionAST> function_node = parser.parse_top_level_expr()) {
				if (llvm::Function *function_ir = function_node->codegen(visitor)) {
					fprintf(stderr, "Read top-level expression:\n");
					function_ir->print(llvm::errs());
				}
			} else {
				parser.get_next_token();
			}
		}
};