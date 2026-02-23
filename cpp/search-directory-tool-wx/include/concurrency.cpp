#include "concurrency.h"

wxString SdTokenExchange::sdToken = "";
long long SdTokenExchange::version = -1;
wxCriticalSection SdTokenExchange::sdTokenExchangeCS = wxCriticalSection();
double SdTokenExchange::DEFAULT_TIME = 3;
double SdTokenExchange::time = SdTokenExchange::DEFAULT_TIME;

queue<PathesExchange::Path> PathesExchange::pathes = queue<PathesExchange::Path>();
queue<pair<PercentageType, int>> PathesExchange::percentages = queue<pair<PercentageType, int>>();
long long PathesExchange::version = -1;
wxCriticalSection PathesExchange::pathesExchangeCS = wxCriticalSection();
