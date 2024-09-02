#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fori(i,a,b) for(int i=a;i<=b;i++)
#define ford(i,a,b) for(int i=a;i>=b;i--)
#define f first
#define s second
#define pb push_back
const int ma = 1000005;
// result
int a_end, a_start, normal_end;
int pos[ma];
int f[ma];
int n, m;
vector<int> my_airports;
map<string, int> str_to_number;
int cnt_map = 0;

// flight
struct flight_struct {
    int t_depart;
    int t_arrive;
    int a_depart;
    int a_arrive;
    int min_end;
    int initial_position;
    bool is_in_itinerary;
};
flight_struct flights[ma];

// airport
int flight_started_track[ma];
// flight min1onward min2onward
vector<pair<flight_struct, pair<int, int>>> flights_from[ma];

int time_to_minutes(string s) {
    int d_pos;
    for(int i=0;i<s.length();i++) {
        if (s[i] == 'd') {
            d_pos = i - 1;
            break;
        }
    }
    int a;
    if (d_pos == 0) {
        a = (s[0] - '0') * 24 * 60;
    } else if (d_pos == 2) {
        a = (s[0] - '0')  * 24 * 60 * 100 + (s[0] - '0') * 24 * 60 * 10 + (s[0] - '0') * 24 * 60;
    } else {
        a = (s[0] - '0') * 24 * 60 * 10 + (s[0] - '0') * 24 * 60;
    }
    int b = (s[2 + d_pos] - '0') * 10 * 60;
    int c = (s[3 + d_pos] - '0') * 60;
    int d = (s[5 + d_pos] - '0') * 10;
    int e = (s[6 + d_pos] - '0');
    return a + b + c + d + e;
}

void dfs(flight_struct my_flight) {
        cout<<my_flight.initial_position<<' ';
    int t_arr = my_flight.t_arrive;
    //int t_dep = my_flight.t_depart;
    int a_arr = my_flight.a_arrive;
    //int a_dep = my_flight.a_depart;
    if (a_arr == a_end) {
        my_flight.min_end = t_arr;
        return;
    }
    // bin search in flights_from[a_arr], where t_arr <= flights_from[a_arr][t].f.t_depart
    int s = 1e18;
    int latest_flights_next = flights_from[a_arr].size() - 1;
    int l = 0, r = flights_from[a_arr].size() - 1;
    while (l <= r) {
        int m = (l + r)/2;
        if (t_arr <= flights_from[a_arr][m].f.t_depart) {
            s = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    if (s > latest_flights_next) {
        my_flight.min_end = 1e18;
        return;
    }
    ford (f, flight_started_track[a_arr] - 1, s) {
        dfs(flights_from[a_arr][f].f);
        int min1, min2;
        if (f == latest_flights_next) {
            min1 = 1e18;
            min2 = 1e18;
        } else {
            min1 = flights_from[a_arr][f + 1].s.f;
            min2 = flights_from[a_arr][f + 1].s.s;
        }
        int tmp = flights_from[a_arr][f].f.min_end;
        if (tmp <= min1) {
            min2 = min1;
            min1= tmp;
        } else {
            min2 = min(min2, tmp);
        }
        flights_from[a_arr][f].s.f = min1;
        flights_from[a_arr][f].s.s = min2;
    }
    my_flight.min_end = flights_from[a_arr][s].s.f;
    flight_started_track[a_arr] = s;
    return;
}

int find_value_if_cancel_itinerary(int i) {
    // f[i] pos[f[i]]
    // f[i-1] pos[f[i-1]]
    int a_arr = flights[pos[f[i-1]]].a_arrive;
    int t_arr = flights[pos[f[i-1]]].t_arrive;

    int s = 1e18;
    int l = 0, r = flights_from[a_arr].size() - 1;
    while (l <= r) {
        int m = (l + r)/2;
        if (t_arr <= flights_from[a_arr][m].f.t_depart) {
            s = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    int min1 = flights_from[a_arr][s].s.f;
    int min2 = flights_from[a_arr][s].s.f;
    if (min1 == normal_end) return min2;
    return min1;
}

int map_airport_to_int(string str) {
    if (!str_to_number.count(str)) {
        my_airports.pb(cnt_map);
        return cnt_map++;
    }
    return str_to_number[str];
}

bool cmp_flights(flight_struct a, flight_struct b) {
    return a.t_depart < b.t_depart;
}

signed main() {
    cin>>n;
    fori(i,1,n) {
        string a,b,c,d;
        cin>>a>>b>>c>>d;
        int t_dep = time_to_minutes(b);
        int t_arr = time_to_minutes(d);
        int a_dep = map_airport_to_int(a);
        int a_arr = map_airport_to_int(c);
        cout<<d<<' '<<t_arr<<'\n';
        flights[i].t_depart = t_dep;
        flights[i].t_arrive = t_arr;
        flights[i].a_depart = a_dep;
        flights[i].a_arrive = a_arr;
        flights[i].min_end = 1e18;
        flights[i].initial_position = i;
    }
    sort(flights + 1, flights + n + 1, cmp_flights);
    flights[0].t_depart = 0;
    flights[0].t_depart = 0;
    flights[0].t_depart = 0;
    flights[0].t_depart = 0;
    for(int i=1;i<=n;i++) {
        pos[flights[i].initial_position] = i;
        flights_from[flights[i].a_depart].pb({flights[i],{1e18,1e18}});
        flight_started_track[flights[i].a_depart]++;
    }
    cin >> m;
    fori (i, 1, m) {
        cin>>f[i];
    }
    a_start = pos[f[1]];
    a_end = pos[f[m]];
    flights[0].a_depart = a_start;
    flights[0].a_arrive = a_start;
    flights[0].t_depart = 0;
    flights[0].t_arrive = 0;
    flights[0].min_end = 1e18;
    dfs(flights[0]);
    fori (i,1,n) cout<<flights[i].t_arrive<<' ';
    return 0;
    int maxVal = 0;
    fori(i,1,n) {
        maxVal = max(maxVal, find_value_if_cancel_itinerary(i));
    }
    if (maxVal <= normal_end) {
        cout<<0;
    } else if (maxVal == 1e18) {
        cout<<"stranded";
    } else {
        cout<<maxVal - normal_end;
    }
}