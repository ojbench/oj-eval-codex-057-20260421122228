#include <bits/stdc++.h>
using namespace std;

struct Student {
    string id;
    string name;
    int score;
    int order; // insertion order for stability/tie-breaking
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Student> students; // maintain insertion order
    unordered_map<string, int> id_index; // id -> index in students
    unordered_map<string, int> name_index; // name -> index in students
    id_index.reserve(20000);
    name_index.reserve(20000);

    string line;
    int order_counter = 0;
    // Read line by line to handle variable-length commands
    while (true) {
        int cmd;
        if (!(cin >> cmd)) break;
        if (cmd == 1) {
            string id, name; int score;
            if (!(cin >> id >> name >> score)) break;
            if (id_index.find(id) != id_index.end()) {
                cout << "FAILED\n";
                continue;
            }
            Student s{ id, name, score, order_counter++ };
            int idx = (int)students.size();
            students.push_back(s);
            id_index[id] = idx;
            name_index[name] = idx;
            cout << "SUCCESS\n";
        } else if (cmd == 2) {
            // display all in insertion order
            for (const auto &s : students) {
                cout << s.id << ' ' << s.name << ' ' << s.score << "\n";
            }
        } else if (cmd == 3) {
            string id; cin >> id;
            auto it = id_index.find(id);
            if (it != id_index.end()) {
                const auto &s = students[it->second];
                cout << s.id << ' ' << s.name << ' ' << s.score << "\n";
            }
        } else if (cmd == 4) {
            string name; cin >> name;
            auto it = name_index.find(name);
            if (it != name_index.end()) {
                const auto &s = students[it->second];
                cout << s.id << ' ' << s.name << ' ' << s.score << "\n";
            }
        } else if (cmd == 5) {
            // sort by id ascending, output result only, do not change stored order
            vector<const Student*> arr;
            arr.reserve(students.size());
            for (const auto &s : students) arr.push_back(&s);
            sort(arr.begin(), arr.end(), [](const Student* a, const Student* b){
                if (a->id != b->id) return a->id < b->id;
                return a->order < b->order; // deterministic, though ids are unique
            });
            for (auto p : arr) {
                cout << p->id << ' ' << p->name << ' ' << p->score << "\n";
            }
        } else if (cmd == 6) {
            // sort by score descending; ties keep insertion order
            vector<const Student*> arr;
            arr.reserve(students.size());
            for (const auto &s : students) arr.push_back(&s);
            stable_sort(arr.begin(), arr.end(), [](const Student* a, const Student* b){
                return a->score > b->score;
            });
            for (auto p : arr) {
                cout << p->id << ' ' << p->name << ' ' << p->score << "\n";
            }
        } else if (cmd == 7) {
            cout << "END\n";
            break;
        } else {
            // Unknown command: ignore rest of line safely if any
            // But per problem, commands are valid, so do nothing.
        }
    }
    return 0;
}

