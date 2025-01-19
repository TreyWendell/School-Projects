/*Trey Wendell
tdw0042
project2_Wendell_tdw0042.cpp
When testing one might have to press enter twice
*/



# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>
using namespace std;
//prototypes
/* Input: A_alive indicates whether Aaron is alive */
/* B_alive indicates whether Bob is alive */
/* C_alive indicates whether Charlie is alive */
/* Return: true if at least two are alive */
/* otherwise return false */
/*
* Add other function prototypes below
*/

const int total_duels = 10000;
const double aaron_acc = 0.33333333;
const double bob_acc = 0.5;
const double charlie_acc = 1;

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    
    if (A_alive && B_alive) {
        return true;
    }
    if (A_alive && C_alive) {
        return true;
    }
    if (B_alive && C_alive) {
        return true;
    }
    else {
        return false;
    }
}

bool fire(double odds) {
double chance = static_cast<double>(rand()) / RAND_MAX;
if (chance <= odds) {
    return true;
}
else {
    return false;
}
}

int Aaron_shoots1(bool& B_alive, bool& C_alive) {
   if (C_alive) {
        bool hit = fire(aaron_acc);
        C_alive = hit ? false : C_alive;
        return 2;
    }
    else if (B_alive) {
        bool hit = fire(aaron_acc);
        B_alive = hit ? false : B_alive;
        return 1;
    }
    return -1;
}

int Aaron_shoots2(bool& B_alive, bool& C_alive) {
   if (B_alive && C_alive) {
        return -1;
    }
    return Aaron_shoots1(B_alive, C_alive);
    }

int Bob_shoots(bool& A_alive, bool& C_alive) {
   if (C_alive) {
        bool hit = fire(bob_acc);
        C_alive = hit ? false : C_alive;
        return 2;
    }
    else if (A_alive) {
        bool hit = fire(bob_acc);
        A_alive = hit ? false : A_alive;
        return 0;
    }
    return -1;
    }

int Charlie_shoots(bool& A_alive, bool& B_alive) {
   if (B_alive) {
        bool hit = fire(charlie_acc);
        B_alive = hit ? false : B_alive;
        return 1;
    }
    else if (A_alive) {
        bool hit = fire(charlie_acc);
        A_alive = hit ? false : A_alive;
        return 0;
    }
    return -1;
    }

int duel(int strategy) {
    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive) {
            if (strategy == 1) {
                Aaron_shoots1(B_alive, C_alive);
            }
            else if (strategy == 2) {
                Aaron_shoots2(B_alive, C_alive);
            }
        }
        if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        }
        if (C_alive) {
            Charlie_shoots(A_alive, B_alive);
        }
    }
   return A_alive ? 0 : B_alive ? 1 : C_alive ? 2 : -1;
}






void wait_for_key(void) {
        cout << "Press Enter to continue...";
        cin.ignore().get(); // Pause Terminal
        

}

// Unit Tests
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\t\tCase passed ...\n";
    
    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\t\tCase passed ...\n";

    wait_for_key();
}

void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function - Aaron_shoots1()\n";

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool b = true; bool c = true;
    assert(2 == Aaron_shoots1(b, c));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    b = false; c = true;
    assert(2 == Aaron_shoots1(b, c));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    b = true; c = false;
    assert(1 == Aaron_shoots1(b, c));
    cout << "\t\tAaron is shooting at Bob\n";

    wait_for_key();
}

void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function - Bob_shoots()\n";

    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    bool a = true; bool c = true;
    assert(2 == Bob_shoots(a, c));
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    a = false; c = true;
    assert(2 == Bob_shoots(a, c));
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    a = true; c = false;
    assert(0 == Bob_shoots(a, c));
    cout << "\t\tBob is shooting at Aaron\n";

    wait_for_key();
}

void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function - Charlie_shoots()\n";

    cout << "\tCase 1: Aaron alive, Bob alive\n";
    bool a = true; bool b = true;
    assert(1 == Charlie_shoots(a, b));
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 2: Aaron dead, Bob alive\n";
    a = false; b = true;
    assert(1 == Charlie_shoots(a, b));
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 3: Aaron alive, Bob dead\n";
    a = true; b = false;
    assert(0 == Charlie_shoots(a, b));
    cout << "\t\tCharlie is shooting at Aaron\n";

    wait_for_key();
}

void test_Aaron_shoots2(void) {
    cout << "Unit Testing 5: Function - Aaron_shoots2()\n";

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool b = true; bool c = true;
    assert(-1 == Aaron_shoots2(b, c));
    cout << "\t\tAaron intentionally misses his first shot\n";
    assert(b == true); assert(c == true);
    cout << "\t\tBoth Bob and Charlie are alive\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    b = false; c = true;
    assert(2 == Aaron_shoots2(b, c));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    b = true; c = false;
    assert(1 == Aaron_shoots2(b, c));
    cout << "\t\tAaron is shooting at Bob\n";

    wait_for_key();
}

int test_duel(int strategy) {
    cout << "Ready to test strategy " << strategy << " (run " << total_duels << " times):\n";
    wait_for_key();

    int a_wins = 0; int b_wins = 0; int c_wins = 0;
    for (int i = 0; i < total_duels; i++) {
        int duel_result = duel(strategy);
        switch (duel_result) {
        case 0: a_wins++;
                break;
        case 1: b_wins++;
                break;
        case 2: c_wins++;
                break;
        }
    }

    cout << "Aaron won " << a_wins << "/" << total_duels << " duels or " << static_cast <double>(a_wins) / total_duels * 100 << "%\n";
    cout << "Bob won " << b_wins << "/" << total_duels << " duels or " << static_cast <double>(b_wins) / total_duels * 100 << "%\n";
    cout << "Charlie won " << c_wins << "/" << total_duels << " duels or " << static_cast <double>(c_wins) / total_duels * 100 << "%\n";
    cout << endl;

    return a_wins;
}

void eval_strategies(int wins_1, int wins_2) {
    if (wins_1 > wins_2) {
        cout << "Strategy 1 is better than strategy 2";
    }
    else if (wins_2 > wins_1) {
        cout << "Strategy 2 is better than strategy 1";
    }
    else {
        cout << "Both strategies produce equal results for Aaron";
    }
}

int main() {
    // Set cout Format
    cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

    // Initialize Random
    srand(time(0));
    rand();

    cout << "*** Welcome to Trey's Duel Simulator ***\n";
    // Unit Testing
    test_at_least_two_alive();
    test_Aaron_shoots1();
    test_Bob_shoots();
    test_Charlie_shoots();
    test_Aaron_shoots2();

    // Test Strategy
    int wins_1 = test_duel(1);
    int wins_2 = test_duel(2);
    eval_strategies(wins_1, wins_2);

    cout << endl;
    return 0;
}