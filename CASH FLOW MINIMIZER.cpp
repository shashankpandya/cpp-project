// CASH FLOW MINIMIZER
// This program optimizes financial transactions among multiple banks by minimizing the number of cash transactions using graph algorithms.

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
using namespace std;

// Structure to represent a bank with its name, net amount and payment types
struct Bank
{
    string name;
    int netAmount = 0;
    unordered_set<string> paymentTypes;
};

// Custom Pair class for storing transaction amount and payment mode
template <typename K, typename V>
class Pair
{
    K key;
    V value;

public:
    Pair(K k = 0, V v = "") : key(k), value(v) {}
    K getKey() const { return key; }
    V getValue() const { return value; }
    void setKey(K k) { key = k; }
    void setValue(V v) { value = v; }
};

// Utility to find the bank with maximum positive net amount
int getMaxIndex(const vector<Bank> &banks)
{
    int maxIdx = -1, maxAmount = INT_MIN;
    for (int i = 0; i < banks.size(); ++i)
    {
        if (banks[i].netAmount > maxAmount)
        {
            maxAmount = banks[i].netAmount;
            maxIdx = i;
        }
    }
    return maxIdx;
}

// Utility to find the bank with maximum negative net amount
int getMinIndex(const vector<Bank> &banks)
{
    int minIdx = -1, minAmount = INT_MAX;
    for (int i = 0; i < banks.size(); ++i)
    {
        if (banks[i].netAmount < minAmount)
        {
            minAmount = banks[i].netAmount;
            minIdx = i;
        }
    }
    return minIdx;
}

// Helper to find common payment mode
string getCommonPaymentMode(const Bank &a, const Bank &b)
{
    for (const auto &mode : a.paymentTypes)
    {
        if (b.paymentTypes.count(mode))
            return mode;
    }
    return "";
}

// Function to minimize cash flow using a greedy algorithm
void minimizeCashFlow(vector<Bank> &banks, vector<vector<Pair<int, string>>> &resultGraph)
{
    while (true)
    {
        int creditor = getMaxIndex(banks);
        int debtor = getMinIndex(banks);

        if (banks[creditor].netAmount == 0 || banks[debtor].netAmount == 0)
            break;

        int amount = min(banks[creditor].netAmount, -banks[debtor].netAmount);
        string mode = getCommonPaymentMode(banks[creditor], banks[debtor]);

        if (mode == "")
            mode = "WorldBank"; // Intermediary fallback

        resultGraph[debtor][creditor] = Pair<int, string>(amount, mode);
        banks[creditor].netAmount -= amount;
        banks[debtor].netAmount += amount;
    }
}

// Display transaction results
void printTransactions(const vector<vector<Pair<int, string>>> &resultGraph, const vector<Bank> &banks)
{
    cout << "\nMinimized Transactions:\n";
    for (int i = 0; i < resultGraph.size(); ++i)
    {
        for (int j = 0; j < resultGraph.size(); ++j)
        {
            if (resultGraph[i][j].getKey() > 0)
            {
                cout << banks[i].name << " pays Rs " << resultGraph[i][j].getKey()
                     << " to " << banks[j].name << " via " << resultGraph[i][j].getValue() << endl;
            }
        }
    }
}

int main()
{
    int numBanks;
    cout << "Enter number of banks: ";
    cin >> numBanks;

    vector<Bank> banks(numBanks);
    unordered_map<string, int> nameToIndex;

    // Input banks and their payment modes
    for (int i = 0; i < numBanks; ++i)
    {
        cout << "\nBank " << i + 1 << " name: ";
        cin >> banks[i].name;
        nameToIndex[banks[i].name] = i;

        int numModes;
        cout << "Enter number of payment modes: ";
        cin >> numModes;
        cout << "Enter payment modes: ";
        for (int j = 0; j < numModes; ++j)
        {
            string mode;
            cin >> mode;
            banks[i].paymentTypes.insert(mode);
        }
    }

    int numTransactions;
    cout << "\nEnter number of transactions: ";
    cin >> numTransactions;

    // Build netAmount graph
    for (int i = 0; i < numTransactions; ++i)
    {
        string from, to;
        int amount;
        cout << "Transaction " << i + 1 << " (from to amount): ";
        cin >> from >> to >> amount;
        if (nameToIndex.count(from) && nameToIndex.count(to))
        {
            banks[nameToIndex[from]].netAmount -= amount;
            banks[nameToIndex[to]].netAmount += amount;
        }
        else
        {
            cout << "Invalid bank names.\n";
        }
    }

    vector<vector<Pair<int, string>>> resultGraph(numBanks, vector<Pair<int, string>>(numBanks));
    minimizeCashFlow(banks, resultGraph);
    printTransactions(resultGraph, banks);

    return 0;
}
