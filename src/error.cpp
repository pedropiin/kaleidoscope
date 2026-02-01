#include "llvm/IR/Value.h"

#include "error.hpp"
#include "ast.hpp"

std::unique_ptr<ExprAST> log_error(const char *str) {
    fprintf(stderr, "Error: %s\n", str);
    return nullptr;
}

std::unique_ptr<PrototypeAST> log_error_proto(const char *str) {
    log_error(str);
    return nullptr;
}

llvm::Value *log_error_value(const char *str) {
    log_error(str);
    return nullptr;
}