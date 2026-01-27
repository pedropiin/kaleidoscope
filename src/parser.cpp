#include <string>
#include <vector>

#include "lexer.cpp"
#include "ast.cpp"

class parser {
	public:
		static int cur_tok;

		static int get_next_token() {
			return cur_tok = lexer::gettok();
		}
};
