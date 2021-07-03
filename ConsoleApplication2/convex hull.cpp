#include <iostream>
#include <vector>
using namespace std;

#define point pair<int, int> 
vector<point> hull;

int dishelper(point p1, point p2, point p) {
    int dis = p1.first * p2.second + p.first * p1.second + p2.first*p.second - p.first * p2.second - p2.first * p1.second - p1.first * p.second;
    return dis;
}

int distance(point p1, point p2, point p) {
    return abs(dishelper(p1, p2, p));
}

// positive is left, negative is right
int sidehelper(point p1, point p2, point p)
{
    int dis = dishelper(p1, p2, p);

    if (dis > 0) return 1;
    if (dis < 0) return -1;
    return 0;
}

vector<point> uphull(vector<point> group, point p1, point p2) {
    vector<point> temp;
    for (unsigned int i = 0; i < group.size(); i++) {
        if (sidehelper(p1, p2, group[i]) > 0) {
            temp.push_back(group[i]);
        }
    }
    return temp;
}

vector<point> downhull(vector<point> group, point p1, point p2) {
    vector<point> temp;
    for (unsigned int i = 0; i < group.size(); i++) {
        if (sidehelper(p1, p2, group[i]) < 0) {
            temp.push_back(group[i]);
        }
    }
    return temp;
}

void sortgroup(vector<point> group) {
    for (unsigned int i = 0; i < group.size() - 1; i++) {
        for (unsigned int j = i + 1; j < group.size(); j++) {
            if (group[j-1].first > group[j].first) group[j].swap(group[j-1]);
        }
    }
}


void QuickHull2(vector<point> group, int size, point p1, point p2)
{
    if (size == 0) return;

    // find the farthest point 
    int index = -1;
    int maxdis = 0;
    for (int i = 0; i < size; i++)
    {
        int temp = distance(p1, p2, group[i]);
        if (temp > maxdis){
            index = i;
            maxdis = temp;
        }
    }
    if (index == -1) return;

    point temp2 = group[index];
    hull.push_back(group[index]);
    for (auto i = group.begin(); i != group.end(); i++) {
        if ((*i).first == group[index].first && (*i).second == group[index].second) {
            group.erase(i);
            break;
        }
    }

    vector<point> up = uphull(group, temp2, p1);
    vector<point> down = downhull(group, temp2, p2);

    QuickHull2(up, up.size(),temp2, p1);
    QuickHull2(down, down.size(), temp2, p2);
}

void Quickhull(vector<point> group)
{
    int size = group.size();
    if (size < 3)
    {
        cout << "Not enough points"<<endl;
        return;
    }

    sortgroup(group);
    hull.push_back(*group.begin());
    group.erase(group.begin());
    hull.push_back(*(group.end()-1));
    group.erase(group.end() - 1);

    vector<point> up = uphull(group, hull[0], hull[1]);
    vector<point> down = downhull(group, hull[0], hull[1]);

    QuickHull2(up, up.size(), hull[0], hull[1]);
    QuickHull2(down, down.size(), hull[0], hull[1]);
}

int main()
{
    vector<point> pointgroup = { {-1,1}, {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {3, 1},{5,3} };
    Quickhull(pointgroup);

    cout << "The points in Convex Hull are: ";
    while (!hull.empty())
    {
        cout << "(" << (*hull.begin()).first << ", "<< (*hull.begin()).second << ") ";
        hull.erase(hull.begin());
    }

    return 0;
}

