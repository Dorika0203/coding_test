#include <string>
#include <vector>

#include <map>
#include <iostream>

using namespace std;

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;

    int todayi = stoi(today.substr(0, 4))*12*28 + stoi(today.substr(5, 2))*28 + stoi(today.substr(8, 2));
    map<char, int> tmap;

    for(int i=0; i<terms.size(); i++)
    {
        char type = terms[i].at(0);
        int life = stoi(terms[i].substr(2, terms[i].length()-2));
        tmap.insert({type, life});
    }

    for(int i=0; i<privacies.size(); i++)
    {
        string priv = privacies.at(i);
        string priv_date = priv.substr(0, 10);
        char priv_type = priv.at(11);

        int life = tmap.find(priv_type)->second;
        int die_date = stoi(priv_date.substr(0, 4))*12*28 + stoi(priv_date.substr(5, 2))*28 + stoi(priv_date.substr(8, 2)) + life*28;

        if(die_date <= todayi) {
            answer.push_back(i+1);
        }
    }

    return answer;
}