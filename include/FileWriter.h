#ifndef FILEWRITER_H
#define FILEWRITER_H
#include  <ctime>


#include <fstream>

using namespace std;


class FileWriter
{
    public:
        static void write2FileHeader(string input);
        static void write2FileBody(string input);

    protected:
    private:

        FileWriter();
};

#endif // FILEWRITER_H
