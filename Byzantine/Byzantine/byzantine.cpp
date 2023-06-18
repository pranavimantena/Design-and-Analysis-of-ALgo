//
//  main.cpp
//  Byzantine
//
//  Created by Pranavi Manthena on 11/25/21.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;


// true attack
// false retreat
class officer {
    public:
    bool is_traitor = false;
    std::map<string, bool> commands;
   
};

int main()
{
    // inputs
    int target_officer_to_display = 9;
    int num_officers = 10;
    bool main_command = true ;
    //
   
    std::vector<officer> army;
    for ( int i = 0 ; i < num_officers; i++){
        officer a;
        army.push_back(a);
    }
   
    // inputs
    int num_traitors = 3;
    army[0].is_traitor = true;
    army[5].is_traitor = true;
    army[6].is_traitor = true;
    //
   
    int rounds = 0;
   
    for ( int j = 0 ; j < num_traitors+1; j++) {
   
        for( int i = 0; i < num_officers; i++){
            if ( i == 0){
                continue;
            }
            if (army[i].commands.size()==0){
                if (army[0].is_traitor){
                    army[i].commands.insert(pair<string, bool>("0", i%2));
                }
                else {
                    army[i].commands.insert(pair<string, bool>("0", main_command));
                }
            }
            else {
                for (auto itr = army[i].commands.begin(); itr != army[i].commands.end(); ++itr){
                    if (itr->first.size() != rounds){
                        continue;
                    }
                    for ( int other = 1; other < num_officers; other++){
                        if ( other == i){
                            continue;
                        }
                        if (itr->first.find(std::to_string(other)) != std::string::npos) {
                            continue;
                        }
                        if (army[other].is_traitor && rounds == 1){
                            army[i].commands.insert(pair<string, bool>(itr->first + std::to_string(other),i%2));
                        }
                        else {
                            army[i].commands.insert(pair<string, bool>(itr->first + std::to_string(other),
                            army[other].commands.find(itr->first)->second));
                        }
                    }
                }
            }
           
        }
        rounds++;
    }
   
   
    // second phase:
    std::vector<bool> final_commands;
    for ( int officer  = 1; officer < num_officers; officer ++) {
       
        bool final_command = true;
       
        if ( officer == target_officer_to_display ){
            cout << "general " << officer << "\n\n";
        }
       
        for ( int cur_round = rounds-1; cur_round > 0; cur_round--){
       
            for (auto itr = army[officer].commands.begin(); itr != army[officer].commands.end(); ++itr){
               
                           
                int attack = 0;
                int retreat = 0;
           
                if ( itr->first.size() != cur_round){
                    continue;
                }
                if ( officer == target_officer_to_display){
                    cout << itr->first << "->" << itr->second << "\n";
                }
                if (itr->second == true){
                    attack++;
                }
                else{
                    retreat++;
                }
                for (auto other_iter = army[officer].commands.begin(); other_iter != army[officer].commands.end(); ++other_iter){
                    if (other_iter->first.size()!=cur_round+1){
                        continue;
                    }
                    if ( other_iter->first.compare(0, itr->first.size(), itr->first) != 0 ){
                        continue;
                    }
                    if (other_iter->second == true){
                        attack++;
                    }
                    else{
                        retreat++;
                    }
                    if ( officer == target_officer_to_display){
                        cout << other_iter->first << "->" << other_iter->second << "\n";
                    }
                }
                if ( attack > retreat ){
                    if ( officer == target_officer_to_display){
                        cout << "consensus" << "->" << "Attack" << "\n";
                    }
                    itr->second = 1;
                    final_command = 1;
                }
                else {
                    if ( officer == target_officer_to_display){
                        cout << "consensus" << "->" << "Retreat" << "\n";
                    }
                    itr->second = 0;
                    final_command = 0;
                }
                if ( officer == target_officer_to_display){
                    cout << "---\n";
                }
            }
        }
       
        final_commands.push_back(final_command);
    }
   
    for ( int officer  = 1; officer < num_officers; officer ++){
       
        if (army[officer].is_traitor){
            continue;
        }
        cout << "General " << officer << " decides to ";
        if (final_commands[officer-1] == true ){
            cout << "Attack\n";
        }
        else {
            cout << "Retreat\n";
        }
    }
}
