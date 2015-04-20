#include <iostream>
#include <stdlib.h>

using namespace std;

int n, i, j, k, amount, alive_count, alive_count_total, amount_first, died_count, born_count; // counters
int right_view, left_view, up_view, down_view; // coordinates of the view
long long steps, vx, vy;
bool left_up, right_down; // check if the field needs to be enlarged
char answer; // user's answers to the quesions

int main() {
    cout << "Hometask #2. Life." << endl << "Written by Roman Samokhvalov, 1536." << endl << endl;
    cout << "Please, enter the size of the start position (n x n)." << endl;
    cin >> n;
    cout << "Please, enter the amount of the creatures at the first step of the simulation." << endl;
    cin >> amount;
    amount_first = amount;
    cout << "Please, enter the amount of steps of the simulation." << endl;
    cin >> steps;
    bool** the_field = new bool*[n];
    for (i = 0; i < n; i++)
        the_field[i] = new bool[n];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            the_field[i][j] = false;
        }
    }
    cout << "Would you like to set the position for every creature (" << amount << " ones) (y/n)? ";
    cin >> answer;
    if (answer == 'y') {
        for (i = 0; i < amount; i++) {
            cout << endl << endl << "Enter the coordinates for creature #" << i + 1 << ":" << endl;
            cout <<"x = ";
            cin >> vx;
            cout <<"y = ";
            cin >> vy;
            if ((vx < n) && (vy < n) && (vx >= 0) && (vy >= 0)) {
                if (the_field[vy][vx] == false)
                    the_field[vy][vx] = true;
                else {
                    i--;
                    cout << endl << "The cell is set alive yet. Try again.";
                    continue;
                }
            } else {
                i--;
                cout << endl << "Bad coordinates. Try again.";
                continue;
            }
        }
    } else {
        for (i = 0; i < amount; i++) {
            vx = rand() % n;
            vy = rand() % n;
            if ((vx < n - 1) && (vy < n - 1) && (vx >= 0) && (vy >= 0))
                if (the_field[vy][vx] == false)
                    the_field[vy][vx] = true;
                else {
                    i--;
                    continue;
                } else {
                    i--;
                    continue;
                }
            }
    }
