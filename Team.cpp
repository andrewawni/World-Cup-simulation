#include "Team.h"

Team::Team(): m_points(0),m_GF(0),m_GA(0),m_GD(0),m_numWins(0)
{
}

void Team::updateTeam(int GF, int GA)
{
    int GD = GF-GA;
    set_GF(GF);
    set_GA(GA);
    set_GD(GD);
    if(GF>GA)
    {
        set_points(3);
    }
    else if(GA == GF)
    {
        set_points(1);

    }
    else
    {
        set_points(0);
    }
    //std::cout<<get_name()<<" ";
    //std::cout<<get_points()<<" "<<get_GF()<<" "<<get_GA()<<'\n';

}

//void Tournment::updateTeams(Team team_a,int goals_a, Team team_b, int goals_b)
//{
//    int GF,GA,GD;
//
//    GF = team_a.get_GF()+goals_a;
//    GA = team_a.get_GA()+goals_b;
//    GD = team_a.get_GD()+GF-GD;
//
//    team_a.set_GF(GF);
//    team_a.set_GA(GA);
//    team_a.set_GD(GD);
//
//    GF = team_b.get_GF()+goals_b;
//    GA = team_b.get_GA()+goals_a;
//    GD = team_b.get_GD()+(GF-GD);
//
//    team_b.set_GF(GF);
//    team_b.set_GA(GA);
//    team_b.set_GD(GD);
//
//    if(goals_a>goals_b)
//        team_a.set_points(team_a.get_points()+3);
//    else if(goals_b>goals_a)
//        team_b.set_points(team_b.get_points()+3);
//    else
//    {
//          team_a.set_points(team_a.get_points()+1);
//          team_b.set_points(team_b.get_points()+1);
//    }
//
//
//}
