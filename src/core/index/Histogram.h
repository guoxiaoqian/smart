#ifndef HISTOGRAM_H
#define HISTOGRAM_H

class Histogram
{
private:
    static Histogram* p_histogram;
public:
    Histogram();
    static Histogram* getHistogram();
};

#endif // HISTOGRAM_H
