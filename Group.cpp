#include "Group.h"

Group::Group()
{

}
void Group::displayGroup()
{

    std::cout<<"POS"<<'\t'<<"TEAM"<<'\t'<<"GF"<<'\t'<<"GA"<<'\t'<<"GD"<<'\t'<<"PTS"<<'\n';
    for(int i=0; i<4; i++)
    {
        std::cout<<i+1<<'\t'<<m_teams[i].get_abr()<<'\t'<<m_teams[i].get_GF()<<'\t'<<m_teams[i].get_GA()<<'\t'<<m_teams[i].get_GD()<<'\t'<<m_teams[i].get_points()<<'\n';
    }


}
void Group::sortGroup()
{
    for(int i=0; i<4; i++)
    {
        int maxPoints = m_teams[i].get_points();
        int maxPos = i;
        for(int j = i; j<4; j++)
        {
            if(m_teams[j].get_points() > maxPoints)
            {
                maxPos = j;
                maxPoints = m_teams[j].get_points();
            }
            else if (m_teams[j].get_points() == maxPoints)
            {
                if(m_teams[j].get_GD() > m_teams[maxPos].get_GD())
                {
                    maxPos = j;
                    maxPoints = m_teams[j].get_points();
                }

            }
        }
        std::swap(m_teams[i],m_teams[maxPos]);
    }
}

