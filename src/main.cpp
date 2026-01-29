#include "lexer.cpp"
#include "parser.cpp"

int main(int argc, char* argv[]) {
	
	Parser parser;
	fprintf(stderr, "ready> ");
	parser.get_next_token();

	int eof = 0;
	while (!eof) {
		fprintf(stderr, "ready> ");
		switch (parser.curr_tok) {
			case tok_def: 
				parser.handle_definition();
				break;
			case tok_extern:
				parser.handle_extern();
				break;
			case ';':
				parser.get_next_token();
				break;
			case tok_eof:
				eof = 1;
				break;
			default:
				parser.handle_top_level_expr();
				break;
		}
	}

	return 0;
}
