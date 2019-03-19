 #include "CuTest.h"
    
    CuSuite* StrUtilGetSuite();
    
    void RunAllTests(void) {
        CuString *output = CuStringNew();
        CuSuite* suite = CuSuiteNew();
        
        //There are duplicate functions so bot hfiles can't be tested together, 
        //to test Dijkstra's uncoment the first line and comment the second. 

        //CuSuiteAddSuite(suite, DijkstraGetSuite());
        CuSuiteAddSuite(suite, BellmanGetSuite());
        //CuSuiteAddSuite(suite, GraphsSuite());

        CuSuiteRun(suite);
        CuSuiteSummary(suite, output);
        CuSuiteDetails(suite, output);
        printf("%s\n", output->buffer);
    }
    
    int main(void) {
        RunAllTests();
    }