// The simulation.
    died_count = 0;
    born_count = 0;
    cout << endl << "Start of the simulation." << endl << endl;
    cout << endl << "------------------------------------------------------------------" << endl << endl;
    for (k = 0; k < steps; k++) {
        alive_count_total = amount;
        // Any neighbours?
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                alive_count = 0;
                if ((i > 0) && (j > 0))
                    if (the_field[i - 1][j - 1] == true)
                        alive_count++;
                if (j > 0)
                    if (the_field[i][j - 1] == true)
                        alive_count++;
                if ((i < n - 1) && (j > 0))
                    if (the_field[i + 1][j - 1] == true)
                        alive_count++;
                if (i > 0)
                    if (the_field[i - 1][j] == true)
                        alive_count++;
                if (i < n - 1)
                    if (the_field[i + 1][j] == true)
                        alive_count++;
                if ((i > 0) && (j < n - 1))
                    if (the_field[i - 1][j + 1] == true)
                        alive_count++;
                if (j < n - 1)
                    if (the_field[i][j + 1] == true)
                        alive_count++;
                if ((i < n - 1) && (j < n - 1))
                    if (the_field[i + 1][j + 1] == true)
                        alive_count++;
                if ((the_field[i][j] == false) && (alive_count == 3)) {
                    the_field[i][j] = true;
                    alive_count_total++;
                    born_count++;
                }
                if ((the_field[i][j] == true) && ((alive_count > 3) || (alive_count < 2))) {
                    the_field[i][j] = false;
                    alive_count_total--;
                    died_count++;
                }
            }
        }
        if (amount == alive_count_total)
            cout << endl << "Step " << k + 1 << ": the population hasn't changed." << endl;
        amount = alive_count_total;
        // The statisics per 10 steps.
        if ((k + 1) % 10 == 0) {
            cout << endl << "Step " << k + 1 << "." << endl << "Alive cells: " << amount << ";" << endl << "Born/dead ratio (last 10 steps): " << born_count << "/" << died_count << "." << endl;
            died_count = 0;
            born_count = 0;
        }
        left_up = false;
        right_down = false;
        for (i = 0; i < n; i++) {
            if ((the_field[n - 1][i] == true) || (the_field[i][n - 1] == true))
                right_down = true;
            if ((the_field[0][i] == true) || (the_field[i][0] == true))
                left_up = true;
        }
        //The field expands right and down if necessary.
        if (right_down == true) {
            n++;
            bool** field_temp = new bool*[n];
            for (i = 0; i < n; i++)
                field_temp[i] = new bool[n];
            for (i = 0; i < n - 1; i++) {
                for (j = 0; j < n - 1; j++) {
                    field_temp[i][j] = the_field[i][j];
                }
            }
            for (i = 0;i < n - 1; i++)
                delete [] the_field[i];
            delete [] the_field;
            the_field = NULL;
            for (j = 0; j < n; j++)
                field_temp[n - 1][j] = false;
            for (j = 0; j < n; j++)
                field_temp[j][n - 1] = false;
            the_field = field_temp;
        }
        //The field expands up and left if necessary.
        if (left_up == true) {
            n++;
            bool** field_temp = new bool*[n];
            for (i = 0; i < n; i++) field_temp[i] = new bool[n];
            for (i = 0; i < n - 1; i++) {
                for (j = 0; j < n - 1; j++) {
                    field_temp[i + 1][j + 1] = the_field[i][j];
                }
            }
            for (j = 0; j < n; j++) {
                field_temp[0][j] = false;
            }
            for (j = 0; j < n; j++) {
                field_temp[j][0] = false;
            }
            delete [] the_field;
            the_field = field_temp;
        }
    }
    // Conclusion data.
    cout << endl << "------------------------------------------------------------------" << endl << endl;
    cout << "End of the simulation." << endl << endl;
    cout << "Alive cells: " << alive_count_total << ";" << endl;
    cout << "Population increasement: " << alive_count_total - amount_first << "." << endl << endl;
    cout << "Field size now: " << n << " x " << n << endl << endl;
    // Field view.
    cout << "Would you like to view the field (y/n)? ";
    cin >> answer;
    if (answer == 'y') {
        if (n <= 21) {
            cout << "Ok. Field size: " << n << " x " << n << endl;
            cout << "     " << 0 << " ";
            for (j = 0; j < n - 2; j++)
                cout << "  ";
            cout << n - 1 << endl;
            cout << "    ";
            for (j = 0; j < n + 1; j++)
                cout << "%%";
            cout << endl;
            for (i = 0; i < n; i++) {
                if (i == 0)
                    cout << "  0 %";
                else
                    if (i == n - 1)
                        if (n < 11)
                            cout << "  " << n - 1 << " %";
                        else
                            if (n > 100)
                                cout << " " << n - 1 << "%";
                            else
                                cout << " " << n - 1 << " %";
                    else
                        cout << "    %";
                for (j = 0; j < n; j++) {
                    if (the_field[i][j] == true)
                        cout << "*" << " ";
                    else
                        cout << "." << " ";
                }
                cout << "%" << endl;
            }
            cout << "    ";
            for (j = 0; j < n + 1; j++)
                cout << "%%";
            cout << endl;
        } else {
            while (answer != 'n') {
                cout << endl << "The field is pretty large.";
                cout << endl << "Please, enter the position which you want to view." << endl;
                cout << "x = ";
                int view_x;
                cin >> view_x;
                cout << "y = ";
                int view_y;
                cin >> view_y;
                if (view_x - 10 < 1) {
                    left_view = 1;
                    right_view = 21;
                } else {
                    if (view_x + 10 > n - 1) {
                        right_view = n - 2;
                        left_view = n - 22;
                    } else {
                        right_view = view_x + 10;
                        left_view = view_x - 10;
                    }
                }
                if (view_y - 10 < 1) {
                    up_view = 1;
                    down_view = 21;
                } else {
                    if (view_y + 10 > n - 1) {
                        down_view = n - 1;
                        up_view = n - 22;
                    } else {
                        down_view = view_y + 10;
                        up_view = view_y - 10;
                    }
                }

            cout << "Field size: " << n << " x " << n << endl;
            cout << "     " << left_view - 1 << " ";
            int d;
            if ((left_view + right_view < 101) && (left_view < 11))
                d = 40;
            if ((left_view + right_view < 101) && (left_view >= 11))
                d = 39;
            if ((left_view + right_view < 202) && (left_view + right_view > 101))
                d = 39;
            if (left_view + right_view > 202)
                d = 38;
            for (j = 0; j < d; j++)
                cout << " ";
            cout << right_view - 1 << endl;
            cout << "    ";
            for (j = 0; j < 23; j++)
                cout << "%%";
            cout << endl;
            for (i = up_view - 1; i < down_view; i++) {
                if (i == up_view - 1)
                    if (up_view < 11)
                        cout << "  " << up_view - 1 << " %";
                    else
                        if (up_view > 100)
                            cout << " " << up_view - 1 << "%";
                        else
                            cout << " " << up_view - 1 << " %";
                else
                    if (i == down_view - 1)
                        if (down_view < 11)
                            cout << "  " << down_view - 1 << " %";
                        else
                            if (down_view > 100)
                                cout << " " << down_view - 1 << "%";
                            else
                                cout << " " << down_view - 1 << " %";
                     else
                    cout << "    %";
                for (j = left_view - 1; j <= right_view; j++) {
                    if (the_field[i][j] == true)
                        cout << "*" << " ";
                    else
                        cout << "." << " ";
                }
                cout << "%" << endl;
            }
            cout << "    ";
            for (j = 0; j < 23; j++)
                cout << "%%";
            cout << endl;
                cout << endl;
                cout << "Would you like to view an another position (y/n)? ";
                cin >> answer;
            }
        }
    }
    return 0;
}

