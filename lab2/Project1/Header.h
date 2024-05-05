#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct tree {
	int key;
	char* color;
	struct tree* left;
	struct tree* right;
} tree;

tree* AppendElement(int key);
void AddElement(tree** T, int new_key);
tree* Balance(tree* T, int z);
tree* GrandFather(tree* T, int z);
tree* Father(tree* T, int z);
void PrintTree(tree* T, int n);
void LeftRotate(tree** T, int z);
void RightRotate(tree** T, int z);
tree* List(tree* T, int z);
void Root(tree** T);
tree* CreateTree(tree* T);

tree* Delete(tree* T, int z);
tree* DeleteElement(tree* T, int z);
tree* DeleteTree(tree* T);
tree* MaxLeft(tree* T);
tree* MinRight(tree* T);
tree* DeleteLastBlack(tree* T, int z);
tree* DeleteBlack(tree* T, int z);
