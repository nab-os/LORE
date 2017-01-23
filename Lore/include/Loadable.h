#ifndef LOADABLE_H
#define LOADABLE_H

namespace LORE
{

    class Loadable
    {

        public:

            Loadable();
            virtual ~Loadable();

            virtual void load() { m__loaded = true; };
            virtual void unload() { m__loaded = false; };
            virtual void reload() { unload(); load(); };

            bool loaded() { return m__loaded; };

        private:

            bool m__loaded;

    };

}

#endif
