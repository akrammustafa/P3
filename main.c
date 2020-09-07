#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 10 //a constant SIZE with the value 10.
// Akram MUSTAFA
// 150116905
/*-----------------------------------A------------------------------------------------------------*/
typedef struct MetroStation // definition the MetroStation struct
{
    char name[20];
    int x;
    int y;
} MetroStation;

typedef struct MetroLine   // definition the MetroLine struct
{
    char color[20];
    MetroStation MetroStations[SIZE];
} MetroLine;

typedef struct MetroSystem  // definition the MetroSystem struct
{
    char name[20];
    MetroLine MetroLines[SIZE];
} MetroSystem;

MetroSystem istanbul = {"istanbul", '\0'}; //a MetroSystem with named istanbul.
/*-----------------------------------A------------------------------------------------------------*/



/*-----------------------------------B------------------------------------------------------------*/
int equals (MetroStation s1, MetroStation s2);  //which returns a non-zero value if the name property of the MetroStation s1 is equal to the name property of MetroStation s2; zero otherwise

void addStation (MetroLine *line, MetroStation st); //array pointed by the MetroLine* pointer. It should return void.

int hasStation (MetroLine line, MetroStation st);  // if the given metro line has a metro station with the same name as the given metro station; zero otherwise.

MetroStation getFirstStop (MetroLine line);    // If there is no such station, your function should return an empty MetroStation.

MetroStation getPastStop (MetroLine line, MetroStation st);  //If the given station is the first stop on the MetroLine, then this function should return an empty MetroStation

MetroStation getNextStop (MetroLine line, MetroStation st);  // If the given station is the last stop on the MetroLine, then this function should return an empty MetroStation.

void addLine (MetroSystem *system, MetroLine line);  //adds the given metro line to the end of the MetroLines[] array pointed byMetroSystem pointer.

void printLine (MetroLine line); //prints metro line.

void printPath (MetroStation *stations); // prints the metro stations in the given array.

double getDistanceTravelled (MetroStation *path); // total distance travelled along a path that goes from the first MetroStation in the array,

MetroStation findNearestStation (MetroSystem system, double x, double y); // returns the MetroStation which is nearest to the x and y.

void getNeighboringStations (MetroSystem system, MetroStation station, MetroStation *neighboringStations); //fills the given neigboringStations array containing all neighboring stations to the given station

void findPath (MetroStation start, MetroStation finish, MetroStation *path); //call the recursiveFindPath function by passing to it as input start,finish, given MetroStation array path[]

void recursiveFindPath (MetroStation start, MetroStation finish, MetroStation *partialPath, MetroStation *bestPath);

MetroStation findNearestStation (MetroSystem system, double x, double y); // smallest distance away.

int equals (MetroStation s1, MetroStation s2)
{ //this function checks if the given metro stations same or not.

    if (!strcmp(s1.name, s2.name))
        return 1;

    return 0;
}

void addStation (MetroLine *line, MetroStation st)
{ //this adds given station to given line.
    int i = 0;
    while (line->MetroStations[i].name[0] != '\0')
    {
        i++;
    }
    line->MetroStations[i] = st;
}

int hasStation (MetroLine line, MetroStation st)
{ //this function checks if given line contains the given station or not.
    int i;
    for (i = 0; strlen(line.MetroStations[i].name) != 0; i++)
    {
        if (strcmp(line.MetroStations[i].name, st.name))
            return 1;
    }
    return 0;
}

MetroStation getFirstStop (MetroLine line)
{ //this function returns the first stop of given line
    return line.MetroStations[0];
}

MetroStation getPastStop (MetroLine line, MetroStation st)
{
    MetroStation mS;
    int i = 0; //function returns the station before the given station on given line.

    while (!strcmp(line.MetroStations[i].name, st.name))   i++;

    if (i != 0)
    {
        mS = line.MetroStations[i-1];
        return mS;
    }

    return mS;
}

MetroStation getNextStop (MetroLine line, MetroStation st)
{ //this function returns the station just after the given station on given line.
    MetroStation mS;
    int i = 0;

    while (!strcmp(line.MetroStations[i].name, st.name))   i++;

    if (i != SIZE - 1)
    {
        mS = line.MetroStations[i+1];
        return mS;
    }

    return mS;
} //if the given station is the last stop on the MetroLine, then this function should return an empty MetroStation.

void addLine (MetroSystem *system, MetroLine line)
{
    int i = 0;
    while (strlen(system->MetroLines[i].color) != 0)   i++;
    system->MetroLines[i] = line;
} // //adding the line to metro system.

