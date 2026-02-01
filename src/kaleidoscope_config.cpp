#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <map>

#include "ast.hpp"
#include "error.hpp"
#include "parser.cpp"

class KaleidoscopeConfig {
    private:
        // LLVM-related members
        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::IRBuilder<>> builder;
        std::unique_ptr<llvm::Module> module;
        std::map<std::string, llvm::Value *> named_values;

    public:
        Parser parser;

        void handle_definition() {
            if (parser.parse_definition()) 
				fprintf(stderr, "Parsed a function definition.\n");
			else
				parser.get_next_token();
        }

        void handle_extern() {
			if (parser.parse_extern()) 
				fprintf(stderr, "Parsed an extern.\n");
			else 
				parser.get_next_token();
		}

		void handle_top_level_expr() {
			if (parser.parse_top_level_expr()) 
				fprintf(stderr, "Parsed a top-level expression.\n");
			else
				parser.get_next_token();
		}

};