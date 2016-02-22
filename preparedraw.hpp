#include <TGraph.h>
#ifndef _NO2D
#include <TGraph2D.h>
void preparedraw(std::string fname, TGraph2D *data, TGraph *errs, TGraph *firsthalf, TGraph *secondhalf, TGraph *maximum);
#else
void preparedraw(std::string fname, TGraph *errs, TGraph *firsthalf, TGraph *secondhalf, TGraph *maximum);
#endif // _NO2D
