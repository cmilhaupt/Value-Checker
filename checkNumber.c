#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct node {
	int flag;
	struct node * left;
	struct node * right;
};

void insertIntoTree(int * binary, struct node * parent, int i) {
	if(i == -1)
		return;
	if (i == 0) {
		parent->flag = 1;
		return;
	}
	if(binary[i]== 0) {
		if(parent->left == NULL) {
			parent->left = malloc(sizeof(struct node));
			parent->left->flag = 0;
			parent->left->left = NULL;
			parent->left->right = NULL;
		}
		return insertIntoTree(binary, parent->left, i - 1);
	} else if (binary[i] == 1) {
		if(parent->right == NULL) {
			parent->right = malloc(sizeof(struct node));
			parent->right->flag = 0;
			parent->right->left = NULL;
			parent->right->right = NULL;
		}
		return insertIntoTree(binary, parent->right, i - 1);
	} else
		fprintf(stderr, "invalid digit: %d\n", binary[i]);
}

int * numberToBinary(int num, int places) {
	int * binary = malloc(sizeof(int)*places);
	int i = places - 1;
	while (num != 0 ) {
		if ((num % 2) == 1)
			binary[i--] = 1;
		else
			binary[i--] = 0;

		num /= 2;
	}
	return binary;
}

int inTree(int * check, struct node * parent, int i) {
	if (i == -1)
		return 0;
	if(check[i] == 0) {
		if(i == 0 && parent->flag == 1)
			return 1;
		if(parent->left == NULL)
			return 0;
		return inTree(check, parent->left, i - 1);
	} 
	
	if(check[i] == 1) {
		if(i == 0 && parent->flag == 1)
			return 1;
		if (parent->right == NULL)
			return 0;
		return inTree(check, parent->right, i - 1);
	}

}

void removeNode (struct node * node) {
	if(node == NULL)
	 return;
	if(node->left != NULL)
		removeNode(node->left);
	if(node->right != NULL)
		removeNode(node->right);
	free(node);
}

int main(int argc, char ** argv) {
	//check if numbers exist from huge file
	//build trie
	FILE *fp = fopen(argv[2], "r");
	int num = 0;
	fscanf(fp, "%d", &num);
	struct node * head = malloc(sizeof(struct node));
	head->flag = 2;
	head->left = NULL;
	head->right = NULL;

	printf("Building tree...\n");
	while(!feof(fp)) {
		//convert the number to binary
		//insert each byte char into the tree
		int places = (int)ceil(log((double)num)/log(2));
		int * binary = numberToBinary(num, places);
	
		insertIntoTree(binary, head, places - 1);
		
		free(binary);
	
		//get next int
		fscanf(fp, "%d", &num);
	}
	
	int places = (int)ceil(log((double)atoi(argv[1]))/log(2));
	int * check = numberToBinary(atoi(argv[1]), places);

	printf("Checking for value ");
	for (int i = 0; i < places; i++)
		printf("%d", check[i]);
	printf(" in tree\n");
	int value = inTree(check, head, places - 1);

	printf("%s\n", (value == 1)?"Value found in file!":"Value not in file.");
	
	fclose(fp);
	removeNode(head);


	return 0;
}
