#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Team.h"


class Group
{
    private:
    public:
        Group();
        std::vector <Team> m_teams;
        void sortGroup();
        void displayGroup();
        Team getTeam(int i){return m_teams[i];}




};

#endif // GROUP_H
