#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
// void removeProduct(struct Library *library);

COORD coord= {0,0};                  // this is global variable
//center of axis is set to the top left cornor of the screen
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
struct Product
{
    char Pname[50];
    int quantity;
    int price;
};

struct Category
{
    char Cname[50];
    struct Product products[100];
    int productCount;
};

struct Library
{
    struct Category categories[70];
    int categoryCount;
};
void initialize(struct Library *library)
{
    library->categoryCount = 2;
    strcpy(library->categories[0].Cname,"ScienceFiction");
    library->categories[0].productCount = 3;
    strcpy(library->categories[0].products[0].Pname,"Neuromancer ");
    library->categories[0].products[0].price = 200;
    library->categories[0].products[0].quantity = 100;

    strcpy(library->categories[0].products[1].Pname, "Ender's Game");
    library->categories[0].products[1].price = 100;
    library->categories[0].products[1].quantity = 50;
   strcpy(library->categories[0].products[0].Pname,"Neuromancer ");
    library->categories[0].products[0].price = 200;
    library->categories[0].products[0].quantity = 100;


   strcpy(library->categories[1].Cname,"Children'sBooks");
    library->categories[1].productCount = 3;
    strcpy(library->categories[1].products[0].Pname, "Harry Potter");
    library->categories[1].products[0].price = 200;
    library->categories[1].products[0].quantity = 100;
    strcpy(library->categories[1].products[1].Pname, "Charlie and the Chocolate Factory");
    library->categories[1].products[1].price = 300;
    library->categories[1].products[1].quantity = 90;
    strcpy(library->categories[1].products[1].Pname, "Charlie and the Chocolate Factory");
    library->categories[1].products[1].price = 300;
    library->categories[1].products[1].quantity = 90;

}

void display(const struct Library *library)
{
    for (int i = 0; i < library->categoryCount; i++)
    {
        printf("\n\n");
        printf("*************************************************************************************************************");
        printf("\n");
        printf("%d -> Category   %s \n",i+1, library->categories[i].Cname);
        for (int j = 0; j < library->categories[i].productCount; j++)
        {
            printf("    %d-  books    %s          ||  price :    %d\t          || quantity :   %d\t",j+1,library->categories[i].products[j].Pname,library->categories[i].products[j].price,library->categories[i].products[j].quantity);

            printf("  \n");
        }

    }
}
void addCategory(struct Library *library)
{
    if (library->categoryCount < 10)
    {
        char categoryName[50];
        printf("\t\t\t\t->  Enter category name: ");
        scanf("%s", categoryName);

        struct Category newCategory;
        strcpy(newCategory.Cname, categoryName);
        newCategory.productCount = 0;

        library->categories[library->categoryCount] = newCategory;
        library->categoryCount++;
        printf("\t\t\t\t-------Category added-------\n");
    }
    else
    {
        printf("\t\t\t\t  Category limit reached.\n");
    }
}
void removeCategory(struct Library *library)
{
    if (library->categoryCount > 0)
    {
        char categoryName[50];
        printf("\t\t\t\t->  Enter category name to remove: ");
        scanf("%s", categoryName);

        int i;
        for (i = 0; i < library->categoryCount; i++)
        {
            if (strcmp(library->categories[i].Cname, categoryName) == 0)
            {
                break;
            }
        }

        if (i < library->categoryCount)
        {
            for (int j = i; j < library->categoryCount - 1; j++)
            {
                library->categories[j] = library->categories[j + 1];
            }
            library->categoryCount--;

            printf("\t\t\t\t->  -----Category removed----------\n");
        }
        else
        {
            printf("\t\t\t\t->  Category not found.\n");
        }
    }
    else
    {
        printf("\t\t\t\t->  No categories available.\n");
    }
}
void addProduct(struct Library* library)
{
    char Pname[20], Cname[20];
    int price, quantity;
    printf("\t\t\t\t->  Enter category name: ");
    scanf("%s", Cname);
    int Cindex = -1;
    for (int i = 0; i < library->categoryCount; i++)
    {
        if (strcmp(library->categories[i].Cname, Cname) == 0)
        {
            Cindex = i;
            break;
        }
    }

    if (Cindex != -1)
    {
        printf("\t\t\t\t->  Enter product name: ");
        scanf("%s", Pname);

        int Pindex = -1;
        for (int i = 0; i < library->categories[Cindex].productCount; i++)
        {
            if (strcmp(library->categories[Cindex].products[i].Pname, Pname) == 0)
            {
                Pindex = i;
                break;
            }
        }

        if (Pindex == -1)
        {

            printf("\t\t\t\t->  Enter price: ");
            scanf("%d", &price);
            while (price < 0)
            {
                printf("\t\t\t\t  Invalid price.\nPlease enter a non-negative value: ");
                scanf("%d", &price);
            }

            printf("\t\t\t\t->  Enter quantity: ");
            scanf("%d", &quantity);
            while (quantity < 0)
            {
                printf("\t\t\t\t   Invalid quantity.\t Please enter a non-negative value: ");
                scanf("%d", &quantity);
            }

            strcpy(library->categories[Cindex].products[library->categories[Cindex].productCount].Pname, Pname);
            library->categories[Cindex].products[library->categories[Cindex].productCount].price = price;
            library->categories[Cindex].products[library->categories[Cindex].productCount].quantity = quantity;

            library->categories[Cindex].productCount++;
            printf("\t\t\t\t-> -------Product added successfully---------------\n");
        }
        else
        {
            printf("\t\t\t\t->  Product already exists.\n");
        }
    }
    else
    {
        printf("\t\t\t\t->  Category not found.\n");
    }
}