void printLine (MetroLine line)
{
    int i;
    printf("Metroline %s: ", line.color);
    for (i = 0; i < 10; i++)
    {
        if (line.MetroStations[i].name[0] != '\0')
        {
            printf("%s ", line.MetroStations[i].name);
        }
        else
            continue;
    }
    puts("");
} //prints the stations of the line.

void printPath (MetroStation *stations)
{
    int i;
    for (i = 0; strlen(stations[i].name) != 0; i++)
    {
        printf("%d. %s\n", i+1, stations[i].name);
    }
} //prints the stations in path.

double getDistanceTravelled (MetroStation *path) // return double value to get the distance of traveled by path in array pointer from the first MetroStation
{
    double total = 0;
    int i, x, y;

    x = path[0].x;
    y = path[0].y;

    for (i = 1; i < sizeof(path); i++)
    {
        if (path[i].name == NULL)
        {
            if (i == 1)
                return 0;
            else
                break;
        }
        else
        {
            total += sqrt(pow(path[i].x - x, 2) + pow(path[i].y - y, 2));
            x = path[i].x;
            y = path[i].y;
        }
    }

    return total;
}

MetroStation findNearestStation (MetroSystem system, double x, double y)
{
    double distance;
    double temp;
    double nexX;
    double nexY;
    double mult1;
    double mult2;
    int i, j;
    MetroStation next, nearest;

    nearest = getFirstStop(system.MetroLines[0]);
    distance = sqrt(pow(getFirstStop(system.MetroLines[0]).x - x, 2) + pow(getFirstStop(system.MetroLines[0]).y - y, 2));
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            next = system.MetroLines[i].MetroStations[j];
            nexX = next.x; nexX -= x;
            nexY = next.y; nexY -= y;
            mult1 = nexX * nexX;
            mult2 = nexY * nexY;
            temp = mult1 + mult2;
            temp = sqrt(temp);
            if (next.name != NULL)
            {
                if (temp < distance)
                {
                    distance = temp;
                    nearest = next;
                }
            }
            else
                break;
        }
    }
    return nearest;
} //returns the MetroStation which is nearest to the x and y.

void getNeighboringStations (MetroSystem system, MetroStation station, MetroStation *neighboringStations)
{
    int i;
    int j;
    int x = 0;

    for (i = 0; strlen(system.MetroLines[i].color) != 0; i++)
    {
        for (j = 0; strlen(system.MetroLines[i].MetroStations[j].name) != 0; j++)
        {
            if (!strcmp(station.name, system.MetroLines[i].MetroStations[j].name))
            {
                if (!include(neighboringStations, system.MetroLines[i].MetroStations[j-1].name) && !include(neighboringStations, system.MetroLines[i].MetroStations[j+1].name)) {
                    if (j > 0)
                    {
                        neighboringStations[x++] = system.MetroLines[i].MetroStations[j - 1];
                        neighboringStations[x++] = system.MetroLines[i].MetroStations[j + 1];
                    }
                    else
                    {
                        neighboringStations[x++] = system.MetroLines[i].MetroStations[j + 1];
                    }

                }
            }
        }
    }
} //the function update the NeigBoringStations containing the MetroStation.

int include (MetroStation *arr, MetroStation stat)
{
    int i;
    for (i = 0; i < strlen(arr[i].name) != 0; i++)
    {
        if (!strcmp(arr[i].name, stat.name))
        {
            return 1;
        }

    }
    return 0;
} //if array including the station stat function return 1 else 0.

void findPath (MetroStation start, MetroStation finish, MetroStation *path)
{
    MetroStation partialPath[SIZE] = {'\0'};


    recursiveFindPath(start, finish, path, partialPath);
}  //finds the path with the help of recursiveFindPath function.

void recursiveFindPath (MetroStation start, MetroStation finish, MetroStation *partialPath, MetroStation *bestPath)
{
    int i;
    double distance = 10000;

    for (i = 0; i < SIZE; i++)
    {
        if (equals(partialPath[i], start))
            return;
    }

    if (equals(start, finish))
    {
        for (i = 0; i < SIZE; i++)
        {
            if (strlen(partialPath[i].name) < 5)
            {
                partialPath[i] = finish;
                break;
            }
        }
        for (i = 0; strlen(partialPath[i].name) != 0; i++)
        {
            strcpy(bestPath[i].name, partialPath[i].name);
            bestPath[i].x = partialPath[i].x;
            bestPath[i].y = partialPath[i].y;
        }
        return;
    }



    MetroStation neighbors[SIZE] = {'\0'};
    getNeighboringStations(istanbul, start, neighbors);

    MetroStation duplicatePath[SIZE] = {'\0'};
    for (i = 0; strlen(partialPath[i].name) != 0; i++)
    {
        strcpy(duplicatePath[i].name, partialPath[i].name);
        duplicatePath[i].x = partialPath[i].x;
        duplicatePath[i].y = partialPath[i].y;
    }

    for (i = 0; i < SIZE; i++)
    {
        if (strlen(duplicatePath[i].name) < 5)
        {
            duplicatePath[i] = start;
            break;
        }
    }

    for (i = 1; strlen(neighbors[i].name) != 0; i++)
    {
        if (!include(duplicatePath, neighbors[i]))
        {
            recursiveFindPath(neighbors[i], finish, duplicatePath, partialPath);
        }
        else
        {
            recursiveFindPath(neighbors[i+1], finish, duplicatePath, partialPath);
            i++;
        }

    }

    for (i = 0; strlen(duplicatePath[i].name) != 0; i++)
    {
        strcpy(partialPath[i].name, duplicatePath[i].name);
        partialPath[i].x = duplicatePath[i].x;
        partialPath[i].y = duplicatePath[i].y;
    }

    if (strlen(partialPath[0].name) != 0)
    {
        if (getDistanceTravelled(partialPath) < distance)
        {
            *bestPath = *partialPath;
        }
    }
}
/*-----------------------------------B------------------------------------------------------------*/


