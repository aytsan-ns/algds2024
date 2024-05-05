#include "Header.h"

void Root(tree** T) {
	(*T)->color = "BLACK";
}

tree* Father(tree* T, int z) {
	if (T==NULL || (T != NULL && T->key == z)) return NULL;

	if ((T->right!=NULL && T->right->key == z) || (T->left!=NULL && T->left->key == z)) return T;
	
	if (z < T->key) return Father(T->left, z);
	else return Father(T->right, z);
}

tree* GrandFather(tree* T, int z) {
	if (T == Father(T, z) || Father(T, z) == NULL) return NULL;

	if (T->right == Father(T, z) || T->left == Father(T, z)) return T;
	
	if (z < T->key) return GrandFather(T->left, z);
	else return GrandFather(T->right, z);
}

tree* List(tree* T, int z) {
	if (T == NULL) return NULL;

	if (T->key == z) return T;
	else {
		if (z < T->key) return List(T->left, z);
		else return List(T->right, z);
	}
}

void LeftRotate(tree** T, int z) {
	tree* father = Father(*T, z);
	tree* grand_father = GrandFather(*T, z);
	tree* element = List(*T, z);

	if (grand_father == NULL) *T = element;
	else {
		if (grand_father->left == father) grand_father->left = element;
		else grand_father->right = element;
	}

	if (father != NULL && father->right->key == z) {
		father->right = element->left;
		element->left = father;
	}
}

void RightRotate(tree** T, int z) {
	tree* father = Father(*T, z);
	tree* grand_father = GrandFather(*T, z);
	tree* element = List(*T, z);

	if (grand_father == NULL) *T = element;
	else {
		if (grand_father->left == father) grand_father->left = element;
		else grand_father->right = element;
	}

	if (father != NULL && father->left->key == z) {
		father->left = element->right;
		element->right = father;
	}
}

tree* Balance(tree* T, int z) {
	tree* father = Father(T, z);
	tree* grand_father = GrandFather(T, z);
	tree* y;
	while (father != NULL && father->color == "RED" && List(T, z)->color=="RED") {
		if (grand_father != NULL && grand_father->left == father) {
			y = grand_father->right;

			if (y != NULL && y->color == "RED") {
				father->color = "BLACK";
				y->color = "BLACK";
				grand_father->color = "RED";
				z = grand_father->key;
				father = Father(T, z);
				grand_father = GrandFather(T, z);
			}
			else {
				if (father->right != NULL && father->right->key == z) {
					LeftRotate(&T, z);
					List(T, z)->color = "BLACK";
					Father(T, z)->color = "RED";
					RightRotate(&T, z);
				}
				else {
					RightRotate(&T, father->key);
					father->color = "BLACK";
					grand_father->color = "RED";
				}
			}
		}
		else {
			y = grand_father->left;

			if (y != NULL && y->color == "RED") {
				father->color = "BLACK";
				y->color = "BLACK";
				grand_father->color = "RED";
				z = grand_father->key;
				father = Father(T, z);
				grand_father = GrandFather(T, z);
			}
			else {
				if (father->left != NULL && father->left->key == z) {
					RightRotate(&T, z);
					List(T, z)->color = "BLACK";
					Father(T, z)->color = "RED";
					LeftRotate(&T, z);
				}
				else {
					LeftRotate(&T, father->key);
					father->color = "BLACK";
					grand_father->color = "RED";
				}
			}
		}
		Root(&T);
		father = Father(T, z);
		grand_father = GrandFather(T, z);
	}
	return T;
}

tree* AppendElement(int key) {
	tree* element = (tree*)malloc(sizeof(tree));
	if (element == NULL) {
		printf("Память не выделена.");
		return NULL;
	}
	element->color = "RED";
	element->key = key;
	element->left = NULL;;
	element->right = NULL;
	return element;
}

void AddElement(tree** T, int new_key) {
	if (*T == NULL) *T = AppendElement(new_key);
	else {
		if (new_key > (*T)->key) {
			if ((*T)->right == NULL) {
				(*T)->right = AppendElement(new_key);
			}
			else AddElement(&(*T)->right, new_key);
		}
		else if (new_key < (*T)->key) {
			if ((*T)->left == NULL) {
				(*T)->left = AppendElement(new_key);
			}
			else AddElement(&(*T)->left, new_key);
		}
	}
}

