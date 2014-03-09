#include "Histogram.h"

Histogram* Histogram::p_histogram = 0;

Histogram::Histogram()
{
    p_histogram = this;
}

Histogram *Histogram::getHistogram()
{
    return p_histogram;
}
