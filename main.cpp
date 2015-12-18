#include <iostream>
#include <string.h>
#include <fstream>
#include <graphics.h>
using namespace std;
ifstream fin("aplicatie.in");   //  contains the assigned numbers of the cities and the distance (weight) between them
ifstream f("orase.in");         //  contains the number of cities and the names
int const MAX = 5000;
int a[100][100], n, x1, y1, z1, m;
char s[20][20];

//read from the file that contains the cities
void citire1()
{
    f >> m;
    int i = 1;
    while (f >> s[i])
        i++;
}

//initialize the matrix of distances
void init ()
{
    int i, j;
    fin >> n;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (i == j)
                a[i][j] = 0;
            else a[i][j] = MAX;
}

// read the weighted graph and create the matrix of distances (c)
void citire ()
{
    int i, j, c;
    while (fin >> i>> j >> c)
        a[i][j] = c;
}

//print the matrix
void afisare ()
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}

//Roy-Floyd Algorithm implementation
void roy_floyd ()
{
    int i, j, k;
    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if(a[i][k] + a[k][j] < a[i][j])
                    a[i][j] = a[i][k] + a[k][j];
}

//compare the user's input(strings x,y,z) to the names in the file(orase.in) and pick the corresponding value
int citire_matrice(char* x, char* y, char* z)
{
    int i;
    for(i = 1; i <= m; i++)
        if(strcmp(s[i], x) == 0)
            x1 = i;
        else if (strcmp(s[i], y) == 0)
            y1 = i;
        else if (strcmp(s[i], z) == 0)
            z1 = i;
}

//search for a path between two cities and print the cities in-between the two
void drum (int i, int j)
{
    int k = 1, gasit = 0;

    while ( k <= n && gasit == 0)
    {
        if (k != i && k != j && a[i][j] == a[i][k] + a[k][j])
        {
            gasit = 1;
            drum (i, k);
            drum (k, j);
        }
        k++;
    }
    if (gasit == 0)
    {
        for (int w=1; w <= m; w++)
            if (j==w)
                cout << s[w] << " ";
    }
}

// user menu
void variante ()
{
    cout << "1 - Lenght of the road" << endl;
    cout << "2 - Cities travelled by train" << endl;
    cout << "3 - Building a Las Vegas connection" << endl;
    cout << "4 - The cost of a ticket" << endl;
    cout << "5 - The matrix of minimum weights(academic)\n";
    cout << "6 - Purchase ticket\n";
    cout << "7 - Exit \n";
}

int main()
{
    int var;
    char x[20], y[20], z[20];
    float pret;
    citire1();
    init();
    citire();
    roy_floyd();
    //afisare();
    variante();
    cout << "Pick an option: ";
    cin >> var;
    if (var != 7)
        system("cls");

    // Option 1
    if (var == 1)
    {

        cout << "Leaving from: ";
        cin >> x;
        cout << "Destination: ";
        cin >> y;
        cout << "If you wish to link with a certain city,"<< endl;
        cout << "type the name, otherwise, type 0." << endl;
        cout << "Linking city: ";
        cin >> z;


        citire_matrice(x, y, z);
        if (z1 == 0)
            z1 = y1;

        cout << x1 << " ";
        cout << y1 << " ";
        cout << z1;
        if (a[x1][z1] + a[z1][y1] < MAX )
            cout << "The distance travelled by train: " << a[x1][z1] + a[z1][y1]<< " km." << endl;
        else
            cout << "This journey is not available. " << endl;

    }

    // Option 2
    if (var == 2)
    {
        cout << "Leaving from: ";
        cin >> x;
        cout << "Destination: ";
        cin >> y;
        citire_matrice(x, y, z);
        cout << x1 << " ";

        cout << y1 << " ";
        //citire z aici
        cout << "The train passes through the following cities: ";
        drum(x1, y1);

    }

    // Option 3
    if (var == 3)
    {
        cout << "Leaving from: ";
        cin >> x;
        cout << "Linking cities are: Palmdale, Bakersfield, Los Angeles, Riverside" << endl;


        cout << "Chosen linking city: ";
        cin >> z;

        //cout << "Orasul destinatie: ";
        //cin >> y;
        citire_matrice(x, y, z);
        //citire z aici
        cout << x1 << y1 << z1 << endl;
        if (z1 != 9 && z1 != 10 && z1 != 8 && z1 != 13)
            cout << "Linking cities are: Palmdale, Bakersfield, LosAngeles si Riverside" << endl;
        else if (a[x1][z1] + a[z1][19] < MAX)
            cout << "Distance to Las Vegas: " << a[x1][z1] + a[z1][19] << " km." << endl;
        else cout << "There isn't a connection to L.V." ;


    }

    // Option 4
    if (var == 4)
    {
        cout << "Please complete the following data:" << endl;
        cout << "Leaving from: " ;
        cin >> x;
        cout << "Destination: " ;
        cin >> y;
        citire_matrice(x, y, z);
        pret = 0.25 * a[x1][y1];
        cout << "Ticket price (adult): " << pret << " USD" << endl;
        cout << "Ticket price (children): "<< pret/10 << " USD" << endl;
        cout << "Ticket price (student): " << pret/2 << " USD" << endl;
    }

    // Option 5
    if (var == 5)
    {
        afisare();
    }

    // Option 6
    if (var == 6)
    {
        int gd = DETECT, gm, font=0;
        char str[20], str2[20];
        initgraph(&gd, &gm, "C:\\TC\\BGI");
        cout << "Leaving from: ";
        cin >> x;
        cout << "Destination: ";
        cin >> y;
        citire_matrice(x, y, z);
        pret = 0.25 * a[x1][y1];

        setfillstyle(SOLID_LINE, RED);
        rectangle(10, 10, 410, 130);
        setcolor(GREEN);
        outtextxy(15, 15, "Journey card - SC CaliforniaTrans SRL");
        setcolor(WHITE);
        outtextxy(15, 32, "Leaving from: ");
        outtextxy(100, 32, x);
        outtextxy(15, 50, "Destination: ");
        outtextxy(100, 50, y);
        outtextxy(15, 68, "Distance: ");

        sprintf(str, "%d", a[x1][y1]);
        outtextxy(80, 68, str);
        outtextxy(105, 68, "km");
        sprintf(str2, "%d", (int) pret);
        settextstyle(font, HORIZ_DIR, 4);
        outtextxy(15, 90, "Pret: ");
        outtextxy(205, 90, str2);
        outtextxy(305, 90, "USD");

        int maxX = getmaxx();
        for (int in = 0; in < maxX; in++)   //  train movement
        {

            //Animation
            //Road
            setcolor(DARKGRAY);
            line (0, 370, maxX, 370);

            //Train
            setcolor(RED);
            rectangle(100+in, 300, 200+in, 350);
            circle(120+in, 360, 10);
            circle(180+in, 360, 10);
            if(in == 0)
            {

                settextstyle(font, HORIZ_DIR, 1);
                outtextxy(200, 400, "Press any button to print.");
                getch();
            }
            settextstyle(font, HORIZ_DIR, 1);
            setcolor(GREEN);
            rectangle (525, 250, 535, 370);
            rectangle (480, 200, 580, 250);
            outtextxy(490, 220, "Thank you!");
            settextstyle(font, HORIZ_DIR, 2);
            outtextxy(200, 400, "Printing in progress.");

            delay(20);
            cleardevice();

        }
        getch();
        closegraph();

    }
    return 0;
}
