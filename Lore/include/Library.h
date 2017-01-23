#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <map>


using namespace std;

namespace LORE
{

    template <class T>
        class Library
        {

            public:

                Library(): m__objects()
            {



            }

                ~Library()
                {



                }

                bool has(std::string path)
                {

                    return m__objects.find(path) != m__objects.end();

                }

                void add(std::string path, T* object)
                {

                    m__objects.insert(pair<string, T*>(path, object));

                }

                T* get(std::string path)
                {

                    return m__objects.at(path);

                }

                void flush()
                {

                    m__objects.clear();

                }

            private:

                std::map<std::string, T*> m__objects;

        };

}

#endif