void RemoveProduct(struct Library *library)
{
    char Cname[50], Pname[20];
    printf("\t\t\t\t-> Enter category name: ");
    scanf("%s", Cname);
    int Cindex = -1;
    for (int i = 0; i < library->categoryCount; i++)
    {
        if (strcmp(library->categories[i].Cname, Cname) == 0)
        {
            Cindex = i;
            break;
        }
    }
    if (Cindex != -1)
    {
        printf("\t\t\t\t-> Enter product name: ");
        scanf("%s", Pname);
        int Pindex = -1;
        for (int i = 0; i < library->categories[Cindex].productCount; i++)
        {
            if (strcmp(library->categories[Cindex].products[i].Pname, Pname) == 0)
            {
                Pindex = i;
                break;
            }
        }
        if (Pindex != -1)
        {
            for (int i = Pindex; i < library->categories[Cindex].productCount - 1; i++)
            {
                library->categories[Cindex].products[i] = library->categories[Cindex].products[i + 1];
            }
            library->categories[Cindex].productCount--;
            printf("\t\t\t\t-> ---------Product removed-----------\n");
        }
        else
        {
            printf("\t\t\t\t-> Product not found.\n");
        }
    }
    else
    {
        printf("\t\t\t\t-> Category not found.\n");
    }
}


void SellProduct(struct Library *library)
{
    char Cname[20], Pname[20];
    printf("\t\t\t\t->  Enter category name: ");
    scanf("%s", Cname);
    int Cindex = -1;
    for (int i = 0; i < library->categoryCount; i++)
    {
        if (strcmp(library->categories[i].Cname, Cname) == 0)
        {
            Cindex = i;
            break;
        }
    }
    if (Cindex != -1)
    {
        printf("\t\t\t\t->  Enter book name: ");
        scanf("%s", Pname);
        int Pindex = -1;
        for (int i = 0; i < library->categories[Cindex].productCount; i++)
        {
            if (strcmp(library->categories[Cindex].products[i].Pname, Pname) == 0)
            {
                Pindex = i;
                break;
            }
        }
        if (Pindex != -1)
        {
            int quantity, price;
            printf("\t\t\t\t->  Enter quantity : ");
            scanf("%d", &quantity);


            if (library->categories[Cindex].products[Pindex].quantity >= quantity)
            {
                library->categories[Cindex].products[Pindex].quantity -= quantity;
                printf("\n");
                printf("\t\t\t\t->  book sold\n");
                printf("\t\t\t\t->  the Remaining  Quantity %d\n",library->categories[Cindex].products[Pindex].quantity);
                printf("\t\t\t\t->  Total price %d\n",library->categories[Cindex].products[Pindex].price*quantity);
                printf("\n");
                printf("\t\t\t\t  *******Let me see you again*********");

                if(library->categories[Cindex].products[Pindex].quantity==0)
                {
                    for (int i = Pindex; i < library->categories[Cindex].productCount -1; i++)
                    {
                        library->categories[Cindex].products[i]= library->categories[Cindex].products[i+1] ;
                    }

                    library->categories[Cindex].productCount--;
                }
            }
        else
        {
            printf("\t\t\t\t->  quantity not enough.\n");
        }
        }
        else
        {
            printf("\t\t\t\t->  book  not found.\n");
        }
    }
    else
    {
        printf("\t\t\t\t->  Category not found.\n");
    }
}

