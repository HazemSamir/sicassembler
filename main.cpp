#include <getopt.h>
#include <PassOne.h>
#include <FixedFormatReader.h>

#ifndef INCLUDES_H
#include <Includes.h>
#endif // INCLUDES_H

#include "PassTwo.h"

void runPass1(bool isFixed, string sourceName, string outputName) {
    PassOne *p;
    cout << "intermediate file: \"" << outputName << "\"" << endl;
    if(isFixed) {
        p = new PassOne(new FixedFormatReader(sourceName), outputName);
    } else {
        p = new PassOne(sourceName, outputName);
    }
    p->pass();
    cout << "\n***************************\n\n";
    PassTwo *p2 = new PassTwo(outputName, p->getSymTable(), nullptr, p->getprogrammLength());
    p2->pass();
}

void print_usage();

int main(int argc, char *argv[]) {
    bool isFixed = false;
    char *outputPath = NULL;
    char *sourcePath = NULL;

    int c;
    while ((c = getopt (argc, argv, "hxo:")) != -1) {
        if (c == 'x') {
            isFixed = true;
        } else if (c == 'o') {
            outputPath = optarg;
        } else if(c == '?') {
            if (optopt == 'o')
                fprintf (stderr, "Option -%c requires an output path.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            print_usage();
            return 1;
        } else {
            print_usage();
            abort ();
        }
    }
    if (optind == argc - 1) {
        sourcePath = argv[optind];
        cout << "source path: \"" << sourcePath << "\"" << endl;
    } else if (optind < argc) {
        fprintf (stderr, "too many arguments\n");
        print_usage();
        return 1;
    } else {
        fprintf (stderr, "source file path is messing\n");
        print_usage();
        return 1;
    }
    string source(sourcePath);
    string output;
    if (outputPath == NULL) {
        output = source + "_list.txt";
    } else {
        output = *(new string(outputPath));
    }
    runPass1(isFixed, source, output);
    return 0;
}

void print_usage() {
    printf(
        "sic assembler pass1\n"
        "Usage: pass1 <sourcefile path> options [-x][-o outputPath]\n"
        "Options:\n"
        "\t[-x]             fixed format flag.\n"
        "\t[-o outputPath]  specified output path (default called <sourcefile>_out.txt).\n"
        "\t-h               print help.\n"
    );
}