void PrintTree(tree* T, int n) {
	if (T != NULL) {
		PrintTree(T->right, n + 1);
		for (int i = 0; i < n; i++) printf(" ");
		printf("%i (%s)\n", T->key, T->color);
		PrintTree(T->left, n + 1);
	}
}

tree* CreateTree(tree* T) {
	int elem;
	scanf_s("%i", &elem);
	AddElement(&T, elem);
	Root(&T);
	T = Balance(T, elem);
	PrintTree(T, 0);
	return T;
}

tree* Delete(tree* T, int z) {
	tree* element = List(T, z);
	tree* father = Father(T, z);
	if (father != NULL && father->left == element) father->left = NULL;
	else if (father != NULL) father->right = NULL;
	if (father == NULL) return NULL;
	free(element);
	return T;
}

tree* DeleteLastBlack(tree* T, int z) {
	tree* element = List(T, z);
	tree* father = Father(T, z);

	if (father->color == "RED") {
		if (father->right == element) {
			T = Delete(T, z);
			father->color = "BLACK";
			if (father->left != NULL) {
				father->left->color = "RED";
				if (father->left->left != NULL) father->left->left->color = "BLACK";
				RightRotate(&T, father->left->key);
			}
		}
		else {
			T = Delete(T, z);
			father->color = "BLACK";
			if (father->right != NULL) {
				father->right->color = "RED";
				if (father->right->right != NULL) father->right->right->color = "BLACK";
				LeftRotate(&T, father->right->key);
			}
		}

	}
	else {
		father->color = "RED";
		if (father->right == element) {
			father->left->color = "BLACK";
			T = Delete(T, z);
			RightRotate(&T, father->left->key);
		}
		else {
			father->right->color = "BLACK";
			T = Delete(T, z);
			LeftRotate(&T, father->right->key);
		}
	}
	Root(&T);
	return T;
}

tree* MaxLeft(tree* T) {
	if (T->right == NULL) return T;
	else return MaxLeft(T->right);
}

tree* MinRight(tree* T) {
	if (T->left == NULL) return T;
	else return MinRight(T->left);
}

tree* DeleteBlack(tree* T, int z) {
	tree* element = List(T, z);

	if (element->left == NULL && element->right == NULL) T = DeleteLastBlack(T, z);
	else {
		tree* min_right = MinRight(element->right);
		tree* max_left = MaxLeft(element->left);
		if (min_right->color == "RED" || max_left->color == "RED") {
			if (min_right->color == "RED") {
				T = Delete(T, min_right->key);
				element->key = min_right->key;
			}
			else {
				T = Delete(T, max_left->key);
				element->key = max_left->key;
			}
		}
		else {
			if (min_right->left == NULL && min_right->right==NULL) {
				T = DeleteLastBlack(T, min_right->key);
				element->key = min_right->key;
			}
			else {
				if (max_left->left == NULL && max_left->right == NULL) {
					T = DeleteLastBlack(T, max_left->key);
					element->key = max_left->key;
				}
				else {
					T = DeleteBlack(T, min_right->key);
					element->key = min_right->key;
				}
			}
		}
	}
	return T;
}

tree* DeleteElement(tree* T, int z) {
	tree* element = List(T, z);

	if (element == NULL) {
		printf("The element was not found");
		return T;
	}

	if (element->color == "RED") {
		if (element->left == NULL && element->right == NULL) Delete(T, z);
		else {
			tree* min_right = MinRight(element->right);
			tree* max_left = MaxLeft(element->left);
			if (min_right->color == "RED" || max_left->color == "RED") {
				if (min_right->color == "RED") {
					T = Delete(T, min_right->key);
					element->key = min_right->key;
				}
				else {
					T = Delete(T, max_left->key);
					element->key = max_left->key;
				}
			}
			else {
				T = DeleteBlack(T, min_right->key);
				element->key = min_right->key;
			}
		}
	}
	else {
		if (element->left == NULL && element->right == NULL) T = DeleteLastBlack(T, z);
		else T = DeleteBlack(T, z);
	}

	Root(&T);
	return T;
}

tree* DeleteTree(tree* T) {
	int elem;
	scanf_s("%i", &elem);
	T = DeleteElement(T, elem);

	PrintTree(T, 0);

	return T;
}