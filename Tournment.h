#ifndef TOURNMENT_H
#define TOURNMENT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "Group.h"
#include "Team.h"
#include "math.h"




class Tournment
{
    private:
        bool displayFixture;
        int m_stage;
        std::vector<Group> m_groups;
        std::vector<Team> m_R16;
        std::vector<Team> m_R8;
        std::vector<Team> m_R4;
        std::vector<Team> m_R2;
        Team m_winner;
        int factorial(int n);
        double possCalculator(double,double);

    public:

        Tournment();
        //for testing
        void displayTeams();

        int play();
            void playTournment();
                void playGroups();
                void playR16();
                void playR8();
                void playR4();
                void playR2();


        //returns ID of winner,-1 if draw
        int playMatch(Team&,Team&);
        int playPenalties();

        void displayMatchResult(int,int);
        void setDisplayFixture(bool b){displayFixture = b;}



        //increments m_numWins in the winner team
        int incrementWinner();
        void displayWinners();

        int getStage(){return m_stage;}
        void setStage(int stage){m_stage = stage;}

        //empties the knockouts vectors
        void clean();

};

#endif // TOURNMENT_H
