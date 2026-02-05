#ifndef PERCENTAGE_H_INCLUDED
#define PERCENTAGE_H_INCLUDED

class PercentageCalculator
{
private:
    const int MID_DEPTH = 5;

    int percentage = 0;
    int depth = 0;
    int maximumDepth = 0;
    long long maximum = 0;
    long long sumBeforeMaximum = 0;
    long long sumAfterMaximum = 0;

    bool calc(long long nextCnt)
    {
        if (depth < MID_DEPTH)
        {
            long long sum = sumBeforeMaximum + maximum + sumAfterMaximum;
            long long averageMaximum = 2 * sum / depth;
            long long expectedMaximum = averageMaximum * MID_DEPTH / depth;
            long long expectedMidSum = MID_DEPTH * expectedMaximum / 2 - expectedMaximum / 2;
            int newPercentage;
            if (expectedMidSum == 0)
                newPercentage = 0;
            else
                newPercentage = 100.0 * sum / expectedMidSum * 0.5;
            if (newPercentage >= 100)
                newPercentage = 99;
            if (newPercentage > percentage)
            {
                percentage = newPercentage;
                return true;
            }
            else
                return false;
        }
        else if (depth >= MID_DEPTH && sumAfterMaximum == 0 && maximum < nextCnt)
        {
            return false;
        }
        else
        {
            long long sumBeforeMid = sumBeforeMaximum + maximum / 2;
            long long sumAfterMid = maximum / 2 + sumAfterMaximum;
            int newPercentage;
            if (sumBeforeMid == 0)
                newPercentage = 50;
            else
                newPercentage = 50 + 50.0 * sumAfterMid / sumBeforeMid;
            if (newPercentage >= 100)
                newPercentage = 99;
            if (newPercentage > percentage)
            {
                percentage = newPercentage;
                return true;
            }
            else
                return false;
        }
    }
public:
    bool addLayer(int depth, long long currentCnt, long long nextCnt)
    {
        this->depth = depth;
        if (currentCnt >= maximum)
        {
            sumBeforeMaximum += maximum + sumAfterMaximum;
            maximum = currentCnt;
            maximumDepth = depth;
            sumAfterMaximum = 0;
        } else
        {
            sumAfterMaximum += currentCnt;
        }
        return calc(nextCnt);
    }

    int getPercentage()
    {
        return percentage;
    }
};

#endif // PERCENTAGE_H_INCLUDED
