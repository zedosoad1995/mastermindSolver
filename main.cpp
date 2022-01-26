#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void initialize_possible_sets(vector<string> &possible_sets, string &string_of_set, char colors[], int n_colors, int n_columns, int depth = 0);
void get_set(vector<string> &possible_sets, string previous_set, int n_reds, int n_whites);
bool check_reds(string set, string previous_set, int n_reds, bool tested_positions[]);
bool check_whites(string set, string previous_set, int n_whites, bool tested_positions_current[]);

int main(){
    
    int n_colors = 8;
    int n_columns = 5;
    char colors[n_colors] {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}; 
    vector<string> possible_sets;
    string aux_string {"AAAAA"};
    
    srand(time(nullptr));
    
    initialize_possible_sets(possible_sets, aux_string, colors,  n_colors, n_columns);
    
    string user_response;
    int n_reds, n_whites;
    string previous_set;
    while(true){
        previous_set = possible_sets[rand()%possible_sets.size()];
        cout << previous_set << endl;
        cout << "How many Reds? ";
        cin >> user_response;
        n_reds = stoi(user_response);
        if(n_reds == n_columns){
            cout << "I win!!!";
            break;
        }
        cout << "How many Whites? ";
        cin >> user_response;
        n_whites = stoi(user_response);
        get_set(possible_sets, previous_set, n_reds, n_whites);
        if(possible_sets.size() == 0){
            cout << "Impossible! You made a mistake.";
            break;
        }else if(possible_sets.size() == 1){
            cout << "I know the answer ...\n" << possible_sets[0];
            break;
        }
    }
    
    cin >> n_reds;
    
	return 0;
}

void initialize_possible_sets(vector<string> &possible_sets, string &string_of_set, char colors[], int n_colors, int n_columns, int depth){
    
    if(depth++ < n_columns){
        for(size_t i = 0; i < n_colors; i++){
            string_of_set[depth-1] = colors[i];
            initialize_possible_sets(possible_sets, string_of_set, colors, n_colors, n_columns, depth);
        }
    }else{
        possible_sets.push_back(string_of_set);
    }
}

void get_set(vector<string> &possible_sets, string previous_set, int n_reds, int n_whites){

    bool tested_positions[previous_set.length()];
    
    for(size_t i = 0; i < possible_sets.size(); i++){
        for(size_t j = 0; j < previous_set.length(); j++){
            tested_positions[j] = false;
        }
        if(!check_reds(possible_sets[i], previous_set, n_reds, tested_positions) || !check_whites(possible_sets[i], previous_set, n_whites, tested_positions)){
            possible_sets.erase(possible_sets.begin() + i);
            i--;
        }
    }

}

bool check_reds(string set, string previous_set, int n_reds, bool tested_positions[]){
    int counted_reds = 0;
    for(size_t i = 0; i < set.length(); i++){
        if(set[i] == previous_set[i]){
            counted_reds++;
            tested_positions[i] = true;
        }
    }
    if(n_reds == counted_reds){
        return true;
    }else{
        return false;
    }
}

bool check_whites(string set, string previous_set, int n_whites, bool tested_positions_current[]){
    int counted_whites = 0;
    bool tested_positions_previous[set.length()];
    
    for(size_t i = 0; i < set.length(); i++){
        tested_positions_previous[i] = tested_positions_current[i];
    }
        
    for(size_t i = 0; i < set.length(); i++){
        if(tested_positions_current[i]) continue;
        for(size_t j = 0; j < set.length(); j++){
            // checks if elements are in different positions and if they haven't yet been marked
            if(!tested_positions_current[i] && !tested_positions_previous[j] && i != j){
                if(set[i] == previous_set[j]){
                    counted_whites++;
                    tested_positions_current[i] = true;
                    tested_positions_previous[j] = true;
                }
            }
        }
    }
    
    if(n_whites == counted_whites){
        return true;
    }else{
        return false;
    }
}