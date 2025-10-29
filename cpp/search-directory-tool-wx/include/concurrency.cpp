#include "concurrency.h"

wxString SdTokenExchange::sdToken = "";
long long SdTokenExchange::version = -1;
wxCriticalSection SdTokenExchange::sdTokenExchangeCS = wxCriticalSection();
double SdTokenExchange::DEFAULT_TIME = 3;
double SdTokenExchange::time = SdTokenExchange::DEFAULT_TIME;

vector<PathesExchange::Path> PathesExchange::pathes = vector<PathesExchange::Path>();
long long PathesExchange::version = -1;
wxCriticalSection PathesExchange::pathesExchangeCS = wxCriticalSection();
