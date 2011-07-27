#ifndef LOGGER_H
#define LOGGER_H

#include<string>
#include<cstdio>
#include<vector>
#include<ncurses.h>

namespace hax{

    typedef std::vector<std::string> Lines;

    class Logger{
        int pos; //where to write
        int width;

      protected:
        Lines wordWrap(std::string,size_t width);
      public:
        Logger();
        void clearLog();
        void write(std::string);
        void write(char*);
    };

}

#endif
