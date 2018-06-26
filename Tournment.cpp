#include "Tournment.h"

Tournment::Tournment() :m_stage(0),displayFixture(false)
{
    std::ifstream openFile("Teams.txt");
    for(int i=0; i<8; i++)
    {
        m_groups.push_back(Group());

        for(int j=0; j<4; j++)
        {
            m_groups[i].m_teams.push_back(Team());
            int id;
            char group;
            std::string name;
            std::string abr;
            double att;
            double def;

            openFile>>id>>group>>name>>abr>>att>>def;

            m_groups[i].m_teams[j].set_id(id);
            m_groups[i].m_teams[j].set_group(group);
            m_groups[i].m_teams[j].set_name(name);
            m_groups[i].m_teams[j].set_abr(abr);
            m_groups[i].m_teams[j].set_att(att);
            m_groups[i].m_teams[j].set_def(def);

        }

    }
    openFile.close();
}

int Tournment::play()
{
    std::cout<<"WORLDCUP SIMULATION RUSSIA 2018"<<'\n';
        std::cout<<"==============================="<<'\n'<<'\n'<<'\n';
        char choice;
    while(true)
    {
        std::cout<<"Simulate once [1]"<<'\n';
        std::cout<<"Simulate for n times [2]"<<'\n';
        std::cout<<"EXIT [0]"<<'\n';

        std::string choice;
        std::cin>>choice;
        if(choice.size()>1 || choice.size()<0)
        {
            std::cout<<"Invalid input, please try again"<<'\n';
        }

        else if(choice[0] == '1')
        {
            setDisplayFixture(true);
            playTournment();
            std::cout<<'\n';
        }
        else if(choice[0] == '2')
        {
            setDisplayFixture(false);

            RETRY:
            std::cout<<"Enter number of simulations"<<'\n';
            int n;
            std::cin>>n;
            if(n<1)
                goto RETRY;
            else
            {
                for(int i=0; i<n; i++)
                    playTournment();
            }
            displayWinners();
        }
        else if(choice[0] == '0')
        {
            std::cout<<"Goodbye!"<<'\n';
            return 0;
        }
        else
        {
            std::cout<<"Invalid input, please try again"<<'\n';
        }
    }
}

void Tournment::playTournment()
{
    playGroups();
    playR16();
    playR8();
    playR4();
    playR2();

    clean();
}
int Tournment::factorial(int n)
{
    int ans = 1;
    for(int i=1; i<=n; i++)
        ans*=i;

    return ans;
}

double Tournment::possCalculator(double x,double rateOfSuccess)
{
    double probability;
    probability = pow(rateOfSuccess, x)/exp(rateOfSuccess);
    probability/=factorial(x);

    return probability;
}



void Tournment::displayTeams()
{


    for(int i=0; i<8; i++)
    {


        for(int j=0; j<4; j++)
        {

            std::cout<<m_groups[i].m_teams[j].get_id()<<" "<<
                     m_groups[i].m_teams[j].get_group()<<" "<<
                     m_groups[i].m_teams[j].get_name()<<" "<<
                     m_groups[i].m_teams[j].get_abr()<<" "<<
                     m_groups[i].m_teams[j].get_att()<<" "<<
                     m_groups[i].m_teams[j].get_def()<<'\n';
        }
    }
}


int Tournment::playPenalties()
{

    std::vector<int> a;
    std::vector<int> b;
    int rnd = 0;
    int score_a = 0;
    int score_b = 0;

    for(int i=0; i<5; i++)
    {
        if(score_a>score_b+5-i)
        {
            //a wins
            if(displayFixture)
                std::cout<<"PEN("<<score_a<<"-"<<score_b<<")"<<'\n';
            return 0;
        }
        else if(score_a+5-i >= score_b)
        {
            //play
            rnd = rand()%2;
            a.push_back(rnd);
            score_a+=rnd;
        }
        else
        {
            //b wins
            if(displayFixture)
                std::cout<<"PEN("<<score_a<<"-"<<score_b<<")"<<'\n';
            return 1;
        }
        if(score_b > score_a+5-i-1)
        {
            //b wins
            if(displayFixture)
                std::cout<<"PEN("<<score_a<<"-"<<score_b<<")"<<'\n';
            return 1;
        }
        else if (score_b+5-i >= score_a)
        {
            //play
            rnd = rand()%2;
            b.push_back(rnd);
            score_b+=rnd;
        }
        else
        {
            //a wins
            if(displayFixture)
                std::cout<<"PEN("<<score_a<<"-"<<score_b<<")"<<'\n';
            return 0;
        }
    }
    while(true)
    {
        if(score_a>score_b)
        {
            //a wins
            if(displayFixture)
                std::cout<<"PEN("<<score_a<<"-"<<score_b<<")"<<'\n';
            return 0;
        }
        else if(score_a<score_b)
        {
            //b wins
            if(displayFixture)
                std::cout<<"PEN("<<score_a<<"-"<<score_b<<")"<<'\n';
            return 1;
        }
        int rnd1 = rand()%2;
        a.push_back(rnd1);
        score_a+=rnd1;

        int rnd2 = rand()%2;
        b.push_back(rnd2);
        score_b+=rnd2;
    }
}
void Tournment::displayMatchResult(int a, int b)
{
        std::cout<<a<<" "<<b<<'\n';

}

