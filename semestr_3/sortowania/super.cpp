#include <stdio.h>
#include <malloc.h>
struct element
{
	int k;
	struct element *left;
	struct element *right;
	struct element *parent;
};

void inorder(struct element *x)			// porz¹dek inorder
{
	if (x!=NULL) 
		{
			inorder(x->left);
			printf("%d ",x->k);
			inorder(x->right);
	}
}
void postorder (struct element*x)		// porz¹dek postorder
{
	if (x!=NULL)
		{
			postorder(x->left);
			postorder(x->right);
			printf(" %d ",x->k);
		}
}


void preorder (struct element*x)		// porz¹dek preorder
{
	if (x!=NULL)
		{
			printf("%d ",x->k);
			preorder(x->left);
			preorder(x->right);
		}
}


struct element *wstaw(struct element *root, struct element *z)		//wstawianie
			{
				struct element *y=NULL, *x=root;
				while(x!=NULL)
					{
						y=x;
						if(z->k<x->k)
						x=x->left;
						else x=x->right;
					}
						z->parent=y;
						if(y==NULL)
						root=z;
						else if(z->k<y->k)
						y->left=z;
						else y->right=z;
						return root;
			}

struct element *min(struct element *x)			//element minimalny
{
	while(x->left!=NULL)
		x=x->left;
	return x;
}

struct element *max(struct element *x)			//element maksymalny
{
	while(x->right!=NULL)
	x=x->right;
	return x;
}
struct element *nastepnik(struct element *x)		//nastêpnik
{
	struct element *y;
	if(x->right!=NULL)
	return min(x->right);
	y=x->parent;
	while(y!=NULL&&x==y->right)
	{
		x=y;
		y=y->parent;
	}
	return y;
}

struct element *poprzednik(struct element *x)		//poprzednik
{
	struct element *y;
	if(x->left!=NULL)
	return max(x->left);
	y=x->parent;
	while(y!=NULL&&x==y->left)
	{
		x=y;
		y=y->parent;
	}
	return y;
}

struct element *szukaj(struct element *x, int k)		//szukanie
{
       while(x!=NULL&&k!=x->k)
       {
                              if(k<x->k)
                              x=x->left;
                              else x=x->right;
                              }
       return x;
       }
void usun(struct element *root, struct element *x)
{
	if(root)
	{
		if(x->left)
		{
			if(x->right)
			{
				
			}
			else
			{
				if(x->parent->left==x)
				{
					x->left->parent=x->parent;
					x->parent->left=x->left;
				}
				else
				{
					x->left->parent=x->parent;
					x->parent->right=x->left;
				}			
			}
		}
		else
			if(x->right)
			{
				if(x->parent->left==x)
				{
					x->right->parent=x->parent;
					x->parent->left=x->right;
				}
				else
				{
					x->right->parent=x->parent;
					x->parent->right=x->right;
				}
			}
			else
			{
				if(x->parent->left==x)
					x->parent->left=NULL;
				else
					x->parent->right=NULL;
			}
	}
	else
	root=NULL;
	free(x);
}
float srednia(struct element *x)
	{
		int skladnik1=nastepnik(nastepnik(min(x)))->k;
		int skladnik2=poprzednik(poprzednik(max(x)))->k;
		float srednia=(skladnik1+skladnik2)/2.0;
		return srednia;
	}
	
int suma( struct element *root)
{
    if(root)
        return  root->k+ suma(root->left)+suma(root->right);
}

int ilosc(struct element *root)
{
    if(root)
    {
        return (1+ilosc(root->left)+ilosc(root->right));

    }
}

int main()
{
	struct element *root=NULL, *nowy=NULL;
	char z;
	int liczba;
	while(1)
	{
		
        printf("Co chcesz zrobic?");
		printf("\n0 - Dodac");
		printf("\n1 - Szukac");
		printf("\n2 - Usunac");
		printf("\n3 - Wystwietlic metoda inorder");
		printf("\n4 - Wystwietlic metoda postorder");
		printf("\n5 - Wystwietlic metoda preorder");
		printf("\n6 - Wyswietlic najmniejszy");
		printf("\n7 - Wyswietlic najwiekszy");
		printf("\n8 - Podac nastepnik");
		printf("\n9 - Podac poprzednik");
		printf("\n9 - funkcja1");
		printf("\n9 - funkcja2");
		fflush(stdin);
		printf("\nWybor: ");
        z=getchar();
		switch(z)
		{
		case '0': 
			nowy=(struct element*) malloc(sizeof(struct element));
			printf("\nPodaj wartosc do wstawienia: ");
			scanf("%d",&liczba);
			nowy->k=liczba;
			nowy->left=NULL;
			nowy->right=NULL;
			root=wstaw(root,nowy);
			break;
		case '1':
             printf("\nPodaj wartosc do znalezienia: ");
             scanf("%d",&liczba);
             nowy=szukaj(root,liczba);
             fflush(stdin);
             if(nowy==NULL)
             {
                           printf("\nNie znaleziono elemenu w drzewie.");
                           getchar();
                           }
             else
             {
                 printf("\nSzukany element znajduje sie w drzewie.");
                 getchar();
                 }
             break;
		case '3':
			if(root==NULL) printf("\nDrzewo puste");
			else
			inorder(root);
			fflush(stdin);
			getchar();
			break;
		case '4':
			if(root==NULL) printf("\nDrzewo puste");
			else
			postorder(root);
			fflush(stdin);
			getchar();
			break;
		case '5':
			if(root==NULL) printf("\nDrzewo puste");
			else
			preorder(root);
			fflush(stdin);
			getchar();
			break;
		case '2':
			printf("\nPodaj element do usuniecia ");
			scanf("%d",&liczba);
			nowy=szukaj(root,liczba);
			fflush(stdin);
			if(nowy==NULL)
            {
                           printf("\nNie znaleziono elementu do usuniecia");
                           getchar();
                           }
			else 
            {
                 usun(root,nowy);
                 printf("\nElement usuniety");
                 }
			getchar();
			break;
		case '6':
			if(root==NULL) printf("\nDrzewo puste");
			else
			printf("%d", (min(root))->k);
			fflush(stdin);
			getchar();
			break;
		case '7':
			if(root==NULL) printf("\nDrzewo puste");
			else
			printf("%d", (max(root))->k);
			fflush(stdin);
			getchar();
			break;
		case '8':
			if(root==NULL) printf("\nDrzewo puste");
			else
			printf("czego nastepnik?\n");
			scanf("%d", &liczba);
			nowy= szukaj(root,liczba);
			nowy=nastepnik(nowy);
			if(nowy)
			printf("%d", nowy->k);
			else
			printf("nie ma");
			fflush(stdin);
			getchar();
			break;
		case '9':
			if(root==NULL) printf("\nDrzewo puste");
			else
			printf("czego poprzednik?\n");
			scanf("%d", &liczba);
			nowy= szukaj(root,liczba);
			nowy=poprzednik(nowy);
			if(nowy)
			printf("%d", nowy->k);
			else
			printf("nie ma");
			fflush(stdin);
			getchar();
			break;
		case 'a':
			printf("srednia1 jest rowna=%f" ,srednia(root));
			fflush(stdin);
			getchar();
			break;
		case 'b':
			float k;
			k=(float(suma(root))/(float(ilosc(root))));
			printf("srednia2 jest rowna=%f", k);
			fflush(stdin);
			getchar();
			break;
		case 'q': return 0;
		}
	}
	

}