void moveandupdate(struct Library *library)
{
    char Pname[20], sourceCatName[20], destinationCatName[20];
    printf("\t\t\t\t->  Enter source category name: ");
    scanf("%s", sourceCatName);
    int sourceIndex = -1;
    for (int i = 0; i < library->categoryCount; i++)
    {
        if (strcmp(library->categories[i].Cname, sourceCatName) == 0)
        {
            sourceIndex = i;
            break;
        }
    }

    if (sourceIndex != -1)
    {
        printf("\t\t\t\t->  Enter book name: ");
        scanf("%s", Pname);

        int productIndex = -1;
        for (int i = 0; i < library->categories[sourceIndex].productCount; i++)
        {
            if (strcmp(library->categories[sourceIndex].products[i].Pname, Pname) == 0)
            {
                productIndex = i;
                break;
            }
        }

        if (productIndex != -1)
        {
            printf("\t\t\t\t->  Enter destination category name: ");
            scanf("%s", destinationCatName);

            int destinationIndex = -1;
            for (int i = 0; i < library->categoryCount; i++)
            {
                if (strcmp(library->categories[i].Cname, destinationCatName) == 0)
                {
                    destinationIndex = i;
                    break;
                }
            }

            if (destinationIndex != -1)
            {
                if (library->categories[destinationIndex].productCount < 10)
                {
                    struct Product movedProduct = library->categories[sourceIndex].products[productIndex];

                    for (int i = productIndex; i < library->categories[sourceIndex].productCount - 1; i++)
                    {
                        library->categories[sourceIndex].products[i] = library->categories[sourceIndex].products[i + 1];
                    }
                    library->categories[sourceIndex].productCount--;
                    library->categories[destinationIndex].products[library->categories[destinationIndex].productCount] = movedProduct;
                    library->categories[destinationIndex].productCount++;
                    printf("\t\t\t\t->  --------book moved successfully-------------\n");

                }
                else
                {
                    printf("\t\t\t\t->  Destination category has reached its product limit.\n");
                }
            }
            else
            {
                printf("\t\t\t\t->  Destination category not found.\n");
            }
        }
        else
        {
            printf("\t\t\t\t->  book not found in the source category.\n");
        }
    }
    else
    {
        printf("\t\t\t\t->  Source category not found.\n");
    }
}





int main()
{
    struct Library library;
    initialize(&library);
    int selector=0;
    while(1)
    {
        gotoxy(5,3);
        if (selector==0)
        {

            SetColor(44);
            printf("\t\t\t\t-> DISPLAY LIBRAAY");
            SetColor(22);

        }
        else
        {
            printf("\t\t\t\t-> DISPLAY LIBRAAY");
        }
        gotoxy(5,4);
        if (selector==1)
        {
            SetColor(44);
            printf("\t\t\t\t-> ADD  CATEGORY");
            SetColor(22);

        }
        else
        {
            printf("\t\t\t\t-> ADD  CATEGORY");
        }
        gotoxy(5,5);
        if (selector==2)
        {
            SetColor(44);
            printf("\t\t\t\t-> REMOVE CATEGRY");
            SetColor(22);
        }
        else
        {
            printf("\t\t\t\t-> REMOVE CATEGRY");
        }
        gotoxy(5,6);
        if (selector==3)
        {
            SetColor(44);
            printf("\t\t\t\t-> ADD BOOK");
            SetColor(22);
        }
        else
        {
            printf("\t\t\t\t-> ADD BOOK");
        }
        gotoxy(5,7);
        if (selector==4)
        {
            SetColor(44);
            printf("\t\t\t\t-> REMOVE BOOK");
            SetColor(22);
        }
        else
        {
            printf("\t\t\t\t-> REMOVE BOOK");
        }
        gotoxy(5,8);
        if (selector==5)
        {
            SetColor(44);
            printf("\t\t\t\t-> MOVE BOOK");
            SetColor(22);
        }
        else
        {
            printf("\t\t\t\t-> MOVE BOOK");
        }

        gotoxy(5,9);
        if (selector==6)
        {

            SetColor(44);
            printf("\t\t\t\t-> SELL BOOK");
            SetColor(22);

        }
        else
        {
            printf("\t\t\t\t-> SELL BOOK");
        }

        gotoxy(5,10);
        if (selector==7)
        {
            SetColor(44);
            printf("\t\t\t\t-> EXIT");
            SetColor(22);

        }
        else
        {
            printf("\t\t\t\t-> EXIT");
        }
        char key;
        key=_getch();
        switch(key)
        {
        case 72:
            if (selector<=0)
            {
                selector=7;

            }
            else
            {
                selector--;
            }
            break;
        case 80:
            if (selector>=7)
            {
                selector=0;

            }
            else
            {
                selector++;
            }
            break;
        case 13:
            switch(selector)
            {
            case 0:
                system("cls");
                display(&library);
                _getch();
                system("cls");
                break;

            case 1:
                system("cls");
                addCategory(&library);
                _getch();
                system("cls");
                break;
            case 2:
                system("cls");
                removeCategory(&library);
                _getch();
                system("cls");
                break;
            case 3:
                system("cls");
                addProduct(&library);
                _getch();
                system("cls");
                break;

            case 4:
                system("cls");
                RemoveProduct(&library);
                _getch();
                system("cls");
                break;

            case 5:
                system("cls");
                moveandupdate(&library);
                _getch();
                system("cls");
                break;

            case 6:
                system("cls");
                SellProduct(&library);
                _getch();
                system("cls");
                break;

            case 7:
                system("cls");
                break;

            }

        }

    }

    return 0;
}
