#pragma once

#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::pair;
using std::to_string;

namespace LORE {
    template <class T>
    class Library {
        public:
            Library(): m__objects() {}

            ~Library() {}

            bool has(string path) {
                return m__objects.find(path) != m__objects.end();
            }

            void add(string path, T* object) {
                string path_ = path;
                int i = 1;
                while(has(path_)) {
                    path_ = path + "_" + to_string(i);
                    i++;
                }
                cout << "Resulting path: " << path_ << endl;
                m__objects.insert(pair<string, T*>(path_, object));
            }

            T* get(string path) {
                if(has(path))
                    return m__objects.at(path);
                else
                    return nullptr;
            }

            void list() {
                for(auto it: m__objects)
                    cout << "[Library]: " << it.first << endl;
            }

            void flush() {
                for(auto it: m__objects)
                    delete(it.second);
                m__objects.clear();
            }

        private:
            map<string, T*> m__objects;
    };
}
