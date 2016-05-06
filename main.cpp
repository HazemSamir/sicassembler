#include <bits/stdc++.h>
#include <getopt.h>
#include <PassOne.h>
#include <PassTwo.h>
#include <FixedFormatReader.h>

using namespace std;

void runPass1(bool isFixed, string sourceName, string outputName) {
    PassOne *p;
    if(isFixed) {
        p = new PassOne(new FixedFormatReader(sourceName), outputName);
    } else {
        p = new PassOne(sourceName, outputName);
    }
    p->pass();
    PassTwo *p2;
    p2 = new PassTwo(outputName,p->getSymTable(),nullptr,p->getProgramLength());
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
        output = source + "_out.txt";
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