int Tournment::playMatch(Team& a,Team& b)
{
    double prob_a = a.get_att()*b.get_def();
    double prob_b = b.get_att()*a.get_def();

    int sumWeights_a = 0;
    int sumWeights_b = 0;

    std::vector<double> weights_a;
    std::vector<double> weights_b;

    for(int i=0; i<8; i++)
    {
        weights_a.push_back(possCalculator(i,prob_a/10)*100);
        sumWeights_a+=weights_a[i];
        weights_b.push_back(possCalculator(i,prob_b/10)*100);
        sumWeights_b+=weights_b[i];
    }

    int rnd;
    int g_a,g_b;

    rnd = (rand()%sumWeights_a)+1;

    for(int i=0; i<8; i++)
    {
        if(rnd<weights_a[i])
        {
            g_a =i;
            break;
        }
        else
        {
            rnd-=weights_a[i];
        }
    }

    rnd = (rand()%sumWeights_b)+1;
    for(int i=0; i<8; i++)
    {
        if(rnd<weights_b[i])
        {
            g_b = i;
            break;
        }
        else
        {
            rnd-=weights_b[i];
        }
    }
    if(displayFixture)
        displayMatchResult(g_a,g_b);

    if(getStage()<=3)
    {
        a.updateTeam(g_a,g_b);
        b.updateTeam(g_b,g_a);
    }

    if(g_a == g_b)
        return -1;
    else if(g_a<g_b)
        return 1;
    else if(g_a>g_b)
        return 0;
}

void Tournment::playGroups()
{

    int stage;
    std::ifstream openFile("matches.txt");

    for(int k =0; k<3; k++)
    {
        openFile>>stage;
        setStage(stage);
        if(displayFixture)
            std::cout<<"STAGE "<<getStage()<<'\n';
        for(int n=0; n<16; n++)
        {
            char group;
            int id_a,id_b;
            int KEY1,KEY2;
            Team team_a;
            Team team_b;
            openFile>>group>>id_a>>id_b;

            int j = (int)group-65;
            //std::cout<<group<< " ";
            for(int i=0; i<4; i++)
            {
                if(m_groups[j].m_teams[i].get_id() == id_a)
                {
                    team_a = m_groups[j].m_teams[i];
                    KEY1 = i;
                }
                else if(m_groups[j].m_teams[i].get_id() == id_b)
                {
                    team_b = m_groups[j].m_teams[i];
                    KEY2 = i;
                }
            }
            if(displayFixture)
                std::cout<<team_a.get_abr()<<" "<<team_b.get_abr()<<'\n';
            playMatch(team_a,team_b);

            m_groups[j].m_teams[KEY1] = team_a;
            m_groups[j].m_teams[KEY2] = team_b;

            m_groups[j].sortGroup();

        }
        if(displayFixture)
            std::cout<<'\n';

    }
    if(displayFixture)
    {

        for(char i='A'; i<='H'; i++)
        {
            std::cout<<"GROUP "<<i<<'\n';
            m_groups[(int)(i-65)].displayGroup();
        }

    }
    openFile.close();
}

