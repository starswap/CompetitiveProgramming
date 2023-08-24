#include <bits/stdc++.h>
using namespace std;
// slow on G101
// WA on G14
const long long INF = 1'300'000'000'000'000;

int N, M;
vector<int> A;
vector<int> C;

struct DoublyLinkedNode{
    DoublyLinkedNode* prev;
    DoublyLinkedNode* next;
    long long plant_cost = INF;
    long long cost_to_next;
    long long cost_to_prev; // remove?
};

long long cost = 0;
set<DoublyLinkedNode*> eradicated;
void merge(DoublyLinkedNode* ptr) {
    long long plant_cost = min(ptr->plant_cost, ptr->next->plant_cost);
    cost += ptr->cost_to_next;
    eradicated.insert(ptr->next);

    long long new_cost_to_next = ptr->next->cost_to_next;

    ptr->next->next->prev = ptr;
    ptr->next->next->cost_to_prev = new_cost_to_next;

    ptr->next = ptr->next->next;
    ptr->cost_to_next = new_cost_to_next;
    ptr->plant_cost = plant_cost;
}

bool is_good(DoublyLinkedNode* ptr) {
    long long unmerged_cost = ptr->plant_cost + ptr->next->plant_cost;
    long long merged_cost = min(ptr->plant_cost, ptr->next->plant_cost) + ptr->cost_to_next;
    return !eradicated.count(ptr) && (merged_cost <= unmerged_cost) && ptr != ptr->next; // check still saves
}

priority_queue<pair<long long, DoublyLinkedNode*>> pq;
set<DoublyLinkedNode*> in_pq;
void add_if_good(DoublyLinkedNode* ptr) {
    long long unmerged_cost = ptr->plant_cost + ptr->next->plant_cost;
    long long merged_cost = min(ptr->plant_cost, ptr->next->plant_cost) + ptr->cost_to_next;
    if (merged_cost <= unmerged_cost && !(in_pq.count(ptr)) && ptr != ptr->next) {
        kpq.emplace(unmerged_cost - merged_cost, ptr);
        in_pq.insert(ptr);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    A.resize(M);
    C.resize(M);

    for (int i = 0; i < M; ++i) {
        cin >> C[i] >> A[i];
    }

    // build structure
    vector<DoublyLinkedNode> nodes(N);
    for (int i = 0; i < N - 1; ++i) {
        nodes[i].next = &nodes[i + 1];
        nodes[i + 1].prev = &nodes[i];
    }
    nodes[N - 1].next = &nodes[0];
    nodes[0].prev = &nodes[N - 1];

    long long cost_to_next;
    for (int i = 0; i < N - 1; ++i) {
        cin >> cost_to_next;
        nodes[i].cost_to_next = cost_to_next;
        nodes[i + 1].cost_to_prev = cost_to_next;
    }
    cin >> cost_to_next;
    nodes[N - 1].cost_to_next = cost_to_next;
    nodes[0].cost_to_prev = cost_to_next;

    for (int i = 0; i < M; ++i) {
        nodes[C[i]-1].plant_cost = A[i];
    }

    DoublyLinkedNode* ptr = &nodes[0];

    bool done_any = false;
    while (&nodes[0] != ptr || !done_any)  {
        done_any = true;
        add_if_good(ptr);
        ptr = ptr->next;
    }

    DoublyLinkedNode* lastOk = &nodes[0];
    while (pq.size() != 0) {
        ptr = pq.top().second; pq.pop();
        in_pq.erase(ptr);

        if (is_good(ptr)) {
            merge(ptr);
            lastOk = ptr;
        }
        add_if_good(ptr->next);
        add_if_good(ptr->prev);
    }

    ptr = lastOk;
    DoublyLinkedNode* start = ptr;
    done_any = false;
    while (start != ptr || !done_any) {
        done_any = true;
        cost += ptr->plant_cost;
        ptr = ptr->next;
    }

    cout << cost << endl;
    return 0;
}

// make power plant cost infinite at all units where we can't build
// ptr = 0
// can merge ptrth pair?
// if yes: 
//    do merge
//    ptr--
// if no
//    ptr++ 

// seg fault?
// stack overlfow
// pointer issue - null ptr dereference?
