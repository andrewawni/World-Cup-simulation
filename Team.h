#ifndef TEAM_H
#define TEAM_H
#include <iostream>
#include <vector>
#include <algorithm>



class Team
{
    private:
        int m_id;
        char m_group;
        std::string m_name;
        std::string m_abr;
        double m_att;
        double m_def;
//
        int m_points;

        int m_GF;
        int m_GA;
        int m_GD;

        int m_numWins;

    public:
        Team();
        void updateTeam(int,int);

        int get_id(){return m_id;}
        void set_id(int id){m_id = id;}

        char get_group(){return m_group;}
        void set_group(char group){m_group = group;}

        std::string get_name(){return m_name;}
        void set_name(std::string name){m_name = name;}

        std::string get_abr(){return m_abr;}
        void set_abr(std::string abr){m_abr = abr;}

        double get_att(){return m_att;}
        void set_att(double att){m_att = att;}

        double get_def(){return m_def;}
        void set_def(double def){m_def = def;}

        int get_points(){return m_points;}
        void set_points(int points){m_points += points;}

        int get_GF(){return m_GF;}
        void set_GF(int GF){m_GF += GF;}

        int get_GA(){return m_GA;}
        void set_GA(int GA){m_GA += GA;}

        int get_GD(){return m_GD;}
        void set_GD(int GD){m_GD += GD;}

        int get_numWins(){return m_numWins;}
        void set_numWins(){m_numWins++;}


};

#endif // TEAM_H