void Tournment:: playR16()
{
    if(displayFixture)
        std::cout<<'\n'<<"ROUND OF 16:\n";
    std::ifstream openFile("R16.txt");
    int pos;
    char group;
    for(int i=0; i<16; i++)
    {
        openFile>>pos>>group;
        m_R16.push_back(m_groups[(int)group-65].m_teams[pos-1]);
    }
    for(int i=0; i<16; i+=2)
    {
        if(displayFixture)
            std::cout<<m_R16[i].get_abr()<<" "<<m_R16[i+1].get_abr()<<'\n';
        int winner = playMatch(m_R16[i],m_R16[i+1]);
        if(winner==0)
        {
            m_R8.push_back(m_R16[i]);

        }
        else if (winner==1)
        {
            m_R8.push_back(m_R16[i+1]);

        }
        else
        {
            winner = playPenalties();
            if(winner==0)
            {
                m_R8.push_back(m_R16[i]);
            }
            else if(winner ==1)
            {
                m_R8.push_back(m_R16[i+1]);
            }
        }
    }
}
void Tournment::playR8()
{
    if(displayFixture)
        std::cout<<'\n'<<"QUARTER FINALS:\n";
    for(int i=0; i<8; i+=2)
    {
        if(displayFixture)
            std::cout<<m_R8[i].get_abr()<<" "<<m_R8[i+1].get_abr()<<'\n';
        int winner = playMatch(m_R8[i],m_R8[i+1]);
        if(winner==0)
        {
            m_R4.push_back(m_R8[i]);

        }
        else if (winner==1)
        {
            m_R4.push_back(m_R8[i+1]);

        }
        else
        {
            winner = playPenalties();
            if(winner==0)
            {
                m_R4.push_back(m_R8[i]);
            }
            else if(winner ==1)
            {
                m_R4.push_back(m_R8[i+1]);
            }
        }
    }
}
void Tournment::playR4()
{
    if(displayFixture)
        std::cout<<'\n'<<"SEMI FINALS:\n";
    for(int i=0; i<4; i+=2)
    {
        if(displayFixture)
            std::cout<<m_R4[i].get_abr()<<" "<<m_R4[i+1].get_abr()<<'\n';
        int winner = playMatch(m_R4[i],m_R4[i+1]);
        if(winner==0)
        {
            m_R2.push_back(m_R4[i]);
        }
        else if (winner==1)
        {
            m_R2.push_back(m_R4[i+1]);
        }
        else
        {
            winner = playPenalties();
            if(winner==0)
            {
                m_R2.push_back(m_R4[i]);
            }
            else if(winner ==1)
            {
                m_R2.push_back(m_R4[i+1]);
            }
        }
    }
}
void Tournment::playR2()
{
    if(displayFixture)
        std::cout<<'\n'<<"FINAL:\n";
    if(displayFixture)
        std::cout<<m_R2[0].get_abr()<<" "<<m_R2[1].get_abr()<<'\n';
    int winner = playMatch(m_R2[0],m_R4[1]);
    if(winner==0)
    {
        m_winner = m_R2[0];
    }
    else if (winner==1)
    {
        m_winner = m_R2[1];
    }
    else
    {
        winner = playPenalties();
        if(winner==0)
        {
            m_winner = m_R2[0];
        }
        else if(winner ==1)
        {
            m_winner = m_R2[1];
        }
    }
    incrementWinner();
    if(displayFixture)
        std::cout<<"WINNER: "<<m_winner.get_abr()<<'\n';
}
void Tournment::clean()
{
    int temp;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<4; j++)
        {
            temp = 0-m_groups[i].m_teams[j].get_points();
            m_groups[i].m_teams[j].set_points(temp);
            temp = 0-m_groups[i].m_teams[j].get_GF();
            m_groups[i].m_teams[j].set_GF(temp);
            temp = 0-m_groups[i].m_teams[j].get_GA();
            m_groups[i].m_teams[j].set_GA(temp);
            temp = 0-m_groups[i].m_teams[j].get_GD();
            m_groups[i].m_teams[j].set_GD(temp);
        }
    }
    m_R16.clear();
    m_R8.clear();
    m_R4.clear();
    m_R2.clear();
}
int Tournment::incrementWinner()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(m_groups[i].m_teams[j].get_id()==m_winner.get_id())

            {
                m_groups[i].m_teams[j].set_numWins();
                return 0;
            }
        }
    }

}
void Tournment::displayWinners()
{

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<4; j++)
        {
            std::cout<<m_groups[i].m_teams[j].get_abr()<<": "<<m_groups[i].m_teams[j].get_numWins()<<'\n';
        }
    }
}