/*-----------------------------------C------------------------------------------------------------*/
int main()
{
    int i; double x=2, y=9; double targetX=60, targetY=35;

    MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
    MetroStation Station1,Station2,Station3,Station4,Station5,Station6,Station7,Station8;
    MetroStation myPath[SIZE]={'\0'};

    strcpy(red.color, "red"); // strcpy() function is used to copy string red.
    strcpy(blue.color, "blue"); // strcpy() function is used to copy string blue.
    strcpy(green.color, "green"); // strcpy() function is used to copy string green.


    strcpy(Station1.name, "Haydarpasa"); // strcpy() function is used to copy string Haydarpasa.
    Station1.x=0;    Station1.y=0; //source destinations.
    strcpy(Station2.name, "Sogutlucesme"); // strcpy() function is used to copy string Sogutlucesme.
    Station2.x=10;    Station2.y=5; //source destinations.
    strcpy(Station3.name, "Goztepe"); // strcpy() function is used to copy string Goztepe.
    Station3.x=20;    Station3.y=10; //source destinations.
    strcpy(Station4.name, "Kozyatagi"); // strcpy() function is used to copy string Kozyatagi.
    Station4.x=30;    Station4.y=35; //source destinations.
    strcpy(Station5.name, "Bostanci"); // strcpy() function is used to copy string Bostanci.
    Station5.x=45;    Station5.y=20; //source destinations.
    strcpy(Station6.name, "Kartal"); // strcpy() function is used to copy string Kartal.
    Station6.x=55;    Station6.y=20; //source destinations.
    strcpy(Station7.name, "Samandira"); // strcpy() function is used to copy string Samandira.
    Station7.x=60;    Station7.y=40; //source destinations.
    strcpy(Station8.name, "Icmeler"); // strcpy() function is used to copy string Icmeler.
    Station8.x=70;    Station8.y=15; //source destinations.

    //Adding the  red lines of metro stations: Metroline red: Haydarpasa, Sogutlucesme, Goztepe, Kozyatagi, Bostanci,
    //Icmeler..
    addStation(&red, Station1); addStation(&red, Station2);
    addStation(&red, Station3); addStation(&red, Station4);
    addStation(&red, Station5); addStation(&red, Station8);
    //Adding the  blue lines of metro stations: Metroline blue: Sogutlucesme, Goztepe, Kozyatagi, Kartal, Samandira.
    addStation(&blue, Station2); addStation(&blue, Station3);
    addStation(&blue, Station4); addStation(&blue, Station6);
    addStation(&blue, Station7);
    //Adding the  green lines of metro stations: Sogutlucesme, Goztepe, Bostanci, Kartal, Icmeler.
    addStation(&green, Station2); addStation(&green, Station3);
    addStation(&green, Station5); addStation(&green, Station6);
    addStation(&green, Station8);

    // Add  the colors of lines for istanbul metro system red,blue,green.
    addLine(&istanbul, red);
    addLine(&istanbul, blue);
    addLine(&istanbul, green);

    // print the content of the red, blue, green metro lines
    printLine(red);
    printLine(blue);
    printLine(green);

    MetroStation target = findNearestStation(istanbul, x, y);
    MetroStation targetGoal = findNearestStation(istanbul, targetX, targetY);

    printf("\n");

    printf("The best path from %s to %s is:\n", target.name, targetGoal.name);

    findPath(target, targetGoal, myPath);

    if(strlen(myPath[0].name) == 0)
        printf("There is no path and line for the metro!\n"); //if myPath =0 there is no line and print nothing
    else{
        printPath(myPath);  // print
    }
    return 0;
}