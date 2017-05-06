#include "FileWriter.h"

FileWriter::FileWriter()
{
    //ctor
}



void FileWriter::write2FileHeader(string input) {
    ofstream resultOfAnalysis;


    time_t rawtime;
    struct tm * timeinfo;
    char date[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(date,sizeof(date),"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string str(date);

    resultOfAnalysis.open ("resultOfAnalysis.txt", std::fstream::app);
    resultOfAnalysis << "\n===================================================================================================\n";
    resultOfAnalysis << date ;
    resultOfAnalysis << "\nAnalisi di: " << input;
    resultOfAnalysis.close();
}


void FileWriter::write2FileBody(string input) {
    ofstream resultOfAnalysis;

    resultOfAnalysis.open ("resultOfAnalysis.txt", std::fstream::app);
    resultOfAnalysis << "\n" + input;
    resultOfAnalysis.close();
}
