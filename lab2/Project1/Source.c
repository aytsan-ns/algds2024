#pragma warning (disable:4996)

#include "Header.h"

int main() {
	setlocale(LC_CTYPE, "Russian");
	
	char action;
	char white_space;
	tree* main_tree = NULL;

	while (true) {
		scanf("%c", &action);

		if (action == '+') main_tree = CreateTree(main_tree);
		else main_tree = DeleteTree(main_tree);
		scanf("%c", &white_space);

	}
	return 0;
}